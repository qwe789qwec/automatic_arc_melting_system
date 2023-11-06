#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "plc_control/plc.hpp"
#include "tcp_handle/tcp_socket.hpp"

plc::plc(std::string ip, int port)
{
	plc_tcp.connect(ip, port);
    ioOnOff(waterSupply, on);
    usleep(1000 * 1000);
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
    ioOnOff(waterSupply, off);
	plc_tcp.close();
}