#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

#define on "1"
#define off "0"
#define open "1"
// #define close "0"

#define transfer "X1"
#define pumpBig "X2"
#define pumpSmall "X3"
#define presure "D1"

#define waterSupply "Y4"
#define pumpValveSmall "Y5"
#define pumpValveBig "Y6"
#define pumpMachine "Y7"
#define openGateValve "YA"  // 20sec
#define closeGateValve "YB"  // 20sec
#define arc "YC"
#define buzz "YD"

#define startPump "M0"
#define startVent "M5"

class plc
{
public:
	plc(std::string, int);
    std::string ioOnOff(std::string io,std::string state);
    std::string status(std::string component);
    std::string read(std::string output);
    std::string write(std::string input);
    char* write_raw(const void* input, int &size);
    int checkPresure(std::string input);
    void gateValve(std::string input);
    void pump(std::string input);
    void airFlow(std::string flux);
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP