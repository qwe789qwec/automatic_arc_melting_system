#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "slider_control/slider.hpp"
#include "tcp_handle/tcp_socket.hpp"

plc::plc(std::string ip, int port)
{
	plc_tcp.connect(ip, port);
}

std::string plc::checkPresure()
{
    slider_tcp.write(input);
    slider_tcp.receive(message);
    std::string presure = message.substr(0, compare.size());
    return presure;
}

std::string plc::status(std::string component)
{
    slider_tcp.write(component);
    slider_tcp.receive(message);
}

void plc::pump(std::string input) 
{
    slider_tcp.write(input);
    slider_tcp.receive(message);
}


void plc::valve(std::string type, std::string state)
{	
    slider_tcp.write(type + state);
    slider_tcp.receive(message);
}

void plc::airFlow(std::string flux)
{
    slider_tcp.write(flux);
    slider_tcp.receive(message);
}

slider::~plc()
{
	plc_tcp.close();
}