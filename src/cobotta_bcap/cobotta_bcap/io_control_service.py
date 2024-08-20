from msg_format.srv import TestSrv
from .pybcapclient.bcapclient import BCAPClient

import rclpy
from rclpy.node import Node
from .cobotta.cobotta import cobotta

class CobottaActionService(Node):

    def __init__(self):
        super().__init__('cobotta_action')
        self.srv = self.create_service(TestSrv, 'test_srv', self.cobotta_act)

    def cobotta_act(self, request, response):
        self.get_logger().info('Incoming request\nactionOne: %s actionTwo: %s' % (request.action_1, request.action_2))
        response.result = 'init status'

        cobotta_client = cobotta("192.168.0.11", 5007, 2000)
        
        value = cobotta_client.changeValue(request.action_1, request.action_2)

        response.result = "Read Variable" + request.action_1 + " = " + str(value)
        return response


def main(args=None):
    rclpy.init(args=args)

    cobotta_action = CobottaActionService()

    rclpy.spin(cobotta_action)

    rclpy.shutdown()


if __name__ == '__main__':
    main()