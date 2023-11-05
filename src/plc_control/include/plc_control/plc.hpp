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

#define transfer "X1"
#define pumpBig "X2"
#define pumpSmall "X3"
#define presure "D1"

#define waterSupply "Y4"
#define pumpValveSmall "Y5"
#define pumpValveBig "Y6"
#define pump "Y7"
#define openValve "Y10"
#define closeValve "Y11"
#define arc "Y12"

class plc
{
public:
	plc(std::string, int);
    std::string ioOnOff(std::string io,std::string state);
    std::string status(std::string component);
    std::string read(std::string output);
    int checkPresure(std::string input);
    void write(std::string input);
    void airFlow(std::string flux);
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP