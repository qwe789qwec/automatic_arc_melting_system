import sys
from tcp_format.srv import CobottaBcap

import rclpy
from rclpy.node import Node


class CobottaClientAsync(Node):

    def __init__(self):
        super().__init__('cobotta_client_async')
        self.cli = self.create_client(CobottaBcap, 'cobotta_bcap')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = CobottaBcap.Request()

    def send_request(self, action, target):
        self.req.action = action
        self.req.target = target
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()


def main(args=None):
    rclpy.init(args=args)

    cobotta_client = CobottaClientAsync()
    response = cobotta_client.send_request(str(sys.argv[1]), str(sys.argv[2]))
    cobotta_client.get_logger().info(
        'action: %s \n target: %s \n status: %s \n message: %s' %
        (str(sys.argv[1]), str(sys.argv[2]), response.status, response.message))

    cobotta_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()