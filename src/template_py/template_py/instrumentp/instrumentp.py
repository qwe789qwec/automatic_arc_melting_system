import sys
sys.path.append('./pybcapclient')
import rclpy
import time
from rclpy.node import Node
import socket

from ros2_utils_py.service_utils import get_command

import argparse

class instrumentp:

    ZERO = 0
    ONE = 1
    TWO = 2

    NO_1 = "I[1]"
    NO_2 = "I[2]"
    NO_3 = "I[3]"

    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.instrumentp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.instrumentp.connect((self.host, self.port))
    
    def make_action(self, step):
        command = get_command(step, "instrumentp")
        action = "none"
        if command == "test" or command == "init":
            action = command
        elif command == "none":
            return "none"
        elif command == "error":
            return "error"

        token = command.split("_")
        if len(token) < 2 and action == "none":
            return "error"
        
        action = token[1]

        position = token[2]

        if action == "init":
            self.instrumentp.send(f"{self.NO_1} {self.ZERO}".encode())
            print("Instrument initialized")
            return "standby"
        elif action == "action2":
            if position == self.NO_2:
                # self.instrumentp.send(f"{self.NO_2} {self.TWO}".encode())
                print(f"Action 2 at {self.NO_2}")
            elif position == self.NO_3:
                # self.instrumentp.send(f"{self.NO_3} {self.TWO}".encode())
                print(f"Action 2 at {self.NO_3}")
        elif action == "test":
            # self.instrumentp.send(f"{self.NO_2} {self.ONE}".encode())
            print("Instrument test action executed")
        
        data = self.instrumentp.recv(1024)
        if data:
            response = data.decode()
            print(f"Response from instrument: {response}")

        return "standby"
    def __del__(self):
        self.instrumentp.close()