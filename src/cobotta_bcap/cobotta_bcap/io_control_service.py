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

        if request.action_1.startswith("run"):
            action = request.action_1.replace("run", "")
            status = cobotta_client.runTask(action)
            self.get_logger().info('run: %s get: %s' % (action, str(status)))
            response.result = "run " + action + " = " + str(status)

        elif request.action_1.startswith("change"):
            # remove action_1 change
            action = request.action_1.replace("change", "")
            value = cobotta_client.changeValue(action, request.action_2)
            self.get_logger().info('value: %s get: %s' % (action, str(value)))
            response.result = "Read Variable" + action + " = " + str(value)

        elif request.action_1.startswith("goto"):
            # remove action_1 change
            action = request.action_1.replace("goto", "")
            cobotta_client.gotoPoint(int(request.action_2))
            self.get_logger().info('end')
            response.result = "goto P" + str(request.action_2)

        return response


def main(args=None):
    rclpy.init(args=args)

    cobotta_action = CobottaActionService()

    rclpy.spin(cobotta_action)

    rclpy.shutdown()


if __name__ == '__main__':
    main()