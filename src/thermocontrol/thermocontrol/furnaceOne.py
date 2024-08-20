from msg_format.srv import TestSrv

import rclpy
from rclpy.node import Node

import serial
import time

ser = serial.Serial(
    port='/dev/ttyUSB0',    # 根據實際情況替換為你的設備名稱
    baudrate=9600,          # 波特率
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1               # 讀取的超時時間
)

class MinimalService(Node):

    def __init__(self):
        super().__init__('minimal_service')
        self.srv = self.create_service(TestSrv, 'fuck', self.fuck)

    def fuck(self, request, response):
        if ser.is_open and request.action_1.startswith("init"):
            response.result = "connect"

        elif request.action_1.startswith("send"):
            try:
                hex_data = request.action_2
                # hex_data = '01030100000185F6'
                data_to_send = bytes.fromhex(hex_data)
                crc_value = self.crc16(data_to_send)
                crc_bytes = crc_value.to_bytes(2, byteorder='little')
                data_with_crc = data_to_send + crc_bytes
                ser.write(data_with_crc)

                time.sleep(3)

                received_data = ser.read(ser.in_waiting or 1)
                response.result = received_data.hex()

            except Exception as e:
                response.result = "error" + str(e)

        elif request.action_1.startswith("close"):
            ser.close()
            response.result = "success and close"



        return response
    
    def crc16(self, data: bytes) -> int:
        polynomial = 0xA001
        crc = 0xFFFF  # CRC 初始值

        for byte in data:
            crc ^= byte  # 將當前字節 XOR 到 CRC 上
            for _ in range(8):  # 處理每一位
                if crc & 0x0001:  # 檢查最低位
                    crc = (crc >> 1) ^ polynomial  # 右移並 XOR 上多項式
                else:
                    crc >>= 1  # 右移
                crc &= 0xFFFF  # 確保 CRC 在 16 位範圍內

        return crc


def main(args=None):
    rclpy.init(args=args)

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()


if __name__ == '__main__':
    main()