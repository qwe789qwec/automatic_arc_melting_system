#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>

#include "weighing_control/weighing_machine.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

weighing_machine::weighing_machine(std::string ip, int port)
    : data_flag(false)
{   
    // Connect to weighing machine through TCP
    weighing_tcp.connect(ip, port);
}


bool weighing_machine::front_door(bool state)
{
    if (state == DOOR_OPEN) {
        // Send open door command
        weighing_tcp.write("QRA 60 7 3\r\n");
    }
    else if (state == DOOR_CLOSE) {
        // Send close door command
        weighing_tcp.write("QRA 60 7 2\r\n");
    }

    // Wait for acknowledgment and return result
    return weighing_tcp.check_receive("QRA 60 7 A", 6);
}

bool weighing_machine::dosing_head(bool state)
{
    if (state == DOSE_LOCK) {
        // Send lock dosing head command
        weighing_tcp.write("QRA 60 2 4\r\n");
    }
    else if (state == DOSE_UNLOCK) {
        // Send unlock dosing head command
        weighing_tcp.write("QRA 60 2 3\r\n");
    }

    // Wait for acknowledgment and return result
    return weighing_tcp.check_receive("QRA 60 2 A", 6);
}

bool weighing_machine::set_gram(std::string gram)
{
    // Compose and send weight setting command
    std::string message = "QRD 1 1 5 " + gram + "\r\n";
    weighing_tcp.write(message);
    
    // Wait for acknowledgment and return result
    return weighing_tcp.check_receive("QRD 1 1 5 A", 6);
}

bool weighing_machine::start_dosing()
{
    // Send dosing start command
    weighing_tcp.write("QRA 61 1\r\n");
    
    // Wait for acknowledgment with extended timeout
    if (weighing_tcp.check_receive("QRA 61 1 A", 200)) {
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
    weighing_tcp.write("QRD 2 4 12\r\n");
    
    std::string receivemessage;
    std::string mg_data;
    auto start_time = std::chrono::steady_clock::now();
    
    // Poll for response with 9 second timeout
    while (true)
    {
        if (weighing_tcp.receive(receivemessage)) {
            // Extract weight value from XML-formatted response
            mg_data = take_data(receivemessage, "<Content Unit=\"mg\">", "</Content>");
            if (mg_data != "none") {
                data_flag = false;
                return last_material + " " + mg_data;
            }
        }
        
        // Check for timeout
        if (std::chrono::steady_clock::now() - start_time >= std::chrono::seconds(15)) {
            printf("take data timeout\n");
            return "take data timeout";
        }
    }
    
    // The following code is technically unreachable due to the infinite loop above
    // Keeping it for compatibility with original implementation
    if (weighing_tcp.check_receive("QRD 2 4 12 A", 5)) {
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
    else if (action == "mgram") {
        // Process weight dosing command (e.g., "mgram30")
        // Extract weight value
        std::string weight_value = token[3];
        last_material = token[2];
        
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
    else if (action == "getweight") {
        const char request[] = "\x53\x0D\x0A"; // S\r\n
        char* message = nullptr;
        int size = 0;
        int retries = 3;
    
        while (retries-- > 0) {
            weighing_tcp.writeRaw(request, sizeof(request) - 1);
            usleep(1000 * 1000 * 1); // 1 second delay
    
            weighing_tcp.receiveRaw(message, size);
    
            if (size > 0) {
                message[size] = '\0';
                std::cout << "Received: " << message << std::endl;
    
                // assuming the format is "S S weight g"
                std::vector<std::string> tokens;
                std::stringstream ss(message);
                std::string t;
                while (ss >> t) tokens.push_back(t);
    
                if (tokens.size() >= 4 && tokens[0] == "S" && tokens[1] == "S") {
                    last_weight_mg = std::stod(tokens[2]) * 1000.0; // g -> mg
                    std::cout << std::fixed << std::setprecision(4) << last_weight_mg << std::endl;
    
                    data_flag = true;
                    return true;
                }
            }
        }
    }
    else {
        // Unknown command
        return false;
    }

    return true;
}

weighing_machine::~weighing_machine()
{
    // Close TCP connection
    weighing_tcp.close();
}