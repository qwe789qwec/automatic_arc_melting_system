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
        if command in ["none", "error"]:
            return command

        action, position = "none", "none"
        tokens = command.split("_")

        # command validation
        if command in ["test", "init"]:
            action = command
        elif len(tokens) >= 2:
            action = tokens[1]
            if len(tokens) >= 3:
                position = tokens[2]
        else:
            return "error"

        # === action ===
        if action == "init":
            self.instrumentp.sendall(f"{self.NO_1} {self.ZERO}\n".encode())
            print("Instrument initialized")
            return "standby"

        elif action == "action2":
            if position == self.NO_2:
                print(f"Action 2 at {self.NO_2}")
            elif position == self.NO_3:
                print(f"Action 2 at {self.NO_3}")
            else:
                print(f"Unknown position for action2: {position}")

        elif action == "test":
            print("Instrument test action executed")

        # === wait for response ===
        try:
            data = self.instrumentp.recv(1024)
            if data:
                response = data.decode()
                print(f"Response from instrument: {response}")
        except socket.timeout:
            print("No response from instrument (timeout)")

        return "standby"
    
    def __del__(self):
        self.instrumentp.close()