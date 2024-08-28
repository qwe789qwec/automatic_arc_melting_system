import rclpy
from rclpy.node import Node
from msg_format.srv import ProcessService

import sys
import os
from datetime import datetime
from .data_record.data_record import DataRecord

class data_Service(Node):

    def __init__(self, file_prefix):
        super().__init__('data_service')
        self.datadecorder = DataRecord(file_prefix)
        self.srv = self.create_service(ProcessService, 'write_data', self.data_hndl)

    def data_hndl(self, request, response):
        write_data = request.action
        self.datadecorder.fileWrite(write_data)
        response.result = 'Success'

        return response


def main(args=None):
    rclpy.init(args=args)

    # argvからファイル名の接頭辞を取得
    # if len(sys.argv) > 1:
    #     file_prefix = sys.argv[1]
    # else:
    #     # file_prefix = 'default_prefix'
    file_prefix = "Expt_" + datetime.now().strftime('%Y-%m-%d %H:%M:%S')

    data_service = data_Service(file_prefix)

    rclpy.spin(data_service)
    data_service.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()