from pathlib import Path
import json
import os

BASE_DIR = Path(__file__).parent.resolve()

# ---- load json config ----
CONFIG_PATH = BASE_DIR / "streamlit_config.json"
with open(CONFIG_PATH, "r") as f:
    CONFIG = json.load(f)

# ---- stock ----
STOCK_PATH = (BASE_DIR / CONFIG["files"]["stock"]["path"]).resolve()

# ---- sequence ----
SEQUENCE_DIR = (BASE_DIR / CONFIG["files"]["sequence"]["dir"]).resolve()
SEQUENCE_DIR.mkdir(parents=True, exist_ok=True)

SEQUENCE_FILENAME = CONFIG["files"]["sequence"]["filename"]
SEQUENCE_PATH = SEQUENCE_DIR / SEQUENCE_FILENAME

# ---- ROS2 ----
SETUP_BASH = Path(
    os.environ.get(
        "ARC_SETUP_BASH",
        CONFIG["ros2"]["setup_bash"]
    )
).expanduser().resolve()
