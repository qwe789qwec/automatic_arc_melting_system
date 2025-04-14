import streamlit as st
import subprocess
import os
import signal

# Initialize session state for processes
if 'processes' not in st.session_state:
    st.session_state.processes = []

def run_ros2():
    # Combined command to source environment and run ROS2 node in one shell
    command = (
        'bash -c "source /home/song/Documents/ww/automatic_arc_melting_system/install/setup.bash && '
        'ros2 run main_process MainProcess"'
    )
    process = subprocess.Popen(
        command,
        shell=True,
        preexec_fn=os.setsid  # Create new process group
    )
    st.session_state.processes.append(process)
    st.write("ROS2 process started with PID:", process.pid)

def stop_processes():
    # Terminate processes using their process groups
    for process in st.session_state.processes:
        if process.poll() is None:  # Check if still running
            try:
                os.killpg(os.getpgid(process.pid), signal.SIGTERM)
            except ProcessLookupError:
                pass  # Process already terminated
    st.session_state.processes.clear()
    st.write("All processes terminated")

# Streamlit interface
st.title("Run automatic arc-melting synthesis")

col1, col2 = st.columns(2)
with col1:
    if st.button("Start ROS2 Process"):
        run_ros2()

with col2:
    if st.button("Stop All Processes"):
        stop_processes()