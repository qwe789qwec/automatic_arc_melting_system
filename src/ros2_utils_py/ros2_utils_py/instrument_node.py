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
        self.data_flag = False

    def make_action(self, action: str):
        pass

    def make_action_async(self, action: str):
        pass

    def write_data(self):
        pass
    
    def get_data(self):
        pass

class InstrumentNode(Node):
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
        try:
            return self.instrument_control.make_action(action)
        except Exception as e:
            self.get_logger().error(f"Exception during test action: {str(e)}")
    
    def command_action(self, msg):
        message = msg.process
        command = get_command(message, self.instrument_name)
        status = "_action"

        if command != self.current_command:
            self.current_command = command
            self.get_logger().info(f"Get command: {command}")

            if not self.instrument_future_valid:
                self.instrument_future = self.instrument_control.make_action_async(self.current_command)
                self.instrument_future_valid = True
                status = "_action"
            else:
                status = "_error"

            call_service(self.process_client, self.get_logger(), self.instrument_name + status)
            return

        if self.instrument_future_valid and self.instrument_future.done():
            try:
                result = self.instrument_future.result()
                if result:
                    self.get_logger().info(f"Command {self.current_command} completed successfully")
                    status = "_standby"
                    if self.instrument_control.data_flag:
                        datalog = self.instrument_control.write_datalog()
                        call_service(
                            self.data_client, self.get_logger(), datalog
                        )
                else:
                    self.get_logger().error(f"Command {self.current_command} failed")
                    status = "_error"

            except Exception as e:
                self.get_logger().error(f"Exception in command {self.current_command}: {e}")
                status = "_error"

            self.instrument_future_valid = False
            call_service(self.process_client, self.get_logger(), self.instrument_name + status)

        return