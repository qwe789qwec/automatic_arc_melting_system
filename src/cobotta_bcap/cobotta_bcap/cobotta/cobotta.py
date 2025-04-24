import sys
sys.path.append('./pybcapclient')
import rclpy
import time
from rclpy.node import Node

from ..pybcapclient.bcapclient import BCAPClient
from ros2_utils_py.service_utils import get_command

import argparse

"""
cobotta_position
p10 init
p11 take dosing on shelf
xp12 take dosing on mid shelf
xp13 p10 to p12 mid
p14 weighing dosing position
p15 weighing bowl position
P16 into weighing

P20 p1 to arc standby
P21 p2 to arc standby
P22 arc standby

P30 stock pass position
P31 stock take position

I10 take
I11 put

cobotta_task
init
weight_take_bowl
weight_put_bowl
weight_take_dose
weight_put_dose
arc_put_bowl
arc_take_bowl
shelf_take_dose
shelf_put_dose
"""

# host = "192.168.0.1"

class cobotta:

    HOME_POINT = 10
    SHELF1_END = 11
    SHELF2_P1 = 23
    SHELF2_END = 24
    WEIGHT_P1 = 16
    WEIGHT_DOSE = 14
    WEIGHT_CUP = 15
    STOCK_P1 = 30
    STOCK_END = 31
    ARC_P1 = 20
    ARC_P2 = 21
    ARC_STANDBY = 22
    TEST_POINT = 44

    TASK_INIT = "test1/init"
    TASK_TAKE_CUP = "test1/take_cup"
    TASK_PUT_CUP = "test1/put_cup"
    TASK_TAKE_DOSE = "test1/take_dose"
    TASK_PUT_DOSE = "test1/put_dose"

    VAR_TAKE = "I10"
    VAR_PUT = "I11"

    def __init__(self, host, port = 5007, timeout = 2000):
        self.host = host
        self.port = port
        self.timeout = timeout
        # open connection
        self.bcap = BCAPClient(self.host, self.port, self.timeout)

        # start b_cap Service send SERVICE_START packet
        self.bcap.service_start("")
        self.valueHandle = 0
        self.taskHandle = 0

        # set Parameter
        Name = ""
        Provider = "CaoProv.DENSO.VRC"
        Machine = "localhost"
        Option = ""

        # Connect to RC8 (RC8(VRC)provider)
        self.hCtrl = self.bcap.controller_connect(Name, Provider, Machine, Option)

        self.robotHandle = 0
        self.robotHandle = self.bcap.controller_getrobot(self.hCtrl,"Arm","")

        # set ExtSpeed Speed,Accel,Decel
        Command = "ExtSpeed"
        Speed = 75
        Accel = 50
        Decel = 50
        Param = [Speed,Accel,Decel]
        self.bcap.robot_execute(self.robotHandle,Command,Param)

    def gotoPoint(self, point):
        
        # Take Arm
        Command = "TakeArm"
        Param = [0,0]
        self.bcap.robot_execute(self.robotHandle,Command,Param)

        # motor on
        Command = "Motor"
        Param = [1,0]
        self.bcap.robot_execute(self.robotHandle,Command,Param)

        Comp = 1
        Pose = [point,"P","@0"]
        self.bcap.robot_move(self.robotHandle,Comp,Pose,"")
        # Move P,@0 P[point]

        # Give Arm
        Command = "GiveArm"
        Param = None
        self.bcap.robot_execute(self.robotHandle,Command,Param)

    def runTask(self, task):
        ### get task Object Handl
        if(self.taskHandle == 0):
            self.taskHandle = self.bcap.controller_gettask(self.hCtrl,task,"")

        #Start pro1
        #mode  1:One cycle execution, 2:Continuous execution, 3:Step forward
        mode = 1
        taskStatus = self.bcap.task_start(self.taskHandle, mode, "")
        
        status = False
        while True:
            taskStatus = self.bcap.task_execute(self.taskHandle,"GetStatus")
            if(taskStatus != 3):
                status = True
                break
        
        return status

    def changeValue(self, ioNum, value):
        # get I[1] Object Handl
        if(self.valueHandle == 0):
            self.valueHandle = self.bcap.controller_getvariable(self.hCtrl, ioNum, "")
        # write value
        self.bcap.variable_putvalue(self.valueHandle, int(value))
        # read value of I[1]
        retI = self.bcap.variable_getvalue(self.valueHandle)
        return retI
    
    def readValue(self, ioNum):
        # get I[1] Object Handl
        if(self.valueHandle == 0):
            self.valueHandle = self.bcap.controller_getvariable(self.hCtrl, ioNum, "")
        # read value
        value = self.bcap.variable_getvalue(self.valueHandle)
        return value

    def runPath(self, path, task):
        if not path:
            print("Path is empty")
            return
        path.insert(0, self.HOME_POINT)
        pathlength = len(path)
        
        for i in range(pathlength-1):
            self.gotoPoint(path[i])
            time.sleep(0.5)

        variable = self.VAR_TAKE if "take" in task else self.VAR_PUT
        self.changeValue(variable, path[-1])
        self.runTask(task)

        for i in reversed(range(pathlength-1)):
            self.gotoPoint(path[i])
            time.sleep(0.5)
    
    def make_action(self, step):
        command = get_command(step, "cobotta")
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

        try:
            if action == "init":
                self.runTask(self.TASK_INIT)
                return "standby"
            elif action == "test":
                self.gotoPoint(self.TEST_POINT)
                time.sleep(0.5)
                return "standby"
            elif action == "takeCup":
                task = self.TASK_TAKE_CUP
            elif action == "putCup":
                task = self.TASK_PUT_CUP
            elif action == "takeDose":
                task = self.TASK_TAKE_DOSE
            elif action == "putDose":
                task = self.TASK_PUT_DOSE
            
            position = token[2]
            if position == "stock":
                self.runPath([self.STOCK_P1, self.STOCK_END], task)
            elif position == "weight":
                if action.find("cup") != -1:
                    self.runPath([self.WEIGHT_P1, self.WEIGHT_CUP], task)
                else:
                    self.runPath([self.WEIGHT_P1, self.WEIGHT_DOSE], task)
            elif position == "shelf":
                self.runPath([self.SHELF1_END], task)
            elif position == "shelf2":
                self.runPath([self.SHELF2_P1, self.SHELF2_END], task)
            elif position == "arc":
                self.runPath([self.ARC_P1, self.ARC_P2, self.ARC_STANDBY], task)
            else:
                return "error"
            
        except Exception as e:
            print(f"An error occurred: {e}")
            print("Trying to reconnect to cobotta, maybe no this name")
            return "error"  
        
        return "standby"
    def __del__(self):

        # motor off
        Command = "Motor"
        Param = [0,0]
        self.bcap.robot_execute(self.robotHandle,Command,Param)

        # Give Arm
        Command = "GiveArm"
        Param = None
        self.bcap.robot_execute(self.robotHandle,Command,Param)

        # Disconnect
        if self.valueHandle != 0:
            self.bcap.variable_release(self.valueHandle)

        if self.taskHandle != 0:
            self.bcap.variable_release(self.taskHandle)

        if self.robotHandle != 0:
            self.bcap.robot_release(self.robotHandle)

        # End If
        if self.hCtrl != 0:
            self.bcap.controller_disconnect(self.hCtrl)
            
        # End If
        self.bcap.service_stop()
        print("B-CAP service Stop")