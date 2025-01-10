import sys
import rclpy
import time
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from .camera.camera import camera

import argparse

global camera_handle
camera_handle = camera()

class CameraClient(Node):

    def __init__(self):
        super().__init__('camera_client')
        self.cli = self.create_client(ProcessService, 'process_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = ProcessService.Request()

    def send_request(self, message):
        self.req.action = message
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class CameraSubscriber(Node):

    def __init__(self):
        super().__init__('camera_subscriber')
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.last_process = "camera init"

    def listener_callback(self, msg):
        # self.get_logger().info('I heard: "%s"' % msg.process)
        
        if msg.process != self.last_process:
            self.last_process = msg.process
            self.get_logger().info('camera do something')
            action = camera_handle.make_action(msg.process)
            self.get_logger().info('camera do this action: "%s"' % action)
            camera_client = CameraClient()
            if action != "error":
                time.sleep(1.5)
                response = camera_client.send_request("camera standby")
                self.get_logger().info('I heard: "%s"' % response.result)
                camera_client.destroy_node()
            else:
                self.get_logger().info('error cannot make action')
            time.sleep(1.5)

def main(args=None):

    rclpy.init(args=args)

    # the following test code is conflicts with launch file
    # parser = argparse.ArgumentParser(description='Cobotta Subscriber Node')
    # parser.add_argument('--test', type=str, default='default_topic', help='Specify the ROS topic name')
    # parsed_args = parser.parse_args(args)

    # if parsed_args.test != 'default_topic':
    #     print(f"get parsed: {parsed_args.test}")
    #     cobotta_test = cobotta(host,port,timeout)
    #     cobotta_test.make_action("cobotta " + parsed_args.test)
    # time.sleep(1.5)
    
    camera_subscriber = CameraSubscriber()

    rclpy.spin(camera_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    camera_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()