import sys
import rclpy
import time
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from .pybcapclient.bcapclient import BCAPClient
from .cobotta.cobotta import cobotta

import argparse

host = "192.168.0.1"
port = 5007
timeout = 2000

"""
cobotta_position
p10 init
p11 take dosing on shelf
xp12 take dosing on mid shelf
xp13 p10 to p12 mid
p14 weighing dosing position
p15 weighing bowl position
P16 into weighing
p17 intermediate between p10 and p18
p18 cup position after synthesis

P20 p1 to arc standby
P21 p2 to arc standby
P22 arc standby

cobotta_task
init
weight_take_bowl
weight_put_bowl
weight_take_dose
weight_put_dose
arc_put_bowl
arc_take_bowl
shelf_take_dose
shelf_put_dose
stock_put_cup
"""

class CobottaClient(Node):

    def __init__(self):
        super().__init__('cobotta_client')
        self.cli = self.create_client(ProcessService, 'process_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = ProcessService.Request()

    def send_request(self, message):
        self.req.action = message
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class CobottaSubscriber(Node):

    def __init__(self):
        super().__init__('cobotta_subscriber')
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.last_process = "cobotta init"

    def listener_callback(self, msg):
        # self.get_logger().info('I heard: "%s"' % msg.process)
        
        if msg.process != self.last_process:
            self.last_process = msg.process
            cobotta_handle = cobotta(host,port,timeout)
            action = cobotta_handle.make_action(msg.process)
            cobotta_client = CobottaClient()
            if action != "error":
                response = cobotta_client.send_request("cobotta standby")
                cobotta_client.get_logger().info('I heard: "%s"' % response.result)
                cobotta_client.destroy_node()
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
    
    cobotta_subscriber = CobottaSubscriber()

    rclpy.spin(cobotta_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    cobotta_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()