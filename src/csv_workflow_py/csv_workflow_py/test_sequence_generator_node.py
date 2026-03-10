#!/usr/bin/env python3
import os
import json
import rclpy
from rclpy.node import Node
from msg_format.msg import ProcessMsg
from msg_format.srv import ProcessService


class TestSequenceGenerator(Node):
    def __init__(self):
        super().__init__('test_sequence_generator')
        
        # files.sequence.dir / files.sequence.filename をパラメータ化
        default_dir = os.path.abspath(
            os.path.join(os.getcwd(), 'sequence')
        )
        self.declare_parameter('files.sequence.dir', default_dir)
        self.declare_parameter('files.sequence.filename', 'sequence.txt')
        
        self.sequence_dir = self.get_parameter('files.sequence.dir').get_parameter_value().string_value
        self.sequence_filename = self.get_parameter('files.sequence.filename').get_parameter_value().string_value
        self.sequence_path = os.path.join(self.sequence_dir, self.sequence_filename)
        
        # subscribe: new_task
        self.sub_new_task = self.create_subscription(
            ProcessMsg, 'new_task', self.on_new_task, 10
        )
        
        # client: process_service
        self.cli = self.create_client(ProcessService, 'process_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('process_service not available, waiting...')
        
        self.get_logger().info(f'TestSequenceGenerator started. sequence_path={self.sequence_path}')
    
    def on_new_task(self, msg: ProcessMsg):
        """新しいタスクを受信してテスト用シーケンスを生成"""
        try:
            task = json.loads(msg.process)
        except Exception as e:
            self.get_logger().error(f'Invalid task payload: {e}')
            return
        
        task_id = int(task.get('task_id', 0))
        flips = int(task.get('Number_of_flips', 2))
        
        self.get_logger().info(f'Generating test sequence for task_id={task_id}, flips={flips}')
        
        # テスト用：slider_init <-> slider_shelf_1 の往復
        lines = []
        lines.append('slider_init weighing_init cobotta_init plc_init')
        
        for i in range(flips):
            lines.append(f'# Flip {i+1}')
            lines.append('slider_shelf_1')
            lines.append('plc_wait_1')
            lines.append('slider_pos1')
            lines.append('plc_wait_1')
        
        lines_append('plc_buzz')

        # 最終位置
        # lines.append('slider_init weighing_init cobotta_init plc_init')
        
        # ファイル出力（files.sequence.dir/files.sequence.filename）
        os.makedirs(self.sequence_dir, exist_ok=True)
        try:
            with open(self.sequence_path, 'w', encoding='utf-8') as f:
                f.write('\n'.join(lines) + '\n')
            self.get_logger().info(f'Wrote sequence file: {self.sequence_path}')
        except Exception as e:
            self.get_logger().error(f'Failed to write sequence: {e}')
            return
        
        # MainProcessへロード指示（ProcessService）
        self.send_load_request(task_id)
    
    def send_load_request(self, task_id):
        """MainProcessにシーケンスファイルのロードを指示"""
        action = f'LOADSEQ_FILE={self.sequence_path} TASK_ID={task_id}'
        req = ProcessService.Request()
        req.action = action
        
        self.get_logger().info(f'Sending load request: {action}')
        
        # 非同期で送信し、結果を待たない
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
    node = TestSequenceGenerator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()