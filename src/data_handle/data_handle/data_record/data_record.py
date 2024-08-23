import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from msg_format.msg import ProcessMsg  # インポートを追加
import sys
import os
from datetime import datetime

class DataRecord:
    def __init__(self, file_prefix = None):
        self.directory = "/home/song/Documents/ww/automatic_arc_melting_system/datalog"
        os.makedirs(self.directory, exist_ok=True)
        self.file_flag = False
        self.make_file(file_prefix)
        self.last_message = None

    def fileWrite(self, data):
        if data == "finished":
            self.file_flag = False
        
        if data != self.last_message:
            self.last_message = data
            current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')  # 获取当前时间
            if self.filename:
                with open(self.filename, 'a') as f:
                    f.write(f'{current_time} - {data}\n')

    def make_file(self, file_prefix = None):
        self.current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        if not file_prefix:
            self.file_prefix = "Expt_" + self.current_time
        else:    
            self.file_prefix = file_prefix
        self.filename = os.path.join(self.directory, f'{self.file_prefix}.txt')
        self.file_flag = True