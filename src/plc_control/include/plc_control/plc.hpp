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
#define readCoil "\x01"
#define readInput "\x02"
#define readRegister "\x03"
#define writeCoil "\x05"
#define writeRegister "\x06"

#define coilOn "\xFF\x00"
#define coilOff "\x00\x00"

#define EMG "\x00\x03"
#define waterLeak "\x00\x04"
#define waterflow "\x00\x05"
#define presure50 "\x00\x06"
#define presure90 "\x00\x07"
#define s12coil "\xB0\x0C"
#define s13coil "\xB0\x0D"
#define s14coil "\xB0\x0E"
#define s33coil "\xB0\x21"
//S0 = 45056 S1 = 45057 S12 = 45068

#define sd61800x "\x68\x24" //for analog
#define water0x "\x00\x04"
#define pumpValveBig0x "\x00\x06"
#define openGateValve0x "\x00\x08"
#define closeGateValve0x "\x00\x09"
#define airFlow0x "\x00\x0A"
#define arc0x "\x00\x0B"
#define buzz0x "\x00\x17"
#define M10 "\x20\x0A"
#define M15 "\x20\x0F"
#define M20 "\x20\x14"
#define M21 "\x20\x15"
#define M30 "\x20\x1E"
#define M11 "\x20\x0B"

class plc
{
public:
	plc(std::string, int);
    char* modbus(const char* function,const char* component,const char* data);
    char* dec2hex(int value);
    std::string ioOnOff(std::string io,std::string state);
    std::string write(std::string input);
    char* writeRaw(const void* input,int &size);
    char* coilWrite(const char* component,const char* data);
    bool coilRead(const char* component);
    bool inputRead(const char* component);
    char* registerWrite(const char* component,int data);
    bool registerRead(const char* component,int data);
    int checkPresure(std::string input);
    void gateValve(std::string input);
    void pump(std::string input);
    void airFlow(std::string flux);
    bool make_action(std::string action);
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP