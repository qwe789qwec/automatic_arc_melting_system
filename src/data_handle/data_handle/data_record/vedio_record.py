
class VedioRecord:
    def __init__(self, video_path: str):
        self.video_path = video_path
        self.video_name = video_path.split("/")[-1]
        self.video_id = self.video_name.split(".")[0]
        self.video_type = self.video_name.split(".")[-1]
        self.video_size = 0
        self.video_duration = 0
        self.video_fps = 0
        self.video_width = 0
        self.video_height = 0
    
    def start():
        pass

    def end():
        pass

    def __del__(self):
        self.video_path = None
        self.video_name = None
        self.video_id = None
        self.video_type = None
        self.video_size = 0
        self.video_duration = 0
        self.video_fps = 0
        self.video_width = 0
        self.video_height = 0