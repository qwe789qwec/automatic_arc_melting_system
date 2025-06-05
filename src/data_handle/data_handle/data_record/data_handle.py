import sys
sys.path.append('./pybcapclient')
import time

from .data_log import DataRecord
from .vedio_record import camera
# from .elabftw import ElabFTW
from ros2_utils_py.service_utils import get_command


class DataHandle:

    def __init__(self):
        self.datalog = DataRecord(folder="datalog")
        self.camera = camera()
        self.record_flag = False
        # with open("api_key.txt", "r", encoding="utf-8") as f:
        #     read_api_key = f.read().strip()
        # self.elabftw = ElabFTW(
        #     api_url="https://nfm-cpu.local/api",
        #     api_key=read_api_key
        # )

    def record_data(self, data):
        self.datalog.file_Write(data)

    def make_action(self, step):
        command = get_command(step, "record")
        if self.record_flag:
            self.datalog.file_Write(step)
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
            self.datalog.start_record()
            return "standby"
        elif action == "on":
            self.record_flag = True
            self.datalog.file_Write(step)
        elif action == "off":
            self.record_flag = False
        elif action == "test":
            self.datalog.file_Write("test")
            # self.elabftw.create_experiment(
            #     title="test",
            #     body="test",
            #     category_id=1
            # )
            # self.elabftw.add_data(
            #     data="test",
            #     description="test"
            # )
            self.camera.start_recording()
            time.sleep(5)
            self.camera.stop_recording()
            return "standby"
        elif action == "vedio":
            state = token[2]
            if state == "start":
                if len(token) > 3:
                    filename = token[3]
                    self.camera.start_recording(filename)
                else:
                    self.camera.start_recording()
            elif state == "stop":
                self.camera.stop_recording()
            else:
                return "error"      
        else:
            self.datalog.file_Write(action)
            return "standby"
           
    def __del__(self):
        self.datalog.end_record()
        # self.elabftw.close()