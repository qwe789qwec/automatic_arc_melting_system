#include <chrono>
#include <thread>
#include <cstdlib>
#include <memory>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "plc_control/plc.hpp"
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

plc::plc(std::string ip, int port)
{
    // Connect to PLC and initialize water system
    plc_tcp.connect(ip, port);
    coilWrite(WATER_Y4, COIL_ON);
    usleep(1000 * 1000);  // 1 second delay
}

char* plc::dec2hex(int value) 
{
    // Convert decimal to 2-byte hex representation
    static char hex_string[2];
    hex_string[0] = (char)(value / 256);
    hex_string[1] = (char)(value % 256);

    return hex_string;
}

char* plc::modbus(const char* function, const char* component, const char* data)
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

char* plc::writeRaw(const void* input, int &size) 
{
    // Send raw bytes and get response
    char* message;
    plc_tcp.writeRaw(input, size);
    usleep(300 * 1000);  // 300ms delay
    plc_tcp.receiveRaw(message, size);
    
    return message;
}

char* plc::coilWrite(const char* component, const char* data)
{
    // Write to a coil
    int message_size = 12;
    char* return_message = writeRaw(modbus(WRITE_COIL, component, data), message_size);
    return return_message;
}

bool plc::coilRead(const char* component)
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

bool plc::inputRead(const char* component)
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

char* plc::registerWrite(const char* component, int data)
{
    // Write to a register
    int message_size = 12;
    char* return_message = writeRaw(modbus(WRITE_REGISTER, component, dec2hex(data)), message_size);
    return return_message;
}

bool plc::registerRead(const char* component, int data)
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

bool plc::make_action(std::string step)
{    
    // Extract PLC-specific action from command
    std::string command = service_utils::get_command(step, "plc");
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
        usleep(1000 * 1000);  // 1 second delay
    }
    else if (action == "pump"){
        // Start pump and wait for pressure
        return_message = coilWrite(PUMP_M10, COIL_ON);
        usleep(1000 * 1000);  // 1 second delay
        return_message = coilWrite(PUMP_M10, COIL_OFF);
        
        // Wait for pressure to build up
        while (!coilRead(PRESURE_S12))
        {   
            usleep(1000 * 1000);  // 1 second delay
        }
    }
    else if (action == "singlePump"){
        // Control single pump operation
        return_message = coilWrite(SPUMP_M11, COIL_ON);
        usleep(1000 * 1000);  // 1 second delay
        return_message = coilWrite(SPUMP_M11, COIL_OFF);
        
        // Wait for S14 coil to become active
        while (!coilRead(S14_COIL))
        {   
            usleep(1000 * 1000);  // 1 second delay
        }
    }
    else if(action == "vent"){
        // Control ventilation
        return_message = coilWrite(VENT_M15, COIL_ON);
        usleep(1000 * 1000);  // 1 second delay
        return_message = coilWrite(VENT_M15, COIL_OFF);
        
        // Wait for S13 coil to become inactive
        while (coilRead(S13_COIL))
        {   
            usleep(1000 * 1000);  // 1 second delay
        }
    }
    else if(action == "arcOn"){
        // Turn on arc
        std::cout << "arc on" << std::endl;
        return_message = coilWrite(ARC_ON_M20, COIL_ON);
        usleep(3 * 1000 * 1000);  // 3 second delay
        return_message = coilWrite(ARC_ON_M20, COIL_OFF);
    }
    else if(action == "arcOff"){
        // Turn off arc
        std::cout << "arc off" << std::endl;
        return_message = coilWrite(ARC_OFF_M21, COIL_ON);
        usleep(3 * 1000 * 1000);  // 3 second delay
        return_message = coilWrite(ARC_OFF_M21, COIL_OFF);
    }
    else if(action == "waterOn"){
        // Turn on water
        std::cout << "water start" << std::endl;
        return_message = coilWrite(WATER_Y4, COIL_ON);
    }
    else if(action == "waterOff"){
        // Turn off water
        std::cout << "water off" << std::endl;
        return_message = coilWrite(WATER_Y4, COIL_OFF);
    }
    else if(action == "buzz"){
        // Activate buzzer
        std::cout << "buzz start" << std::endl;
        return_message = coilWrite(BUZZ_Y17, COIL_ON);
        usleep(3 * 1000 * 1000);  // 3 second delay
        return_message = coilWrite(BUZZ_Y17, COIL_OFF);
    }
    else if(action == "gateOpen"){
        // Open gate valve
        std::cout << "gate start" << std::endl;
        return_message = coilWrite(OPEN_GATE_VALVE_M17, COIL_ON);
        usleep(20 * 1000 * 1000);  // 20 second delay
        return_message = coilWrite(OPEN_GATE_VALVE_M17, COIL_OFF);
    }
    else if(action == "gateClose"){
        // Close gate valve
        std::cout << "gate start" << std::endl;
        return_message = coilWrite(CLOSE_GATE_VALVE_M19, COIL_ON);
        usleep(20 * 1000 * 1000);  // 20 second delay
        return_message = coilWrite(CLOSE_GATE_VALVE_M19, COIL_OFF);
    }
    else if(action == "airOn"){
        // Turn on air flow
        std::cout << "air start" << std::endl;
        return_message = coilWrite(AIR_FLOW_Y12, COIL_ON);
    }
    else if(action == "airOff"){
        // Turn off air flow
        std::cout << "air off" << std::endl;
        return_message = coilWrite(AIR_FLOW_Y12, COIL_OFF);
    }
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
    else if(action == "checkPresure"){
        // Check pressure status
        std::cout << "check presure" << std::endl;
        if(coilRead(PRESURE_S12)){
            std::cout << "In s12" << std::endl;
        }
        else{
            std::cout << "not in S12" << std::endl;
        }
    }
    else if(action == "autoFlip"){
        // Perform auto flip operation
        return_message = coilWrite(FLIP_M30, COIL_ON);
        usleep(1000 * 1000);  // 1 second delay
        return_message = coilWrite(FLIP_M30, COIL_OFF);
        
        // Wait for flip to complete
        while (!coilRead(FLIP_S33))
        {   
            usleep(1000 * 1000);  // 1 second delay
        }        
    }
    else if(action == "wait"){
        int time = std::stoi(token[2]);
        // Wait for 15 seconds
        usleep(time * 1000 * 1000);
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
plc::~plc()
{
    // Turn off water and close connection
    coilWrite(WATER_Y4, COIL_OFF);
    plc_tcp.close();
}