#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

//for plc tcp string

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

//for plc modbus tcp
#define readInput "\x02"
#define readRegister "\x03"
#define writeCoil "\x05"
#define writeRegister "\x06"

#define coilOn "\xFF\x00"
#define coilOff "\x00\x00"

#define sd61800x "\x68\x24" //for analog
#define water0x "\x00\x04"
#define buzz0x "\x00\x0B"

class plc
{
public:
	plc(std::string, int);
    char* modbus(const char* function,const char* component,const char* data);
    char* dec2hex(int value);
    std::string ioOnOff(std::string io,std::string state);
    std::string write(std::string input);
    char* writeRaw(const void* input,int &size);
    char* ioWrite(const char* component,const char* data);
    bool ioRead(const char* component);
    char* registerWrite(const char* component,int data);
    bool registerRead(const char* component,int data);
    int checkPresure(std::string input);
    void gateValve(std::string input);
    void pump(std::string input);
    void airFlow(std::string flux);
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP