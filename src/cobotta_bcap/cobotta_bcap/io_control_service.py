from tcp_format.srv import CobottaBcap
from .pybcapclient.bcapclient import BCAPClient

import rclpy
from rclpy.node import Node

class CobottaActionService(Node):

    def __init__(self):
        super().__init__('cobotta_action')
        self.srv = self.create_service(CobottaBcap, 'cobotta_bcap', self.cobotta_act)

    def cobotta_act(self, request, response):
        self.get_logger().info('Incoming request\naction: %s target: %s' % (request.action, request.target))
        response.status = 'init status'
        response.message = 'init msg'

        host = "192.168.0.1"
        port = 5007
        timeout = 2000

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
        # get IO128 Object Handl
        IOHandl = 0
        
        ioact = request.action + request.target
        IOHandl = m_bcapclient.controller_getvariable(hCtrl, ioact, "")
        # read value of I[1]
        retIO = m_bcapclient.variable_getvalue(IOHandl)
        print("Read Variable" + ioact + " = %s" % retIO)

        # read value of IO[128]
        # switching IO state
        newval = not(retIO)
        # write value of IO[128]
        m_bcapclient.variable_putvalue(IOHandl, newval)
        print("Write Variable :newval = %s" % newval)
        # read value of IO[128]
        retIO = m_bcapclient.variable_getvalue(IOHandl)
        print("Read Variable" + ioact + " = %s" % retIO)

        # read and write value of IO[130]-[145]
        # get Object Handl
        IOWHandl = 0
        IOWHandl = m_bcapclient.controller_getvariable(hCtrl, "IOW130", "")

        # read value
        retIOW = m_bcapclient.variable_getvalue(IOWHandl)
        print("Read Variable IOW130 = %s" % retIOW)

        # write value
        writevalue = -1  # writevalue = 0b1111111111111111
        m_bcapclient.variable_putvalue(IOWHandl, writevalue)
        # read value
        retIOW = m_bcapclient.variable_getvalue(IOWHandl)
        print("Read Variable IOW130 = %s" % retIOW)

        # Disconnect
        if(IOHandl != 0):
            m_bcapclient.variable_release(IOHandl)
            print("Release" + ioact)
        if(IOWHandl != 0):
            m_bcapclient.variable_release(IOWHandl)
            print("Release IOW130")
        # End If
        if(hCtrl != 0):
            m_bcapclient.controller_disconnect(hCtrl)
            print("Release Controller")
        # End If
        m_bcapclient.service_stop()
        print("B-CAP service Stop")

        response.status = request.action
        response.message = request.target
        return response


def main(args=None):
    rclpy.init(args=args)

    cobotta_action = CobottaActionService()

    rclpy.spin(cobotta_action)

    rclpy.shutdown()


if __name__ == '__main__':
    main()