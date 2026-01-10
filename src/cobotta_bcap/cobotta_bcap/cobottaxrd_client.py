import sys
from msg_format.srv import TestSrv

import rclpy
from rclpy.node import Node


class CobottaXRDClientAsync(Node):

    def __init__(self):
        super().__init__('cobottaxrd_client_async')
        self.cli = self.create_client(TestSrv, 'test_srv_xrd')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = TestSrv.Request()

    def send_request(self, actionOne, actionTwo):
        self.req.action_1 = actionOne
        self.req.action_2 = actionTwo
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()


def main(args=None):
    rclpy.init(args=args)

    cobotta_client = CobottaXRDClientAsync()
    response = cobotta_client.send_request(str(sys.argv[1]), str(sys.argv[2]))
    cobotta_client.get_logger().info(
        'action: %s \n target: %s \n message: %s' %
        (str(sys.argv[1]), str(sys.argv[2]), response.result))

    cobotta_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
