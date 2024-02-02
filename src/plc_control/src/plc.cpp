#include <chrono>
#include <thread>

#include <cstdlib>
#include <memory>
#include <iomanip>

#include <stdio.h>
#include <unistd.h>

#include "rclcpp/rclcpp.hpp"
#include "plc_control/plc.hpp"
#include "tcp_handle/tcp_socket.hpp"

plc::plc(std::string ip, int port)
{
	plc_tcp.connect(ip, port);
    // ioOnOff(waterSupply, on);
    usleep(1000 * 1000);
}

char* plc::dec2hex(int value) 
{
    static char hex_string[2];
    hex_string[0] = (char)(value / 256);
    hex_string[1] = (char)(value % 256);

    return hex_string;
}

char* plc::modbus(const char* function,const char* component,const char* data)
{
    // Allocate memory for the message
    static char message[] = "\x00\x01\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00";
    message[7] = function[0];
    message[8] = component[0];
    message[9] = component[1];
    message[10] = data[0];
    message[11] = data[1];

    return message;
}

std::string plc::ioOnOff(std::string io, std::string state)
{   
    std::string message;
    if(state.compare(on) == 0){
        message = io + "on";
    }
    else if(state.compare(off) == 0){
        message = io + "of";
    }
    plc_tcp.write(message);
    plc_tcp.receive(message);
    return message;
}



int plc::checkPresure(std::string input)
{   
    std::string message;
    plc_tcp.write(input);
    plc_tcp.receive(message);
    std::string number = message.substr(0, message.size());
    int presureValue = strtol(number.c_str(), NULL, 10);
    return presureValue;
}

void plc::gateValve(std::string input)
{
    if(input.compare(on) == 0){
        ioOnOff(openGateValve, on);
        usleep(1000 * 1500);
        ioOnOff(openGateValve, off);
    }
    else if(input.compare(off) == 0){
        ioOnOff(closeGateValve, on);
        usleep(1000 * 1500);
        ioOnOff(closeGateValve, off);
    }

    usleep(1000 * 1000 * 20);
}

void plc::pump(std::string input)
{
    if(input.compare(on) == 0){
        ioOnOff(startPump, on);
        usleep(1000 * 1500);
        ioOnOff(startPump, off);

        // usleep(1000 * 1000 * 60 * 3); //one times pump
        // usleep(1000 * 1000 * 60 * 5); //two times pump
        usleep(1000 * 1000 * 60 * 8); //three times pump

    }
    else if(input.compare(off) == 0){
        ioOnOff(startVent, on);
        usleep(1000 * 1500);
        ioOnOff(startVent, off);

        usleep(1000 * 1000 * 60 * 2);
    }

    usleep(1000 * 1000 * 30);
}

std::string plc::write(std::string input) 
{
    std::string message;
    plc_tcp.write(input);
    plc_tcp.receive(message);
    
    return message;
}

char* plc::writeRaw(const void* input,int &size) 
{
    char* message;
    plc_tcp.writeRaw(input, size);
    usleep(1000 * 300);
    plc_tcp.receiveRaw(message, size);
    // std::cout << "size:" << std::dec << size << " message:";
    // for (int i = 0; i < size; i++)
    // {
    //     std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(message[i])) << " ";
    // }
    // std::cout << std::endl;
    return message;
}

char* plc::ioWrite(const char* component,const char* data)
{
    int message_size = 12;
    char* return_message = writeRaw(modbus(writeCoil, component, data), message_size);
    return return_message;
}

bool plc::ioRead(const char* component)
{
    int message_size = 12;
    char* return_message = writeRaw(modbus(readInput, component, "\x00\x01"), message_size);
    if (return_message[message_size] == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}

char* plc::registerWrite(const char* component,int data)
{
    int message_size = 12;
    char* return_message = writeRaw(modbus(writeRegister, component, dec2hex(data)), message_size);
    return return_message;
}

bool plc::registerRead(const char* component,int data)
{
    int message_size = 12;
    char* checkdata = dec2hex(data);
    char* return_message = writeRaw(modbus(readRegister, component, "\x00\x01"), message_size);
    if(checkdata[0] == return_message[message_size - 2] && checkdata[1] == return_message[message_size-1])
    {
        return true;
    }
    else
    {
        return false;
    }
    return return_message;
}

void plc::airFlow(std::string flux)
{
    std::string message;
    plc_tcp.write(flux);
    plc_tcp.receive(message);
}

plc::~plc()
{
    // ioOnOff(waterSupply, off);
	plc_tcp.close();
}