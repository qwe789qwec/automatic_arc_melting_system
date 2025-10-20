import time
import threading
import concurrent.futures
import rclpy
from rclpy.node import Node
from rclpy.client import Client
from rclpy.task import Future
from rclpy.logging import get_logger
from msg_format.srv import ProcessService


def call_service(
        client: Client,
        logger,
        action: str,
        timeout: float = 6.0) -> bool:

    service_name = client.srv_name

    # Wait for service to be available
    if not client.wait_for_service(timeout_sec=timeout):
        logger.error(f"{service_name} service not available after timeout")
        return False
    
    # Create request
    request = ProcessService.Request()
    request.action = action
    
    # Send request
    future = client.call_async(request)
    
    ret = rclpy.spin_until_future_complete(client, future, timeout_sec=timeout)

    if ret == rclpy.FutureReturnCode.SUCCESS:
        logger.info(f"Service {service_name} call succeeded")
        return True
    else:
        logger.error(f"Service {service_name} call timed out")
        return False

def get_command(command: str, device_id: str) -> str:
    """
    Parse command to extract device_specific command.
    
    Args:
        command: The full command string
        device_id: The device ID to look for
        
    Returns:
        str: Extracted command or status string
    """
    if command == "test" or command == "init":
        return command
    
    pos = command.find(device_id)
    if pos == -1:  # -1 is Python's equivalent to std::string::npos
        return "none"
    
    # Get the position of the underscore
    underscore_pos = pos + len(device_id)
    if underscore_pos >= len(command) or command[underscore_pos] != '_':
        return "error"
    
    # Get the command
    space_pos = command.find(' ', underscore_pos + 1)
    if space_pos == -1:
        device_command = command[pos:]
    else:
        device_command = command[pos:space_pos]
    
    # Check if the action is empty
    if not device_command:
        return "error"
    
    return device_command