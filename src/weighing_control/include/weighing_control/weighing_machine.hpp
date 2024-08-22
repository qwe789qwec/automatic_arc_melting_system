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
    std::string startdosing();
    std::string getgramvalue(const std::string& xml_data) ;
    bool make_action(std::string step);
	~weighing_machine();

private:
    tcp_socket weiging_tcp;
};

#endif // RECTANGLE_HPP