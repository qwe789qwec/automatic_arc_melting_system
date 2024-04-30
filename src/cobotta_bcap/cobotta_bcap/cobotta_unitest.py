import sys
import rclpy
import time
from rclpy.node import Node

from msg_format.srv import ProcessService
from msg_format.msg import ProcessMsg

from .pybcapclient.bcapclient import BCAPClient

import argparse

host = "192.168.0.1"
port = 5007
timeout = 2000

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

def cobotta_task(task):
    ### Connection processing of tcp communication
    m_bcapclient = BCAPClient(host,port,timeout)
    print("Open Connection")

    ### start b_cap Service
    m_bcapclient.service_start("")
    print("Send SERVICE_START packet")

    ### set Parameter
    Name = ""
    Provider="CaoProv.DENSO.VRC"
    Machine = ("localhost")
    Option = ("")

    ### Connect to RC8 (RC8(VRC)provider)
    hCtrl = m_bcapclient.controller_connect(Name,Provider,Machine,Option)
    print("Connect RC8")
    ### get task(pro1) Object Handl
    HTask = 0
    HTask = m_bcapclient.controller_gettask(hCtrl,task,"")

    #Start pro1
    #mode  1:One cycle execution, 2:Continuous execution, 3:Step forward
    mode = 1
    hr = m_bcapclient.task_start(HTask,mode,"")

    print("into loop")
    while True:
        TaskStatus = m_bcapclient.task_execute(HTask,"GetStatus")
        # print("TaskStatus : ",TaskStatus)
        if(TaskStatus != 3):
            break
    print("out loop")

    # Disconnect
    if(HTask != 0):
        m_bcapclient.task_release(HTask)
        print("Release Pro1")
    #End If
    if(hCtrl != 0):
        m_bcapclient.controller_disconnect(hCtrl)
        print("Release Controller")
    #End If
    m_bcapclient.service_stop()
    print("B-CAP service Stop")

def get_action(compare, target):
    # Find the target string in compare string
    pos = compare.find(target)
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

class CobottaClient(Node):

    def __init__(self):
        super().__init__('cobotta_client')
        self.cli = self.create_client(ProcessService, 'process_service')
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self.req = ProcessService.Request()

    def send_request(self, message):
        self.req.action = message
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()

class CobottaSubscriber(Node):

    def __init__(self):
        super().__init__('cobotta_subscriber')
        self.subscription = self.create_subscription(
            ProcessMsg,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.last_process = "cobotta init"

    def listener_callback(self, msg):
        # self.get_logger().info('I heard: "%s"' % msg.process)
        if msg.process.startswith("init"):
            action = "init"
        else:
            action = get_action(msg.process, "cobotta")
        
        if msg.process != self.last_process:
            self.last_process = msg.process
            if action == "error":
                print("error cannot make action")
            else:
                print(f"action: {action}")
                try:
                    cobotta_task(action)
                    cobotta_client = CobottaClient()
                    response = cobotta_client.send_request("cobotta standby")
                    cobotta_client.get_logger().info('I heard: "%s"' % response.result)
                    cobotta_client.destroy_node()
                except Exception as e:
                    print(f"An error occurred: {e}")
                    print("Trying to reconnect to cobotta, maybe no this name")
                time.sleep(1.5)

def main(args=None):

    rclpy.init(args=args)

    parser = argparse.ArgumentParser(description='Cobotta Subscriber Node')
    parser.add_argument('--test', type=str, default='default_topic', help='Specify the ROS topic name')
    parsed_args = parser.parse_args(args)

    if parsed_args.test != 'default_topic':
        print(f"get parsed: {parsed_args.test}")
        cobotta_task(str(parsed_args.test))
    time.sleep(1.5)
    
    cobotta_subscriber = CobottaSubscriber()

    rclpy.spin(cobotta_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    cobotta_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()