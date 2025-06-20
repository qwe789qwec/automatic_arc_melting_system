#include <chrono>
#include <thread>
#include <cstdlib>
#include <memory>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "plc_control/plcxrd.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

void printcharm(const char *message, int size)
{   
    std::cout << "size:" << std::dec << size << " message:";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                  << static_cast<unsigned int>(static_cast<unsigned char>(message[i])) << " ";
    }
    std::cout << std::endl;
}

plcxrd::plcxrd(std::string ip, int port)
{
    // Connect to PLC and initialize water system
    plcxrd_tcp.connect(ip, port);
    // coilWrite(WATER_Y4, COIL_ON);
    usleep(1000 * 1000);  // 1 second delay
}

char* plcxrd::dec2hex(int value) 
{
    // Convert decimal to 2-byte hex representation
    static char hex_string[2];
    hex_string[0] = (char)(value / 256);
    hex_string[1] = (char)(value % 256);

    return hex_string;
}

char* plcxrd::modbus(const char* function, const char* component, const char* data)
{
    // Create Modbus protocol message
    static char message[] = "\x00\x01\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00";
    message[7] = function[0];
    message[8] = component[0];
    message[9] = component[1];
    message[10] = data[0];
    message[11] = data[1];

    return message;
}

char* plcxrd::writeRaw(const void* input, int &size) 
{
    // Send raw bytes and get response
    char* message;
    plcxrd_tcp.writeRaw(input, size);
    usleep(300 * 1000);  // 300ms delay
    plcxrd_tcp.receiveRaw(message, size);
    
    return message;
}

char* plcxrd::coilWrite(const char* component, const char* data)
{
    // Write to a coil
    int message_size = 12;
    char* return_message = writeRaw(modbus(WRITE_COIL, component, data), message_size);
    return return_message;
}

bool plcxrd::coilRead(const char* component)
{
    // Read from a coil
    int message_size = 12;
    char* return_message = writeRaw(modbus(READ_COIL, component, "\x00\x01"), message_size);
    if (return_message[message_size-1] == 0x01)
    {
        return true;
    }
    else
    {
        printcharm(return_message, message_size);
        printf("message_size: %d\n", message_size);
        return false;
    }
}

bool plcxrd::inputRead(const char* component)
{
    // Read from an input
    int message_size = 12;
    char* return_message = writeRaw(modbus(READ_INPUT, component, "\x00\x01"), message_size);
    if (return_message[message_size-1] == 0x01)
    {
        return true;
    }
    else
    {   
        printcharm(return_message, message_size);
        printf("message_size: %d\n", message_size);
        return false;
    }
}

char* plcxrd::registerWrite(const char* component, int data)
{
    // Write to a register
    int message_size = 12;
    char* return_message = writeRaw(modbus(WRITE_REGISTER, component, dec2hex(data)), message_size);
    return return_message;
}

bool plcxrd::registerRead(const char* component, int data)
{
    // Read from a register and compare
    int message_size = 12;
    char* checkdata = dec2hex(data);
    char* return_message = writeRaw(modbus(READ_REGISTER, component, "\x00\x01"), message_size);
    
    // Compare expected and actual values
    if(checkdata[0] == return_message[message_size - 2] && 
       checkdata[1] == return_message[message_size - 1])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool plcxrd::make_action(std::string step)
{    
    // Extract PLC-specific action from command
    std::string command = service_utils::get_command(step, "plcxrd");
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

    // Process different PLC actions
    if (action == "init"){
        // Initialize with a delay
        rclcpp::sleep_for(std::chrono::seconds(1)); // 1 second delay
    }
    else if(action == "doorlock"){
        // Control doorlock of xrd machine based on command
        std::string coil = "none";
        if(token[2] == "open"){
            // release doorlock
            std::cout << "doorlock open" << std::endl;
            coil = DOORLOCK_OPEN_M11;
        }
        else if(token[2] == "close"){
            // Close doorlock
            std::cout << "doorlock close" << std::endl;
            coil = DOORLOCK_CLOSE_M12;
        }
        return_message = coilWrite(coil.c_str(), COIL_ON);
        rclcpp::sleep_for(std::chrono::seconds(2)); // 2 second delay
        return_message = coilWrite(coil.c_str(), COIL_OFF);
        rclcpp::sleep_for(std::chrono::seconds(20)); // 20 second delay
    }
    // else if(action == "air"){
    //     // Control air flow based on command
    //     if(token[2] == "on"){
    //         // Turn on air flow
    //         std::cout << "air on" << std::endl;
    //         return_message = coilWrite(AIR_FLOW_Y12, COIL_ON);
    //     }
    //     else if(token[2] == "off"){
    //         // Turn off air flow
    //         std::cout << "air off" << std::endl;
    //         return_message = coilWrite(AIR_FLOW_Y12, COIL_OFF);
    //     }
    // }
    else if(action == "checkEMG"){
        // Check emergency stop status
        std::cout << "check EMG" << std::endl;
        if(inputRead(EMGX3)){
            std::cout << "EMG on" << std::endl;
        }
        else{
            std::cout << "EMG off" << std::endl;
        }
    }
    else if(action == "wait"){
        int time = std::stoi(token[2]);
        rclcpp::sleep_for(std::chrono::seconds(time)); // x second delay
    }
    else{
        return false;
    }

    // Print response message if available
    if (return_message) {
        printcharm(return_message, 12);
    }
    
    return true;
}

plcxrd::~plcxrd()
{
    // Turn off water and close connection
    // coilWrite(WATER_Y4, COIL_OFF);
    plcxrd_tcp.close();
}