#!/usr/bin/env python3

import sys
import rclpy
import time
from .instrumentp.instrumentp_node import InstrumentPNode
from .instrumentp.instrumentp import instrumentp

def main(args=None):
    rclpy.init(args=args)
    
    # test action
    test = False
    if len(sys.argv) > 1 and test:
        print(f"Running test action: {sys.argv[1]}")
        instrumentp_test = instrumentp("192.168.0.999", 7777)
        instrumentp_test.make_action("instrumentp_" + sys.argv[1])
        time.sleep(1.5)
        rclpy.shutdown()
        return
    
    # create CobottaNode
    node = InstrumentPNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()