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
#include "ros2_utils/service_utils.hpp"

void printcharm(const char *message, int size)
{   
    std::cout << "size:" << std::dec << size << " message:";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(static_cast<unsigned char>(message[i])) << " ";
    }
    std::cout << std::endl;
}

plc::plc(std::string ip, int port)
{
	plc_tcp.connect(ip, port);
    // ioOnOff(waterSupply, on);
    coilWrite(waterY4, coilOn);
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

char* plc::coilWrite(const char* component,const char* data)
{
    int message_size = 12;
    char* return_message = writeRaw(modbus(writeCoil, component, data), message_size);
    return return_message;
}

bool plc::coilRead(const char* component)
{
    int message_size = 12;
    char* return_message = writeRaw(modbus(readCoil, component, "\x00\x01"), message_size);
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
    int message_size = 12;
    char* return_message = writeRaw(modbus(readInput, component, "\x00\x01"), message_size);
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

bool plc::make_action(std::string step)
{	
	std::string action = service_utils::get_command(step, "plc");
	if(action.compare("error") == 0){
		return false;
	}

    char* return_message;

    if (action == "init"){
        usleep(1000 * 1000);
    }
	else if (action == "pump"){
        return_message = coilWrite(pumpM10, coilOn);
        usleep(1000 * 1000);
        return_message = coilWrite(pumpM10, coilOff);
        while (!coilRead(presureS12))
        {   usleep(1000 * 1000);
        }
    }
    else if (action == "singlePump"){
        return_message = coilWrite(spumpM11, coilOn);
        usleep(1000 * 1000);
        return_message = coilWrite(spumpM11, coilOff);
        while (!coilRead(s14coil))
        {   usleep(1000 * 1000);
        }
    }
    else if(action == "vent"){
        return_message = coilWrite(ventM15, coilOn);
        usleep(1000 * 1000);
        return_message = coilWrite(ventM15, coilOff);
        while (coilRead(s13coil))
        {   usleep(1000 * 1000);
        }
    }
    else if(action == "arcOn"){
        std::cout << "arc on" << std::endl;
        return_message = coilWrite(arcOnM20, coilOn);
        usleep(1000 * 1000 * 3);
        return_message = coilWrite(arcOnM20, coilOff);
    }
    else if(action == "arcOff"){
        std::cout << "arc off" << std::endl;
        return_message = coilWrite(arcOffM21, coilOn);
        usleep(1000 * 1000 * 3);
        return_message = coilWrite(arcOffM21, coilOff);
    }
    else if(action == "waterOn"){
        std::cout << "water start" << std::endl;
        return_message = coilWrite(waterY4, coilOn);
    }
    else if(action == "waterOff"){
        std::cout << "water off" << std::endl;
        return_message = coilWrite(waterY4, coilOff);
    }
    else if(action == "buzz"){
        std::cout << "buzz start" << std::endl;
        return_message = coilWrite(buzzY17, coilOn);
        usleep(1000 * 1000 * 3);
        return_message = coilWrite(buzzY17, coilOff);
    }
    else if(action == "gateOpen"){
        std::cout << "gate start" << std::endl;//20sec
        return_message = coilWrite(openGateValveM17, coilOn);
        usleep(20 * 1000 * 1000);
        return_message = coilWrite(openGateValveM17, coilOff);
    }
    else if(action == "gateClose"){
        std::cout << "gate start" << std::endl;//15sec
        return_message = coilWrite(closeGateValveM19, coilOn);
        usleep(20 * 1000 * 1000);
        return_message = coilWrite(closeGateValveM19, coilOff);
    }
    else if(action == "airOn"){
        std::cout << "air start" << std::endl;
        return_message = coilWrite(airFlowY12, coilOn);
    }
    else if(action == "airOff"){
        std::cout << "air off" << std::endl;
        return_message = coilWrite(airFlowY12, coilOff);
    }
    else if(action == "checkEMG"){
        std::cout << "check EMG" << std::endl;
        if(inputRead(EMGX3)){
            std::cout << "EMG on" << std::endl;
        }
        else{
            std::cout << "EMG off" << std::endl;
        }
    }
    else if(action == "checkPresure"){
        std::cout << "check presure" << std::endl;
        if(coilRead(presureS12)){
            std::cout << "In s12" << std::endl;
        }
        else{
            std::cout << "not in S12" << std::endl;
        }
    }
    else if(action == "autoFlip"){
        return_message = coilWrite(flipM30, coilOn);
        usleep(1000 * 1000);
        return_message = coilWrite(flipM30, coilOff);
        while (!coilRead(flipS33))
        {   usleep(1000 * 1000);
        }        
    }
    else if(action == "wait15s"){
        usleep(15 * 1000 * 1000);
    }
    else if(action == "wait20s"){
        usleep(20 * 1000 * 1000);
    }
    else{
        return false;
    }

    printcharm(return_message, 12);
	return true;
}

plc::~plc()
{
    // ioOnOff(waterSupply, off);
    coilWrite(waterY4, coilOff);
	plc_tcp.close();
}