import time
import cv2
import threading

class camera:
    def __init__(self):
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

    def start_recording(self):
        # Ensure frame dimensions match the video writer
        self.out = cv2.VideoWriter('output.avi', self.fourcc, 15.0, (self.frame_width, self.frame_height))
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
        self.cleanup()

    def cleanup(self):
        if self.camera.isOpened():
            self.camera.release()
        if self.out is not None:
            self.out.release()
            self.out = None
        # cv2.destroyAllWindows()
        
    def get_action(self, compare, target):
        # Find the target string in compare string
        pos = compare.find(target)
        if pos == -1:
            return "error 0"

        # Find the space after the target string
        if (pos + len(target) + 1) >= len(compare):
            return "error 1"
        else:
            space = compare[pos + len(target) + 1:]
            pos = space.find(" ")
            if pos == -1:
                return space
            return_string = space[:pos]
            if len(return_string) <= 2:
                return "error 2"
            return space[:pos]
    
    def make_action(self, step):
        action = self.get_action(step, "camera")
        if action == "init":
            time.sleep(0.5)
        elif action == "start":
            self.start_recording()
        elif action == "stop":
            self.stop_recording()
        else:
            return action 
        
        return "standby"

    def __del__(self):
        self.cleanup()
        print("camera Stop")