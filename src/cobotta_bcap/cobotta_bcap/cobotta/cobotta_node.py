#!/usr/bin/env python3

import rclpy
import time
import threading
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from ros2_utils_py.service_utils import call_service

from .cobotta import cobotta

class CobottaNode(Node):
    """
    Cobotta Node class that subscribes to a topic and processes messages.
    """
    def __init__(self):
        super().__init__('cobotta_subscriber')
        
        # cobotta parameters
        self.host = "192.168.0.1"
        self.port = 5007
        self.timeout = 2000
        
        # initial state
        self.last_process = "cobotta init"
        self.processing_lock = threading.Lock()
        self.service_in_progress = False
        
        # create cobotta instance
        self.process_client = self.create_client(ProcessService, 'process_service')
        
        # create subscriber
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        
        self.get_logger().info('Cobotta node initialized')
    
    def listener_callback(self, msg):
        process = msg.process
        
        if process != self.last_process:
            self.last_process = process
            self.get_logger().info(f'Processing new step: {process}')
            
            try:
                cobotta_handle = cobotta(self.host, self.port, self.timeout)
                action_result = cobotta_handle.make_action(process)
                
                if action_result != "error":
                    success = call_service(
                        client=self.process_client,
                        logger=self.get_logger(),
                        action="cobotta_standby",
                        service_name="process_service"
                    )
                    
                    if not success:
                        self.get_logger().error('Failed to call standby service')
                else:
                    self.get_logger().error('Error cannot make action')
            
            except Exception as e:
                self.get_logger().error(f'Exception during action execution: {str(e)}')
            
            time.sleep(1.5)
