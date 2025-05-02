import sys
sys.path.append('./pybcapclient')
import time

from data_log import DataRecord
from elabftw import Elabftw
from ros2_utils_py.service_utils import get_command


class DataHandle:

    def __init__(self):
        self.systemlog = DataRecord(folder="systemlog")
        self.datadecorder = DataRecord(folder="datalog")
        self.elabftw = Elabftw(
            api_url="https://elabftw.com/api",
            api_key="your_api_key_here",
            local_backup=True,
            backup_dir="experiment_logs"
        )

    def record_data(self, data):
        self.datadecorder.file_Write(data)
        self.systemlog.file_Write(data)

    def make_action(self, step):
        command = get_command(step, "record")
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

        if action == "init":
            self.systemlog.start_record()
            self.datadecorder.start_record()
            return "standby"
        elif action == "test":
            self.datadecorder.file_Write("test")
            self.systemlog.file_Write("test")
            return "standby"
        elif action == "vedio":
            state = token[2]
            if state == "start":
                self.elabftw.start_record()
            elif state == "stop":
                self.elabftw.stop_record()
            else:
                return "error"      
        else:
            return "error"
           
    def __del__(self):

        self.systemlog.end_record()
        self.datadecorder.end_record()
        self.elabftw.close()