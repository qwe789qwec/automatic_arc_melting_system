#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

#define open "1"
#define close "0"

#define transfer "X1"
#define pumpBig "X2"
#define pumpSmall "X3"
#define presure "D1"

class plc
{
public:
	plc(std::string, int);
    std::string status(std::string component);
    std::string checkPresure();
    void pump(std::string input);
    void valve(std::string type, std::string state)
    void airFlow(std::string flux)
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP