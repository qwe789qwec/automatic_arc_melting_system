import sys
sys.path.append('./pybcapclient')
import time

from .data_log import DataRecord
from .video_record import camera
from .elabftw import ElabFTW
from ros2_utils_py.service_utils import get_command


class DataHandle:

    def __init__(self):
        self.datalog = DataRecord(folder="datalog")
        self.camera = camera()
        self.record_flag = False
        self.title = None
        with open("api_key.txt", "r", encoding="utf-8") as f:
            read_api_key = f.read().strip()
        self.elabftw = ElabFTW(
            api_url="https://192.168.0.90/api/v2",
            api_key=read_api_key
        )

    def record_data(self, data):
        self.datalog.file_Write(data)
        # added since the same in make_action does not work
        if self.record_flag:
            print(f"[DEBUG] elabftw.record_data() called from record_data() with: {data}")
            self.elabftw.record_data(data)

    def make_action(self, step):
        command = get_command(step, "record")

        # if self.record_flag:
        #     self.datalog.file_Write(step) # write in datalog
        #     self.elabftw.record_data(step) # collect metadata info for elabftw

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
            self.datalog.file_Write("===============START=================")
            self.datalog.file_Write(step)
            self.elabftw.create_experiment(token[2])
        elif action == "off":
            self.record_flag = False
            self.datalog.file_Write("================END==================")
            self.elabftw.update_metadata() # update metadata at elabftw

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
        elif action == "video":
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