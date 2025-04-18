import sys
sys.path.append('./pybcapclient')
import rclpy
import time
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from ..pybcapclient.bcapclient import BCAPClient

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
    
    def get_action(self, compare, target):
        # Find the target string in compare string
        pos = compare.find(target)
        if compare == "init":
            return "init"
        
        if pos == -1:
            return "error"

        # Find the space after the target string
        if (pos + len(target) + 1) >= len(compare):
            return "error"
        else:
            space = compare[pos + len(target) + 1:]
            pos = space.find(" ")
            if pos == -1:
                return space
            return_string = space[:pos]
            if len(return_string) <= 2:
                return "error"
            return space[:pos]
    def take2point(self, point1, point2, function):
        self.gotoPoint(10)
        self.gotoPoint(point1)
        time.sleep(0.5)
        if function.find("take") != -1:
            variable = "I10"
        else:
            variable = "I11"
        self.changeValue(variable, point2)
        self.runTask(function)
        self.gotoPoint(point1)
        self.gotoPoint(10)
    
    def make_action(self, step):
        action = self.get_action(step, "cobotta")
        try:
            if action == "init":
                self.runTask("test1/init")
            elif action == "test":
                self.gotoPoint(44)
                time.sleep(0.5)
            elif action == "take_cup_from_stock":
                self.take2point(30, 31, "test1/take_cup")
            elif action == "put_cup_to_weight":
                self.take2point(16, 15, "test1/put_cup")
            elif action == "take_cup_from_weight":
                self.take2point(16, 15, "test1/take_cup")
            elif action == "put_dose_to_weight":
                self.take2point(16, 14, "test1/put_dose")
            elif action == "take_dose_from_weight":
                self.take2point(16, 14, "test1/take_dose")
            elif action == "put_dose_to_shelf":
                self.take2point(10, 11, "test1/put_dose")
            elif action == "take_dose_from_shelf":
                self.take2point(10, 11, "test1/take_dose")
            elif action == "put_dose_to_shelf2":
                self.take2point(23, 24, "test1/put_dose")
            elif action == "take_dose_from_shelf2":
                self.take2point(23, 24, "test1/take_dose")
            elif action == "put_cup_to_arc":
                self.gotoPoint(10)
                self.gotoPoint(20)
                self.gotoPoint(21)
                time.sleep(0.5)
                self.changeValue("I11", 22)
                self.runTask("test1/put_cup")
                self.gotoPoint(21)
                self.gotoPoint(20)
                self.gotoPoint(10)
            elif action == "take_cup_from_arc":
                self.gotoPoint(10)
                self.gotoPoint(20)
                self.gotoPoint(21)
                time.sleep(0.5)
                self.changeValue("I10", 22)
                self.runTask("test1/take_cup")
                self.gotoPoint(21)
                self.gotoPoint(20)
                self.gotoPoint(10)
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
            self.valueHandle = 0

        if self.taskHandle != 0:
            self.bcap.variable_release(self.taskHandle)
            self.taskHandle = 0

        if self.robotHandle != 0:
            self.bcap.robot_release(self.robotHandle)
            HRobot = 0

        # End If
        if self.hCtrl != 0:
            self.bcap.controller_disconnect(self.hCtrl)
            self.hCtrl = 0
            
        # End If
        self.bcap.service_stop()
        print("B-CAP service Stop")