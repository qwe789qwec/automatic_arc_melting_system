import sys
import rclpy
from rclpy.node import Node

from msg_format.msg import Process
from msg_format.srv import ProcessFormat


class CobottaClient(Node):

    def __init__(self):
        super().__init__('cobotta_client')
        self.cli = self.create_client(ProcessFormat, 'process_format')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = ProcessFormat.Request()

    def send_request(self, message):
        count = int(message)
        if count > 60:
            self.req.action = "three"
        elif count > 40:
            self.req.action = "two"
        elif count > 20 :
            self.req.action = "one"
        else:
            self.req.action = "init"
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class CobottaSubscriber(Node):

    def __init__(self):
        super().__init__('cobotta_subscriber')
        self.subscription = self.create_subscription(
            Process,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.process)
        if msg.process.startswith("init"):
            message = msg.process[5:]
        elif msg.process.startswith("keep"):
            message = msg.process[5:]
        elif msg.process.startswith("first"):
            message = msg.process[6:]
        else:
            message = "0"

        cobotta_client = CobottaClient() 
        response = cobotta_client.send_request(message)
        cobotta_client.get_logger().info('I heard: "%s"' % response.result)
        cobotta_client.destroy_node()


def main(args=None):
    rclpy.init(args=args)
    

    cobotta_subscriber = CobottaSubscriber()

    rclpy.spin(cobotta_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    cobotta_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()