#!/usr/bin/env python3

import rclpy
import time
import threading
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from ros2_utils_py.service_utils import call_service, get_command

class InstrumentControl:
    def __init__(self):
        data_flag = False

    def make_action(self, action: str):
        pass

    def make_action_async(self, action: str):
        pass

class InstrumentNode(Node):
    """
    Cobotta Node class that subscribes to a topic and processes messages.
    """
    def __init__(self, 
                 node_name :str, 
                 instrument_control: InstrumentControl, 
                 process_service_name: str = 'process_service',
                 subscription_name: str = 'topic'):
        super().__init__(node_name + '_node')
        
        # initial state
        self.instrument_control = instrument_control
        self.instrument_name = node_name
        self.current_command = node_name + "_first"
        
        self.instrument_future = None
        self.instrument_future_valid = False

        # create cobotta instance
        self.process_client = self.create_client(ProcessService, process_service_name)
        self.data_client = self.create_client(ProcessService, "write_data")
        
        # create subscriber
        self.subscription = self.create_subscription(
            ProcessMsg,
            subscription_name,
            self.command_action,
            10)
        
        self.get_logger().info('Cobotta node initialized')
    
    def test_instrument_action(self, action: str):
        """
        Test the instrument action directly.
        """
        try:
            return self.instrument_control.make_action(action)
        except Exception as e:
            self.get_logger().error(f"Exception during test action: {str(e)}")
    
    def command_action(self, msg):
        message = msg.process
        command = get_command(message, self.instrument_name)

        if self.instrument_future_valid and not self.instrument_future.done():
            # self.get_logger().info(f"Command {self.current_command} is still running")
            return

        
        if command != self.current_command:
            self.current_command = command
            self.get_logger().info(f'Processing new step: {command}')
            
            try:
                action_result = self.instrument_control.make_action(command)
                
                if action_result != "error":
                    success = call_service(
                        client=self.process_client,
                        logger=self.get_logger(),
                        action="cobotta_standby"
                    )
                    
                    if not success:
                        self.get_logger().error('Failed to call standby service')
                else:
                    self.get_logger().error('Error cannot make action')
            
            except Exception as e:
                self.get_logger().error(f'Exception during action execution: {str(e)}')
            
            time.sleep(1.5)
