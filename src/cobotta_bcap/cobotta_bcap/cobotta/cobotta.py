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

        # set Parameter
        Name = ""
        Provider = "CaoProv.DENSO.VRC"
        Machine = "localhost"
        Option = ""

        # Connect to RC8 (RC8(VRC)provider)
        self.hCtrl = self.bcap.controller_connect(Name, Provider, Machine, Option)

    def makeTask(self, task):
        ### get task(pro1) Object Handl
        self.handle = 0
        self.handle = self.bcap.controller_gettask(self.hCtrl,task,"")

        #Start pro1
        #mode  1:One cycle execution, 2:Continuous execution, 3:Step forward
        mode = 1
        taskHandle = self.bcap.task_start(self.hCtrl, mode, "")

        print("into loop")
        while True:
            TaskStatus = self.bcap.task_execute(self.handle,"GetStatus")
            # print("TaskStatus : ",TaskStatus)
            if(TaskStatus != 3):
                break
        print("out loop")
        return TaskStatus

    def changeValue(self, ioNum, value):
        # get I[1] Object Handl
        self.handle = 0
        self.handle = self.bcap.controller_getvariable(self.hCtrl, ioNum, "")
        # write value
        self.bcap.variable_putvalue(self.handle, int(value))
        # read value of I[1]
        retI = self.bcap.variable_getvalue(self.handle)
        return retI
    
    def readValue(self, ioNum):
        # get I[1] Object Handl
        self.handle = 0
        self.handle = self.bcap.controller_getvariable(self.hCtrl, ioNum, "")
        # read value
        value = self.bcap.variable_getvalue(self.handle)
        return value

    def __del__(self):
        # Disconnect
        if(self.handle != 0):
            self.bcap.variable_release(self.handle)
            print("Release IHandl")

        # End If
        if(self.hCtrl != 0):
            self.bcap.controller_disconnect(self.hCtrl)
            print("Release Controller")
        # End If
        self.bcap.service_stop()
        print("B-CAP service Stop")