import subprocess
import rclpy
from rclpy.node import Node
from msg_format.msg import ProcessMsg# this is for receive process command from main_process
from msg_format.srv import ProcessService# this is to reply the status and so on
from ros2_utils_py.service_utils import get_command, call_service_async


class XrdMeasSystem(Node):
    def __init__(self):
        super().__init__('xrd_meas_system')
        self.device_id = 'xrdmeas'
        self.current_step = ""
        self.last_command = None# prevents double execution

        self.process_client = self.create_client(ProcessService, 'process_service')

        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.topic_callback,
            10
        )

        self.get_logger().info("XrdMeasSystem initialized")

    def topic_callback(self, msg):
        message = msg.process
        self.get_logger().info(f"Received topic message: {message}")

        for action in message.split():
            cmd = get_command(action, self.device_id)

            if cmd is None or cmd == 'none':
                continue

            self.get_logger().info(f"Matched command: {cmd}")

            if cmd == self.last_command:
                #self.get_logger().info(f"Ignored duplicate command: {cmd}")
                return
            self.last_command = cmd

            if cmd == f"{self.device_id}_standby":
                self.publish_status("standby")
                return

            if cmd.startswith(f"{self.device_id}_run_"):
                name = cmd[len(f"{self.device_id}_run_"):]
                self.run_subprocess(name)
                return

            if cmd == f"{self.device_id}_init":
                self.publish_status("standby")
                return

    def run_subprocess(self, name):
        self.get_logger().info(f"Running subprocess for: {name}")
        try:
            result = subprocess.run(
                ['python3', '-m', 'xrd_meas.xrdsocket_client_II', name],
                check=True,
                capture_output=True,
                text=True
            )
            self.get_logger().info(f"Subprocess output:\n{result.stdout}")
            self.publish_status("standby")
        except subprocess.CalledProcessError as e:
            self.get_logger().error(f"Subprocess failed:\n{e.stderr}")
            self.publish_status("error")

    def publish_status(self, status):
        if not self.process_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().error("process_service not available!")
            return

        action = f"{self.device_id}_{status}"
        call_service_async(self.process_client, self.get_logger(), action, "Process")


def main(args=None):
    rclpy.init(args=args)
    node = XrdMeasSystem()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()