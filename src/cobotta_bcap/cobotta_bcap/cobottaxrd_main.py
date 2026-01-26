#!/usr/bin/env python3

import sys
import rclpy
import time
from .cobotta.cobottaxrd_node import CobottaXRDNode
from .cobotta.cobottaxrd import cobottaxrd

def main(args=None):
    rclpy.init(args=args)
    
    # test action
    test = False
    if len(sys.argv) > 1 and test:
        print(f"Running test action: {sys.argv[1]}")
        cobotta_test = cobottaxrd("192.168.0.11", 5007, 2000)
        cobotta_test.make_action("cobottaxrd " + sys.argv[1])
        time.sleep(1.5)
        rclpy.shutdown()
        return
    
    # create CobottaNode
    node = CobottaXRDNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()