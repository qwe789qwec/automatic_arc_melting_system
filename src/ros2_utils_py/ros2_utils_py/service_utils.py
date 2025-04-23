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
        service_name: str,
        timeout: float = 3.0) -> bool:
    """
    Blocking service call with timeout.
    
    Args:
        client: ROS2 service client
        logger: ROS2 logger
        action: Action string to send in the request
        service_name: Name of the service (for logging)
        timeout: Timeout in seconds
        
    Returns:
        bool: True if service call successful, False otherwise
    """
    # Wait for service to be available
    if not client.wait_for_service(timeout_sec=timeout):
        logger.error(f"{service_name} service not available after timeout")
        return False
    
    # Create request
    request = ProcessService.Request()
    request.action = action
    
    # Send request
    future = client.call_async(request)
    
    # Wait for response with timeout
    start_time = time.time()
    while not future.done() and time.time() - start_time < timeout:
        time.sleep(0.01)
    
    if future.done():
        try:
            result = future.result()
            logger.info(f"{service_name} result: {result.result}")
            return True
        except Exception as e:
            logger.error(f"Exception getting {service_name} result: {str(e)}")
            return False
    else:
        logger.error(f"{service_name} call timed out")
        return False


def call_service_async(
        client: Client,
        logger,
        action: str,
        service_name: str) -> concurrent.futures.Future:
    """
    Non-blocking service call.
    
    Args:
        client: ROS2 service client
        logger: ROS2 logger
        action: Action string to send in the request
        service_name: Name of the service (for logging)
        
    Returns:
        Future: A future that resolves to True if successful, False otherwise
    """
    # Create a Future to return
    result_future = concurrent.futures.Future()
    
    # Check if service is available
    if not client.service_is_ready():
        if not client.wait_for_service(timeout_sec=0.1):
            logger.error(f"{service_name} service not available")
            result_future.set_result(False)
            return result_future
    
    # Create request
    request = ProcessService.Request()
    request.action = action
    
    # Define callback for when response is received
    def response_callback(future: Future):
        try:
            result = future.result()
            logger.info(f"{service_name} result for '{action}': {result.result}")
            result_future.set_result(True)
        except Exception as e:
            logger.error(f"Exception in {service_name} call '{action}': {str(e)}")
            result_future.set_result(False)
    
    # Send request asynchronously
    ros_future = client.call_async(request)
    ros_future.add_done_callback(response_callback)
    
    logger.debug(f"{service_name} request '{action}' sent asynchronously")
    return result_future


def get_command(command: str, device_id: str) -> str:
    """
    Parse command to extract device-specific command.
    
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