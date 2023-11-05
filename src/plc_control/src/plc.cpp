#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "plc_control/plc.hpp"
#include "tcp_handle/tcp_socket.hpp"

plc::plc(std::string ip, int port)
{
	plc_tcp.connect(ip, port);
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

std::string plc::status(std::string component)
{   
    std::string message;
    plc_tcp.write(component);
    plc_tcp.receive(message);
    return message;
}

std::string plc::read(std::string output)
{
    std::string message;
    plc_tcp.write(output);
    plc_tcp.receive(message);
    return message;
}

void plc::write(std::string input) 
{
    std::string message;
    plc_tcp.write(input);
    plc_tcp.receive(message);
}

void plc::airFlow(std::string flux)
{
    std::string message;
    plc_tcp.write(flux);
    plc_tcp.receive(message);
}

plc::~plc()
{
	plc_tcp.close();
}