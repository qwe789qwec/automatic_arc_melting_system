#!/usr/bin/env python3

import sys
import rclpy
import time
from .cobotta.cobotta_node import CobottaNode
from .cobotta.cobotta import cobotta

def main(args=None):
    rclpy.init(args=args)
    
    # 简单测试支持，不使用复杂的参数解析
    test = False
    if len(sys.argv) > 1 and test:
        print(f"Running test action: {sys.argv[1]}")
        cobotta_test = cobotta("192.168.0.1", 5007, 2000)
        cobotta_test.make_action("cobotta " + sys.argv[1])
        time.sleep(1.5)
        rclpy.shutdown()
        return
    
    # 创建节点
    node = CobottaNode()
    
    try:
        # 运行节点
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        node.get_logger().error(f'Unexpected error: {str(e)}')
    finally:
        # 清理资源
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()