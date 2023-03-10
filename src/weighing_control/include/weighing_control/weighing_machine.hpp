#ifndef WEIGHING_MACHINE_HPP
#define WEIGHING_MACHINE_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

#define opendoor true
#define closedoor false

#define lock true
#define unlock false

class weighing_machine
{
public:
	weighing_machine(std::string ip, int port);
    void frontdoor(bool state);
    void dosinghead(bool state);
    void setgram(std::string gram);
    void startdosing();
	~weighing_machine();

private:
    tcp_socket weiging_tcp;
};

#endif // RECTANGLE_HPP