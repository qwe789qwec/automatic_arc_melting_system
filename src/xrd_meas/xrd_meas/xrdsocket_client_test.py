# This is to test if this node runs successfully
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

    send_command("move 55 130")
    time.sleep(3.0)
    send_command("move 260 210")
    time.sleep(3.0)
    send_command("move 30 75")
    time.sleep(3.0)

    send_command("finished")
    time.sleep(0.1)

