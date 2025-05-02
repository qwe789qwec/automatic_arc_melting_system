import sys
sys.path.append('./pybcapclient')
import time

from data_log import DataRecord
from vedio_record import camera
from elabftw import Elabftw
from ros2_utils_py.service_utils import get_command


class DataHandle:

    def __init__(self):
        self.systemlog = DataRecord(folder="systemlog")
        self.datadecorder = DataRecord(folder="datalog")
        self.camera = camera()
        with open("api_key.txt", "r", encoding="utf-8") as f:
            read_api_key = f.read().strip()
        self.elabftw = Elabftw(
            api_url="https://nfm-cup.local/api",
            api_key=read_api_key
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
            self.elabftw.create_experiment(
                title="test",
                body="test",
                category_id=1
            )
            self.elabftw.add_data(
                data="test",
                description="test"
            )
            self.camera.start_recording()
            time.sleep(5)
            self.camera.stop_recording()
            return "standby"
        elif action == "vedio":
            state = token[2]
            if state == "start":
                self.camera.start_recording()
            elif state == "stop":
                self.camera.stop_recording()
            else:
                return "error"      
        else:
            return "error"
           
    def __del__(self):
        self.systemlog.end_record()
        self.datadecorder.end_record()
        self.elabftw.close()