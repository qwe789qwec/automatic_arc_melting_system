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

int plc::checkPresure(std::string input)
{   
    std::string message;
    plc_tcp.write(input);
    plc_tcp.receive(message);
    std::string number = message.substr(0, message.size());
    int presure = strtol(number.c_str(), NULL, 10);
    return presure;
}

std::string plc::status(std::string component)
{
    std::string message;
    plc_tcp.write(component);
    plc_tcp.receive(message);
    return message;
}

void plc::pump(std::string input) 
{
    std::string message;
    plc_tcp.write(input);
    plc_tcp.receive(message);
}


void plc::valve(std::string type, std::string state)
{	
    std::string message;
    plc_tcp.write(type + state);
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