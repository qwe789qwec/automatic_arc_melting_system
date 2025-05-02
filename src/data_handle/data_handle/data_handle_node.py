import rclpy
import time
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from .data_record.data_handle import DataHandle

class DataRecordNode(Node):
    def __init__(self, file_name = None):
        super().__init__('record_subscriber')

        self.data_handle = DataHandle()

        self.srv = self.create_service(ProcessService, 'write_data', self.write_data)

        # create subscriber
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        
        self.get_logger().info('record node initialized')

        self.last_process = "record init"

    def write_data(self, request, response):
        write_data = request.action
        self.data_handle.record_data(write_data)
        response.result = 'Success'

        return response
    
    def listener_callback(self, msg):
        process = msg.process
        
        if process != self.last_process:
            self.last_process = process
            self.get_logger().info(f'Processing new step: {process}')
            
            action_result = self.data_handle.make_action(process)
            if action_result == "error":
                self.get_logger().error('Error in action execution')
                return

def main(args=None):
    rclpy.init(args=args)

    data_service = DataRecordNode()

    rclpy.spin(data_service)
    data_service.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()