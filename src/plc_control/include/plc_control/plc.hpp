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

#define transferpin "X1"
#define pumpBigpin "X2"
#define pumpSmallpin "X3"
#define presurepin "D1"

class plc
{
public:
	plc(std::string, int);
    std::string status(std::string component);
    int checkPresure(std::string input);
    void pump(std::string input);
    void valve(std::string type, std::string state);
    void airFlow(std::string flux);
	~plc();

private:
    tcp_socket plc_tcp;
};

#endif // RECTANGLE_HPP