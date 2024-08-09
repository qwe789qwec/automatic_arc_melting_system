from msg_format.srv import TestSrv
from .pybcapclient.bcapclient import BCAPClient

import rclpy
from rclpy.node import Node

host = "192.168.0.11"
port = 5007
timeout = 2000

class CobottaActionService(Node):

    def __init__(self):
        super().__init__('cobotta_action')
        self.srv = self.create_service(TestSrv, 'test_srv', self.cobotta_act)

    def cobotta_act(self, request, response):
        self.get_logger().info('Incoming request\nactionOne: %s actionTwo: %s' % (request.action_1, request.action_2))
        response.result = 'init status'

        # Connection processing of tcp communication
        m_bcapclient = BCAPClient(host, port, timeout)
        print("Open Connection")

        # start b_cap Service
        m_bcapclient.service_start("")
        print("Send SERVICE_START packet")

        # set Parameter
        Name = ""
        Provider = "CaoProv.DENSO.VRC"
        Machine = "localhost"
        Option = ""

        # Connect to RC8 (RC8(VRC)provider)
        hCtrl = m_bcapclient.controller_connect(Name, Provider, Machine, Option)
        print("Connect RC8")

        ioNum = request.action_1
        
        # get I[1] Object Handl
        IHandl = 0
        IHandl = m_bcapclient.controller_getvariable(hCtrl, ioNum, "")
        # read value of I[1]
        retI = m_bcapclient.variable_getvalue(IHandl)
        print("Read Variable" + ioNum + "= %d" % retI)
        # Generate random value
        newval = int(request.action_2)
        # write value of I[1]
        m_bcapclient.variable_putvalue(IHandl, newval)
        print("Write Variable :newval = %d" % newval)
        # read value of I[1]
        retI = m_bcapclient.variable_getvalue(IHandl)
        print("Read Variable I[1] = %d" % retI)

        # Disconnect
        if(IHandl != 0):
            m_bcapclient.variable_release(IHandl)
            print("Release IHandl")

        # End If
        if(hCtrl != 0):
            m_bcapclient.controller_disconnect(hCtrl)
            print("Release Controller")
        # End If
        m_bcapclient.service_stop()
        print("B-CAP service Stop")

        response.result = "Read Variable I[1] = %d" % retI
        return response


def main(args=None):
    rclpy.init(args=args)

    cobotta_action = CobottaActionService()

    rclpy.spin(cobotta_action)

    rclpy.shutdown()


if __name__ == '__main__':
    main()