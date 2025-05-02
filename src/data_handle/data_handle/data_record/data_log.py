import os
from datetime import datetime

class DataRecord:
    def __init__(self, dir = "/home/song/Documents/ww/automatic_arc_melting_system" , folder = "datalog", file_name = None):
        self.directory = os.path.join(dir, folder)
        os.makedirs(self.directory, exist_ok=True)
        if file_name is None:
            file_name = datetime.now().strftime('%Y-%m-%d')
        self.file_name = os.path.join(self.directory, f'{file_name}.txt')
        self.last_message = None
    
    def __del__(self):
        if self.record_flag:
            current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
            with open(self.file_name, 'a') as f:
                f.write(f'{current_time} - {"end system_by_del"}\n')

    def start_record(self):
        current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        with open(self.file_name, 'a') as f:
            f.write(f'{current_time} - start record\n')
        self.record_flag = True
    
    def end_record(self):
        current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        with open(self.file_name, 'a') as f:
            f.write(f'{current_time} - end record\n')
        self.record_flag = False

    def file_Write(self, data):
        if data != self.last_message:
            self.last_message = data
            current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
            with open(self.file_name, 'a') as f:
                f.write(f'{current_time} - {data}\n')