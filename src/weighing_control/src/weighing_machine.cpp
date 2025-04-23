#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>

#include "weighing_control/weighing_machine.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

weighing_machine::weighing_machine(std::string ip, int port)
    : data_flag(false)
{   
    // Connect to weighing machine through TCP
    weiging_tcp.connect(ip, port);
}

bool weighing_machine::front_door(bool state)
{
    if (state == DOOR_OPEN) {
        // Send open door command
        weiging_tcp.write("QRA 60 7 3\r\n");
    }
    else if (state == DOOR_CLOSE) {
        // Send close door command
        weiging_tcp.write("QRA 60 7 2\r\n");
    }

    // Wait for acknowledgment and return result
    return weiging_tcp.check_receive("QRA 60 7 A", 6);
}

bool weighing_machine::dosing_head(bool state)
{
    if (state == DOSE_LOCK) {
        // Send lock dosing head command
        weiging_tcp.write("QRA 60 2 4\r\n");
    }
    else if (state == DOSE_UNLOCK) {
        // Send unlock dosing head command
        weiging_tcp.write("QRA 60 2 3\r\n");
    }

    // Wait for acknowledgment and return result
    return weiging_tcp.check_receive("QRA 60 2 A", 6);
}

bool weighing_machine::set_gram(std::string gram)
{
    // Compose and send weight setting command
    std::string message = "QRD 1 1 5 " + gram + "\r\n";
    weiging_tcp.write(message);
    
    // Wait for acknowledgment and return result
    return weiging_tcp.check_receive("QRD 1 1 5 A", 6);
}

bool weighing_machine::start_dosing()
{
    // Send dosing start command
    weiging_tcp.write("QRA 61 1\r\n");
    
    // Wait for acknowledgment with extended timeout
    if (weiging_tcp.check_receive("QRA 61 1 A", 200)) {
        data_flag = true;
        return true;
    }
    else {
        data_flag = false;
        return false;
    }
}

std::string weighing_machine::getsampledata()
{
    // Request current weight data
    weiging_tcp.write("QRD 2 4 12\r\n");
    
    std::string receivemessage;
    auto start_time = std::chrono::steady_clock::now();
    
    // Poll for response with 9 second timeout
    while (true)
    {
        if (weiging_tcp.receive(receivemessage)) {
            // Extract weight value from XML-formatted response
            receivemessage = take_data(receivemessage, "<Content Unit=\"mg\">", "</Content>");
            if (receivemessage != "none") {
                return receivemessage;
            }
        }
        
        // Check for timeout
        if (std::chrono::steady_clock::now() - start_time >= std::chrono::seconds(9)) {
            printf("take data timeout\n");
            return "take data timeout";
        }
    }
    
    // The following code is technically unreachable due to the infinite loop above
    // Keeping it for compatibility with original implementation
    if (weiging_tcp.check_receive("QRD 2 4 12 A", 5)) {
        data_flag = false;
        return receivemessage;
    }
    else {
        return "error";
    }
}

std::string weighing_machine::take_data(const std::string& xml_data, std::string start, std::string end)
{
    // Find start tag position
    size_t start_pos = xml_data.find(start);
    if (start_pos != std::string::npos) {
        // Move past the start tag
        start_pos += start.length();
        
        // Find end tag position
        size_t end_pos = xml_data.find(end, start_pos);
        if (end_pos != std::string::npos) {
            // Extract data between tags
            return xml_data.substr(start_pos, end_pos - start_pos);
        }
    }
    
    // Return "none" if tags not found
    return "none";
}

bool weighing_machine::make_action(std::string step)
{    
    // Extract weighing machine specific action
    std::string command = service_utils::get_command(step, "weighing");
    std::string action = "none";
    if (command == "test" || command == "init") {
        action = command;
    }
    else if (command == "none") {
        return true;
    }
    else if (command == "error") {
        return false;
    }

    std::vector<std::string>token = service_utils::split_string(command);
    // if no token found, return false
    if (token.size() < 2 && action == "none") {
        return false;
    }
    action = token[1];

    // Process different action types
    if (action == "init") {
        // Initialize by closing door
        printf("start init in sub process\n");
        return front_door(DOOR_CLOSE);
    }
    else if (action == "open") {
        // Open front door
        return front_door(DOOR_OPEN);
    }
    else if (action == "close") {
        // Close front door
        return front_door(DOOR_CLOSE);
    }
    else if (action.compare(0, 5, "mgram") == 0) {
        // Process weight dosing command (e.g., "mgram30")
        // Extract weight value
        std::string weight_value = action.substr(5);
        
        // Wait 3 seconds before operation
        usleep(1000 * 1000 * 3);
        
        // Execute full dosing sequence
        front_door(DOOR_CLOSE);
        dosing_head(DOSE_LOCK);
        set_gram(weight_value);
        start_dosing();
        dosing_head(DOSE_UNLOCK);
        front_door(DOOR_OPEN);
        return true;
    }
    else if (action.compare(0, 6, "Tmgram") == 0) {
        // Process test mode dosing (e.g., "Tmgram50")
        // Extract weight value
        std::string weight_value = action.substr(6);
        
        // Execute dosing sequence without door operations
        dosing_head(DOSE_LOCK);
        set_gram(weight_value);
        start_dosing();
        dosing_head(DOSE_UNLOCK);
        return true;
    }
    else {
        // Unknown command
        return false;
    }
}

weighing_machine::~weighing_machine()
{
    // Close TCP connection
    weiging_tcp.close();
}