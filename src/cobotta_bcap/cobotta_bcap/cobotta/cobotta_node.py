#!/usr/bin/env python3

import rclpy
import time
import threading
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from .cobotta import cobotta

class CobottaNode(Node):
    """
    Cobotta机器人控制节点
    """
    def __init__(self):
        super().__init__('cobotta_subscriber')
        
        # 硬编码配置
        self.host = "192.168.0.1"
        self.port = 5007
        self.timeout = 2000
        
        # 初始化变量
        self.last_process = "cobotta init"
        self.processing_lock = threading.Lock()
        self.service_in_progress = False
        
        # 创建订阅者
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        
        self.get_logger().info('Cobotta node initialized')
    
    def listener_callback(self, msg):
        """
        处理接收到的消息
        """
        process = msg.process
        
        # 使用互斥锁防止并发处理
        if not self.processing_lock.acquire(blocking=False):
            self.get_logger().warn('Previous message still processing, skipping')
            return
        
        try:
            if process != self.last_process:
                self.last_process = process
                self.get_logger().info(f'Processing new step: {process}')
                
                try:
                    # 创建cobotta控制器
                    cobotta_handle = cobotta(self.host, self.port, self.timeout)
                    
                    # 执行操作
                    action_result = cobotta_handle.make_action(process)
                    
                    if action_result != "error":
                        # 调用服务
                        self.call_process_service("cobotta standby")
                    else:
                        self.get_logger().error('Error cannot make action')
                
                except Exception as e:
                    self.get_logger().error(f'Exception during action execution: {str(e)}')
                
                # 添加延迟防止过快请求
                time.sleep(1.5)
        
        finally:
            # 确保锁被释放
            self.processing_lock.release()
    
    def call_process_service(self, action):
        """
        调用处理服务
        """
        if self.service_in_progress:
            self.get_logger().warn('Service call already in progress, skipping')
            return False
        
        self.service_in_progress = True
        success = False
        
        try:
            # 创建客户端
            client = self.create_client(ProcessService, 'process_service')
            
            # 等待服务可用
            if not client.wait_for_service(timeout_sec=1.0):
                self.get_logger().error('Service not available')
                return False
            
            # 创建请求
            request = ProcessService.Request()
            request.action = action
            
            # 发送请求
            future = client.call_async(request)
            
            # 等待响应
            rclpy.spin_until_future_complete(self, future)
            
            if future.done():
                response = future.result()
                self.get_logger().info(f'Service response: {response.result}')
                success = True
            else:
                self.get_logger().error('Service call timed out')
        
        except Exception as e:
            self.get_logger().error(f'Service call failed: {str(e)}')
        
        finally:
            self.service_in_progress = False
            return success