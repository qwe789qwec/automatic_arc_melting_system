#!/usr/bin/env python3

import sys
import rclpy
import time
from .cobotta.cobotta_node import CobottaNode
from .cobotta.cobotta import cobotta

def main(args=None):
    rclpy.init(args=args)

    cobotta_control = cobotta("192.168.0.1", 5007, 2000)

    # create CobottaNode
    cobottanode = CobottaNode("cobotta", cobotta_control, "process_service", "cobotta_topic")

    # test action
    test = False
    if len(sys.argv) > 1 and test:
        print(f"Running test action: {sys.argv[1]}")
        cobottanode.make_action("cobotta_" + sys.argv[1])
        time.sleep(1.5)
    
    rclpy.spin(cobottanode)
    cobottanode.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()