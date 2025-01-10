import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile
from msg_format.msg import ProcessMsg

import time

import cv2
import threading

class CameraRecorder(Node):
    def __init__(self):
        super().__init__('camera_recorder')

        self.subscription = self.create_subscription(
            ProcessMsg,
            'camera_control',
            self.command_callback,
            QoSProfile(depth=10)
        )

        self.camera = cv2.VideoCapture(0, cv2.CAP_V4L2)
        if not self.camera.isOpened():
            self.get_logger().error("Error: Camera not found.")
            exit()

        self.camera.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
        self.camera.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
        self.frame_width = int(self.camera.get(cv2.CAP_PROP_FRAME_WIDTH))
        self.frame_height = int(self.camera.get(cv2.CAP_PROP_FRAME_HEIGHT))
        self.fourcc = cv2.VideoWriter_fourcc(*'MJPG')  # Changed to MJPG codec
        self.out = None
        self.recording = False
        self.recording_thread = None

    def command_callback(self, msg):
        command = msg.process

        if command == "start" and not self.recording:
            self.start_recording()
        elif command == "end" and self.recording:
            self.stop_recording()

    def start_recording(self):
        # Ensure frame dimensions match the video writer
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 15.0, (self.frame_width, self.frame_height))
        self.recording = True
        self.get_logger().info("Recording started.")
        
        # Start the recording in a new thread
        self.recording_thread = threading.Thread(target=self.record_video)
        self.recording_thread.start()

    def record_video(self):
        while self.recording:
            ret, frame = self.camera.read()
            if not ret:
                self.get_logger().error("Error: Unable to read from camera.")
                break

            # Write the frame to the output file
            self.out.write(frame)

            # Show the frame in the window (optional)
            cv2.imshow('USB Camera Feed', frame)

            if cv2.waitKey(1) & 0xFF == ord('q'):
                self.stop_recording()

    def stop_recording(self):
        if self.recording:
            self.recording = False
            self.recording_thread.join()  # Wait for the recording thread to finish
            
            # Flush the frames to ensure they are written before releasing
            if self.out is not None:
                self.out.release()
            self.get_logger().info("Recording stopped.")
            cv2.destroyAllWindows()

    def cleanup(self):
        if self.camera.isOpened():
            self.camera.release()
        if self.out is not None:
            self.out.release()
        cv2.destroyAllWindows()

def main(args=None):
    rclpy.init(args=args)
    camera_recorder = CameraRecorder()

    try:
        rclpy.spin(camera_recorder)
    except KeyboardInterrupt:
        pass
    finally:
        camera_recorder.cleanup()
        camera_recorder.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
