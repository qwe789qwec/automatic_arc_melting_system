#!/usr/bin/env python3

import sys
import rclpy
import time
from .cobotta.cobotta_node import CobottaNode
from .cobotta.cobotta import cobotta

def main(args=None):
    rclpy.init(args=args)
    
    # test action
    test = False
    if len(sys.argv) > 1 and test:
        print(f"Running test action: {sys.argv[1]}")
        cobotta_test = cobotta("192.168.0.1", 5007, 2000)
        cobotta_test.make_action("cobotta " + sys.argv[1])
        time.sleep(1.5)
        rclpy.shutdown()
        return
    
    # create CobottaNode
    node = CobottaNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()