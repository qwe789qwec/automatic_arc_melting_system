#!/usr/bin/env python3
import os
import json
import rclpy
from rclpy.node import Node
from msg_format.msg import ProcessMsg
from msg_format.srv import ProcessService
from pymatgen.core import Composition
import pymatgen.core as mg


class SequenceGenerator(Node):
    def __init__(self):
        super().__init__('sequence_generator')
        
        # files.sequence.dir / files.sequence.filename をパラメータ化
        default_dir = os.path.abspath(
            os.path.join(os.getcwd(), 'sequence')
        )
        self.declare_parameter('files.sequence.dir', default_dir)
        self.declare_parameter('files.sequence.filename', 'sequence.txt')
        self.declare_parameter('files.stock.path', 'stock.txt')
        
        self.sequence_dir = self.get_parameter('files.sequence.dir').get_parameter_value().string_value
        self.sequence_filename = self.get_parameter('files.sequence.filename').get_parameter_value().string_value
        self.sequence_path = os.path.join(self.sequence_dir, self.sequence_filename)
        self.stock_path = self.get_parameter('files.stock.path').get_parameter_value().string_value
        
        # subscribe: new_task
        self.sub_new_task = self.create_subscription(
            ProcessMsg, 'new_task', self.on_new_task, 10
        )
        
        # client: process_service
        self.cli = self.create_client(ProcessService, 'process_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('process_service not available, waiting...')
        
        self.get_logger().info(f'SequenceGenerator started. sequence_path={self.sequence_path}')
    
    # Auxiliary functions from streamlit app
    def get_molarmass(self, formula):
        return float(Composition(formula).weight)

    def masscalc(self, formula, target_mass):
        mass = self.get_molarmass(formula)
        mol = target_mass / mass
        composition = Composition(formula)
        value_dic = composition.as_dict()
        original_mass = {key: self.get_molarmass(key) * value * mol for key, value in value_dic.items()}
        return original_mass

    def get_melting_point(self, element_symbol):
        try:
            element = mg.Element(element_symbol)
            return element.melting_point if element.melting_point is not None else 0.0
        except KeyError:
            return None

    def load_from_stock_file(self):
        try:
            with open(self.stock_path, "r") as file:
                return json.load(file)
        except FileNotFoundError:
            self.get_logger().error(f"stock file not found: {self.stock_path}")
            return {}
        except json.JSONDecodeError as e:
            self.get_logger().error(f"Invalid JSON in stock file: {e}")
            return {}

    def query_stock(self, element_name):
        reverse_position = self.load_from_stock_file()
        for position, element in reverse_position.items():
            if element == element_name:
                return tuple(map(int, position.strip("()").split(", ")))  # (行, 列) の形式に変換
        return None
    
    def on_new_task(self, msg: ProcessMsg):
        """新しいタスクを受信してシーケンスを生成"""
        try:
            task = json.loads(msg.process)
        except Exception as e:
            self.get_logger().error(f'Invalid task payload: {e}')
            return
        
        task_id = int(task.get('task_id', 0))
        target_composition = task.get('Target_composition', '')
        target_weight = float(task.get('Target_weight_g', 0.5))
        weighing_order = task.get('Weighing_order', 'melting_point')
        flip_times = int(task.get('Number_of_flips', 3))
        arc_path = task.get('Arc_path', '3')
        
        self.get_logger().info(f'Generating sequence for task_id={task_id}, composition={target_composition}')
        
        # Generate sequence
        steps = self.generate_sequence(
            target_composition, 
            target_weight, 
            weighing_order, 
            flip_times, 
            arc_path
        )
        
        # ファイル出力
        os.makedirs(self.sequence_dir, exist_ok=True)
        try:
            with open(self.sequence_path, 'w', encoding='utf-8') as f:
                f.write(''.join(steps))
            self.get_logger().info(f'Wrote sequence file: {self.sequence_path} ({len(steps)} steps)')
        except Exception as e:
            self.get_logger().error(f'Failed to write sequence: {e}')
            return
        
        # MainProcessへロード指示
        self.send_load_request(task_id)
    
    def generate_sequence(self, target_composition, target_weight, weighing_order, flip_times, arc_path):
        """Streamlitアプリと同じロジックでシーケンスを生成"""
        steps = []
        
        # 初期化（record_onを先に）
        steps.append(f"record_on_{target_composition} slider_init cobotta_init weighing_init plc_init\n")
        steps.append("\n")
        steps.append("cobotta_takeCup_stock\n")
        steps.append("weighing_open slider_weightPos\n")
        steps.append("cobotta_putCup_weight\n")
        
        if not target_composition:
            return steps
        
        # 元素の質量計算
        mass_raw_atoms = self.masscalc(target_composition, target_weight)
        
        # 元素情報の準備
        elements_info = []
        input_order_elements = list(mass_raw_atoms.keys())
        
        for element, mass in mass_raw_atoms.items():
            melting_point = self.get_melting_point(element)
            elements_info.append((element, mass, melting_point))
        
        # ソート処理
        if weighing_order == "melting_point":
            sorted_elements = sorted(elements_info, key=lambda item: item[2] if item[2] is not None else float('inf'), reverse=False)
        elif weighing_order == "Alphabetical":
            sorted_elements = sorted(elements_info, key=lambda item: item[0])
        elif weighing_order == "As_input":
            as_input_order_dict = {element: index for index, element in enumerate(input_order_elements)}
            sorted_elements = sorted(elements_info, key=lambda item: as_input_order_dict[item[0]])
        
        output_data = {element: {"mass": mass, "melting_point": melting_point} for element, mass, melting_point in sorted_elements}
        
        # 元素ごとの処理
        elements_list = list(output_data.keys())
        total_elements = len(elements_list)
        
        for idx, element in enumerate(elements_list):
            mass = output_data[element]['mass']
            miligram = round(float(mass)*1000, 1)
            position = self.query_stock(element)
            
            if position is not None:
                cobotta_position, slider_position = position
                steps.append("\n")
                steps.append(f"slider_shelf_{slider_position} weighing_close\n")
                steps.append(f"cobotta_takeDose_shelf{cobotta_position}\n")
                steps.append("weighing_open slider_weightPos\n")
                steps.append("cobotta_putDose_weight\n")
                steps.append(f"weighing_mgram_{element}_{miligram:.1f}\n")
                
                # 最後の要素の場合は特別な処理
                if idx == total_elements - 1:
                    steps.append("cobotta_takeCup_weight plc_vent\n")
                    steps.append("weighing_close slider_pos1\n")
                    steps.append("cobotta_putCup_arc plc_gate_open\n")
                    steps.append("slider_weightPos weighing_open plc_checkValve\n")
                    steps.append("slider_putCupArc cobotta_takeDose_weight\n")
                    steps.append(f"plc_gate_close slider_shelf_{slider_position} weighing_close\n")
                    steps.append(f"plc_pump cobotta_putDose_shelf{cobotta_position}\n")
                else:
                    steps.append("cobotta_takeDose_weight\n")
                    steps.append(f"weighing_close slider_shelf_{slider_position}\n")
                    steps.append(f"cobotta_putDose_shelf{cobotta_position}\n")
            else:
                self.get_logger().warning(f"Element {element} not found in stock!")
        
        # アーク溶解プロセス
        steps.append("\n")
        steps.append("slider_arcinit\n")
        
        video_prefix = target_composition
        
        for i in range(flip_times):
            direction = "cw" if i % 2 == 0 else "ccw"
            steps.append(f"plc_buzz record_video_start_{video_prefix}{i+1}\n")
            steps.append("plc_arc_on\n")
            steps.append(f"slider_arc_{direction}_{arc_path}\n")
            
            if i == flip_times - 1:  # 最後のflip
                steps.append("plc_arc_off record_video_stop\n")
                steps.append("plc_wait_20\n")
            else:
                steps.append("plc_arc_off\n")
                steps.append("plc_wait_20\n")
                steps.append("plc_autoFlip\n")
                steps.append("record_video_stop\n")
                steps.append("\n")
        
        # 最後の処理
        steps.append("\n")
        steps.append("plc_vent slider_pos1\n")
        steps.append("plc_gate_open\n")
        steps.append("plc_checkValve\n")
        steps.append("slider_takeCupArc\n")
        steps.append("\n")
        steps.append("plc_gate_close cobotta_takeCup_arc\n")
        steps.append("slider_weightPos weighing_open\n")
        steps.append("plc_singlePump cobotta_putCup_weight\n")
        steps.append("weighing_close\n")
        steps.append("plc_wait_3\n")
        steps.append("weighing_getweight\n")
        steps.append("weighing_open\n")
        steps.append("cobotta_takeCup_weight\n")
        steps.append("weighing_close slider_productStock\n")
        steps.append("cobotta_putCupStock\n")
        steps.append("slider_init weighing_init plc_init record_off\n")  # omit cobotta_init for continuous run
        
        return steps
    
    def send_load_request(self, task_id):
        """MainProcessにシーケンスファイルのロードを指示"""
        action = f'LOADSEQ_FILE={self.sequence_path} TASK_ID={task_id}'
        req = ProcessService.Request()
        req.action = action
        
        self.get_logger().info(f'Sending load request: {action}')
        
        future = self.cli.call_async(req)
        future.add_done_callback(
            lambda f: self.load_request_callback(f, task_id)
        )
    
    def load_request_callback(self, future, task_id):
        """ロードリクエストの結果を処理"""
        try:
            resp = future.result()
            if resp:
                self.get_logger().info(f'ProcessService response for task_id={task_id}: {resp.result}')
            else:
                self.get_logger().error(f'ProcessService call failed for task_id={task_id}')
        except Exception as e:
            self.get_logger().error(f'Service call failed: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = SequenceGenerator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()