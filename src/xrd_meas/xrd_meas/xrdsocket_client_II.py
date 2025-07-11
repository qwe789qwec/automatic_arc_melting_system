import socket
import time
import sys
import datetime

# Server configuration
HOST = '192.168.0.91'  # Replace with the Windows machine's IP address
PORT = 65432            # Same port as the server

def send_command(command):
    """Send a command to the server."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        client_socket.connect((HOST, PORT))
        client_socket.sendall(command.encode('utf-8'))  # Send command
        response = client_socket.recv(1024).decode('utf-8')  # Get response
        print(f"Response: {response}")
        return response

if __name__ == "__main__":
    #now = time.strftime("%y%m%d_%H%M%S_")
    now = time.strftime("%Y%b%d_%H%M%S_")
    filename = now + sys.argv[1] +".raw"

    # start Miniflex program
    send_command("move 55 130")
    time.sleep(0.1)
    send_command("doubleclick")
    time.sleep(2.0)

    # edit filename
    send_command("move 260 210")
    time.sleep(0.1)
    send_command("doubleclick")
    time.sleep(0.1)
    send_command(f"type {filename}")
    time.sleep(0.1)

    # execute the measurement
    send_command("move 30 75")
    time.sleep(0.5)
    send_command("click")
    time.sleep(3.0)

    # ok to "Are you ready for equipment?"
    # send_command("move 880 580")
    time.sleep(10.0)
    # send_command("click")
    # time.sleep(0.5)
    # send_command("click")
    # time.sleep(0.5)
    # send_command("click")
    # time.sleep(0.5)

    # wait until meas. finishes
    # wait until the "右コンソール" window is closed
    while True:
        response = send_command("monitor_window")  # Ask the server to monitor the window
        if response is None:  # Handle case where no response is received
            print("No response from server. Retrying...")
            time.sleep(5)
            send_command("move 500 500")# keep monitor awake
            continue
        if "Meas. finished" in response:  # Check if the response contains "Meas. finished"
            print("Measurement is finished. Proceeding with the next steps...")
            break
        print("Waiting for the window to close...")
        time.sleep(5)  # Wait before checking again

    # close MiniFlex Guidance
    send_command("move 593 15")
    time.sleep(0.1)
    send_command("click")
    time.sleep(2.0)
    send_command("move 560 555")
    time.sleep(0.1)
    send_command("click")
    time.sleep(3.0)
    # send_command("press_right")
    # time.sleep(0.1)
    # send_command("press_enter")
    # time.sleep(0.1)

    send_command("finished")
    time.sleep(0.1)

    # memo it takes around 1 min to turn on the lamp.