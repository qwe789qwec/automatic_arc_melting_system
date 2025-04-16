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

//for plc modbus tcp
#define readCoil "\x01"
#define readInput "\x02"
#define readRegister "\x03"
#define writeCoil "\x05"
#define writeRegister "\x06"

#define coilOn "\xFF\x00"
#define coilOff "\x00\x00"

//input
#define EMGX3 "\x00\x03"
#define waterLeakX4 "\x00\x04"
#define waterflowX5 "\x00\x05"
#define presure50X6 "\x00\x06"
#define presure90X7 "\x00\x07"

//output
#define waterY4 "\x00\x04"
#define airFlowY12 "\x00\x0A"
#define buzzY17 "\x00\x17"

//register
#define pumpM10 "\x20\x0A"
#define spumpM11 "\x20\x0B"
#define ventM15 "\x20\x0F"
#define openGateValveM17 "\x20\x11"
#define closeGateValveM19 "\x20\x13"
#define arcOnM20 "\x20\x14"
#define arcOffM21 "\x20\x15"
#define flipM30 "\x20\x1E"
#define flipS33 "\xB0\x21"

#define presureS12 "\xB0\x0C"
#define s13coil "\xB0\x0D"
#define s14coil "\xB0\x0E"

//S0 = 45056 S1 = 45057 S12 = 45068

#define sd61800x "\x68\x24" //for analog
#define pumpValveBig0x "\x00\x06"
#define arc0x "\x00\x0B"

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
        void airFlow(std::string flux);
        bool make_action(std::string action);
        ~plc();

    private:
        tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP