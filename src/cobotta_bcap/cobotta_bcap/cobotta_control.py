import sys
import rclpy
import time
from rclpy.node import Node

from msg_format.msg import ProcessMsg
from msg_format.srv import ProcessService

from .pybcapclient.bcapclient import BCAPClient

host = "192.168.0.1"
port = 5007
timeout = 2000

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

    def listener_callback(self, msg):
        # self.get_logger().info('I heard: "%s"' % msg.process)
        global count
        if msg.process.startswith("init") and count == 0:
            cobotta_task("init")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count = 3
            
        elif msg.process.startswith("step 1") and count == 1:
            cobotta_task("take_bowl")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1

        elif msg.process.startswith("step 3") and count == 2:
            cobotta_task("put_bowl")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1

        elif msg.process.startswith("step 5") and count == 3:
            cobotta_task("take_dose")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1

        elif msg.process.startswith("step 7") and count == 4:
            cobotta_task("put_l")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1

        elif msg.process.startswith("step 9") and count == 5:
            cobotta_task("take_l")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1
        
        elif msg.process.startswith("step 11") and count == 6:
            cobotta_task("put_dose")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1
        
        elif msg.process.startswith("step 13") and count == 7:
            cobotta_task("take_bowl")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1

        elif msg.process.startswith("step 15") and count == 8:
            cobotta_task("put_bowl")
            cobotta_client = CobottaClient()
            message = "cobotta ok"
            response = cobotta_client.send_request(message)
            cobotta_client.get_logger().info('I heard: "%s"' % response.result)
            cobotta_client.destroy_node()
            time.sleep(1.5)
            count += 1
        
        elif msg.process.startswith("Standby"):
            count = 0


def main(args=None):
    rclpy.init(args=args)
    global count
    count  = 0

    cobotta_subscriber = CobottaSubscriber()

    rclpy.spin(cobotta_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    cobotta_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()