# csv_workflow_py/sequence_generator_node.py (SSH版)

import os
import json
import rclpy
from rclpy.node import Node
from msg_format.msg import ProcessMsg
from msg_format.srv import ProcessService
from ros2_utils_py.service_utils import call_service_async
import threading
import subprocess
import shlex

class SequenceGenerator(Node):
    def __init__(self):
        super().__init__('sequence_generator')
        
        # --- ローカルファイルパス関連 ---
        default_dir = os.path.abspath(os.path.join(os.getcwd(), 'sequence'))
        self.declare_parameter('files.sequence.dir', default_dir)
        self.declare_parameter('files.sequence.filename', 'sequence.txt')
        
        self.sequence_dir = self.get_parameter('files.sequence.dir').get_parameter_value().string_value
        self.sequence_filename = self.get_parameter('files.sequence.filename').get_parameter_value().string_value
        self.sequence_path = os.path.join(self.sequence_dir, self.sequence_filename)

        # --- リモート実行関連のパラメータ ---
        self.declare_parameter('remote_host', '192.168.0.90')
        self.declare_parameter('remote_user', 'nfm')
        self.declare_parameter('remote_script_path', '/home/nfm/Documents/kensei/remote_sequence_generator.py')
        self.declare_parameter('remote_venv_path', '/home/nfm/Documents/kensei/venv_pymatgen')
        self.declare_parameter('remote_stock_path', '/home/nfm/Documents/kensei/stock.txt') # リモートマシンのstock.txtパス

        self.remote_host = self.get_parameter('remote_host').value
        self.remote_user = self.get_parameter('remote_user').value
        self.remote_script_path = self.get_parameter('remote_script_path').value
        self.remote_venv_path = self.get_parameter('remote_venv_path').value
        self.remote_stock_path = self.get_parameter('remote_stock_path').value

        self.is_running = False
        
        # --- ROS2通信関連 ---
        self.sub_new_task = self.create_subscription(ProcessMsg, 'new_task', self.on_new_task, 10)
        self.process_client = self.create_client(ProcessService, 'process_service')
        while not self.process_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('process_service not available, waiting...')

        self.get_logger().info(f'SequenceGenerator (SSH mode) started. Remote host: {self.remote_host}')

    def on_new_task(self, msg: ProcessMsg):
        if self.is_running:
            self.get_logger().warning("Sequence generation is already in progress, ignoring new task.")
            return
            
        try:
            task_payload = json.loads(msg.process)
            task_id = int(task_payload.get('task_id', 0))

            thread = threading.Thread(
                target=self.run_remote_generation,
                args=(task_payload, task_id)
            )
            thread.start()

        except Exception as e:
            self.get_logger().error(f'Failed to process new task message: {e}')

    def run_remote_generation(self, task, task_id):
        self.is_running = True
        self.get_logger().info(f"Running remote generation for task_id={task_id}")
        
        # リモートで実行するPythonコマンド
        python_executable = f'{self.remote_venv_path}/bin/python'
        
        # --- ここから修正 ---
        
        # 各パラメータを安全に文字列として取得
        composition = str(task.get('Target_composition', ''))
        weight = str(task.get('Target_weight_(g)', 0.5))
        order = str(task.get('Weighing_order', 'melting_point'))
        flips = str(task.get('Number_of_flips', 3))
        arc_path = str(task.get('Arc_path', '3'))

        # shlex.quoteで各引数をエスケープ
        remote_command = (
            f"cd {os.path.dirname(self.remote_script_path)} && "
            f"{python_executable} {os.path.basename(self.remote_script_path)} "
            f"--composition {shlex.quote(composition)} "
            f"--weight {shlex.quote(weight)} "
            f"--order {shlex.quote(order)} "
            f"--flips {shlex.quote(flips)} "
            f"--arc-path {shlex.quote(arc_path)} "
            f"--stock-file {shlex.quote(self.remote_stock_path)}"
        )
        # --- ここまで修正 ---
        
        ssh_command = ['ssh', f'{self.remote_user}@{self.remote_host}', remote_command]
        
        try:
            result = subprocess.run(
                ssh_command,
                capture_output=True,
                text=True,
                timeout=30 # 30秒でタイムアウト
            )
            
            if result.returncode == 0:
                self.get_logger().info("Remote generation script completed successfully.")
                sequence_text = result.stdout
                
                # 結果をローカルファイルに書き込み
                os.makedirs(self.sequence_dir, exist_ok=True)
                with open(self.sequence_path, 'w', encoding='utf-8') as f:
                    f.write(sequence_text)
                self.get_logger().info(f'Wrote sequence file: {self.sequence_path}')
                
                # MainProcessへロード指示
                self.send_load_request(task_id)

            else:
                self.get_logger().error(f"Remote generation script failed with return code {result.returncode}")
                self.get_logger().error(f"Remote stderr: {result.stderr.strip()}")
                
        except subprocess.TimeoutExpired:
            self.get_logger().error("Remote generation script timed out.")
        except Exception as e:
            self.get_logger().error(f"An error occurred during remote execution: {str(e)}")
        finally:
            self.is_running = False

    def send_load_request(self, task_id):
        action = f'LOADSEQ_FILE={self.sequence_path} TASK_ID={task_id}'
        self.get_logger().info(f'Sending load request: {action}')
        call_service_async(self.process_client, self.get_logger(), action, "Process")


def main(args=None):
    rclpy.init(args=args)
    node = SequenceGenerator()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()