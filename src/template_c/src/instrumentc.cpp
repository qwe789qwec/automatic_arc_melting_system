#include <chrono>
#include <thread>
#include <cstdlib>
#include <memory>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "template_c/instrumentc.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

constexpr int instrumentc::number_ONE;
constexpr int instrumentc::number_TWO;

instrumentc::instrumentc(std::string ip, int port)
{
    // Connect to PLC and initialize water system
    instrumentc_tcp.connect(ip, port);
}

char* instrumentc::dec2hex(int value) 
{
    // Convert decimal to 2-byte hex representation
    static char hex_string[2];
    hex_string[0] = (char)(value / 256);
    hex_string[1] = (char)(value % 256);

    return hex_string;
}

bool instrumentc::make_action(std::string step)
{    
    // Extract instrument action from command
    std::string command = service_utils::get_command(step, "instrumentc");
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

    char* return_message = nullptr;

    // Process different instrument actions
    if (action == "init"){
        // Initialize with a delay
        rclcpp::sleep_for(std::chrono::seconds(1)); // 1 second delay
    }
    else if (action == "action1"){

        if(token[2] == "start"){
            std::cout << "Instrument action1 start" << std::endl;
            // instrumentc_tcp.write("start\r\n");
            // start action
        }
        else if(token[2] == "stop"){
            std::cout << "Instrument action1 stop" << std::endl;
            // instrumentc_tcp.write("stop\r\n");
            // stop action
        }

        rclcpp::sleep_for(std::chrono::seconds(number_ONE)); //delay
    }
    else if (action == "action2"){
        
        if(token[2] == "on"){
            std::cout << "Instrument action2 on" << std::endl;
            // instrumentc_tcp.write("turn_on\r\n");
            // turn on
        }
        else if(token[2] == "off"){
            std::cout << "Instrument action2 off" << std::endl;
            // instrumentc_tcp.write("turn_off\r\n");
            // turn off
        }

        rclcpp::sleep_for(std::chrono::seconds(number_TWO)); //delay
    }
    
    return true;
}

instrumentc::~instrumentc()
{
    // Turn off water and close connection
    instrumentc_tcp.close();
}