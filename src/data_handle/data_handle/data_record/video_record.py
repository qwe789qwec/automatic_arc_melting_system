import time
import cv2
import os
import threading
from datetime import datetime

class camera:
    def __init__(self, dir = "/home/song/Documents/ww/automatic_arc_melting_system", folder = "video"):
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
        self.folder = os.path.join(dir, folder)

    def start_recording(self, filename=None):
        # Ensure frame dimensions match the video writer
        current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        if filename is None:
            filename = current_time
        else:
            filename = f"{current_time}_{filename}"
        video_path = os.path.join(self.folder, filename)
        self.out = cv2.VideoWriter(video_path + '.avi', self.fourcc, 15.0, (self.frame_width, self.frame_height))
        self.recording = True
        
        # Start the recording in a new thread
        self.recording_thread = threading.Thread(target=self.record_video)
        self.recording_thread.start()

    def record_video(self):
        while self.recording:
            ret, frame = self.camera.read()
            if not ret:
                break

            # Write the frame to the output file
            self.out.write(frame)

            # Show the frame in the window (optional)
            # cv2.imshow('USB Camera Feed', frame)

            # if cv2.waitKey(1) & 0xFF == ord('q'):
            #     self.stop_recording()

    def stop_recording(self):
        if self.recording:
            self.recording = False
            self.recording_thread.join()  # Wait for the recording thread to finish
            
            # Flush the frames to ensure they are written before releasing
            if self.out is not None:
                self.out.release()
                self.out = None
            # cv2.destroyAllWindows()

    def cleanup(self):
        if self.camera.isOpened():
            self.camera.release()
        if self.out is not None:
            self.out.release()
            self.out = None
        # cv2.destroyAllWindows()

    def __del__(self):
        self.cleanup()
        print("camera Stop")