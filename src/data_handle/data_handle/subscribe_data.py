import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from msg_format.msg import ProcessMsg  # インポートを追加
import sys
import os
from datetime import datetime
from .data_record.data_record import DataRecord

class DualTopicSubscriber(Node):
    def __init__(self, file_prefix):
        super().__init__('dual_topic_subscriber')
        self.datadecorder = DataRecord(file_prefix)
        
        # 1つ目のトピックを購読
        self.subscription1 = self.create_subscription(
            ProcessMsg,
            'topic',  # 購読する1つ目のトピック名
            self.listener_callback1,
            10
        )
        self.subscription1  # prevent unused variable warning

        # 2つ目のトピックを購読
        self.subscription2 = self.create_subscription(
            ProcessMsg,
            'topic_weigh',  # 購読する2つ目のトピック名
            self.listener_callback2,
            10
        )
        self.subscription2  # prevent unused variable warning

    def listener_callback1(self, msg):
        current_message = msg.process
        self.datadecorder.fileWrite(current_message)

    def listener_callback2(self, msg):
        current_message = msg.process
        self.datadecorder.fileWrite(current_message)

def main(args=None):
    rclpy.init(args=args)

    # argvからファイル名の接頭辞を取得
    if len(sys.argv) > 1:
        file_prefix = sys.argv[1]
    else:
        # file_prefix = 'default_prefix'
        file_prefix = "Expt_" + datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    node = DualTopicSubscriber(file_prefix)
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()