#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "tcp_handle/tcp_socket.hpp"

#define arc_pos "00000001"
#define slider1_init "00000001"// slider for cobotta  0.000 mm
#define slider2_init "0001869F"// slider for vertical 100.000 mm
#define slider3_init "00000001"// slider for horizontal 3.000 mm
#define shelf_pos1 "000249F0"
#define shelf_pos2 "00033450"
#define shelf_pos3 "00041EB0"
#define shelf_pos4 "00050910"
#define shelf_pos5 "0005F370"
#define weighing_pos "0009C400"

#define slider2_liftcup "00004533"// vertical slider position to lift cup
#define slider3_liftcup "00000001"// horizontal slider position to lift cup, same as init
#define slider2_into_arc "00004533"// vertical slider position when slider brings cup into arc furnace, same as lift position
#define slider3_into_arc "0004BD77"// horizontal slider position when slider brings cup right on top of cupholder
#define slider2_putcup_arc "00006582"// vertical slider position when slider puts cup in holder inarc
#define slider3_putcup_arc "0004BD77"// horizontal slider position when slider puts cup in holder inarc
#define slider2_outarc "00006582"// vertical, when it gets out without cup
#define slider3_outarc "00000001"// horizontal, when it gets out without cup

#define motor_1 "01"
#define motor_2 "02"
#define motor_3 "04"
#define motor_x "08"
#define motor_y "10"
#define motor_z "20"
#define motor_7 "40"
#define motor_8 "80"

#define on "1"
#define off "0"

class slider
{
public:
	slider(std::string, int);
    std::string checksum(std::string input);
    std::string command(std::string command);
    std::string servo_onf(std::string station, std::string state);
    std::string servo_move(std::string station, std::string position, std::string speed = "32");
    std::string status(std::string station);
    std::string length2string(int number);
    std::string compute_string(std::string number1, std::string number2, std::string sign = "+");
    std::string relative_position(std::string number1, std::string number2, std::string sign = "+");
    std::string count_circle(double radius, double unmber, double index, std::string center);
    void move(std::string servo, std::string position, std::string speed = "32");
    void curve_move(std::string servo1, std::string servo2, std::string position, std::string speed = "08");
    void check_position(std::string servo);
    void arc_path();
    bool make_action(std::string action);
	~slider();

private:
    tcp_socket slider_tcp;
};

#endif // RECTANGLE_HPP