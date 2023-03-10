#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

#define arc_pos "00000000"
#define shelf_posA "000249F0"
#define shelf_posB "00041EB0"
#define shelf_posC "0005F370"
#define weighing_pos "0009C400"

#define motor2take "000181F9"
#define motor2put "00008C66"
#define motor4take "00016F76"
#define motor4put "00049E13"

#define action_check "#99212011"

class slider
{
public:
	slider(std::string, int);
    std::string servo_onf(std::string station, std::string state);
    std::string servo_move(std::string station, std::string position);
    std::string postion(std::string station);
    void move(std::string servo, std::string position);
    void check_position(std::string servo);
	~slider();

private:
    tcp_socket slider_tcp;
};

#endif // RECTANGLE_HPP