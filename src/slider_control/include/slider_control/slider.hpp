#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <string>
#include "tcp_handle/tcp_socket.hpp"

class slider
{
public:
    slider(std::string ip, int port);
    ~slider();
    bool make_action(std::string step);

private:
    // Position Constants - Slider Positions
    static constexpr const int ZERO = 0;
    static constexpr const int SLIDER1_INIT = 0;
    static constexpr const int SLIDER2_INIT = 100000;  // slider for vertical 100.000 mm
    static constexpr const int SLIDER3_INIT = 0;  // slider for horizontal 3.000 mm
    static constexpr const int CUP_STOCK_R = 600000;   // cup stock (right), slider1 60.000 mm
    static constexpr const int SHELF_POS = 150000;  // shelf position, slider1 150.000 mm
    // static constexpr const char* SHELF_POS1 = "000249F0";
    // static constexpr const char* SHELF_POS2 = "00033450";
    // static constexpr const char* SHELF_POS3 = "00041EB0";
    // static constexpr const char* SHELF_POS4 = "00050910";
    // static constexpr const char* SHELF_POS5 = "0005F370";
    static constexpr const int WEIGHING_POS = 640000;  // weighing position, slider1 640.000 mm
    static constexpr const int PRODUCT_STOCK_R = 699000; // arc product (right), slider1 699.000 mm

    // Position Constants - Cup Handling
    static constexpr const char* SLIDER2_LIFTCUP = "000055F0";   // vertical slider position to lift cup
    static constexpr const char* SLIDER3_LIFTCUP = "00000001";   // horizontal slider position to lift cup
    static constexpr const char* SLIDER2_INTO_ARC = "000055F0";  // vertical for insertion into arc furnace
    static constexpr const char* SLIDER3_INTO_ARC = "0004A8F8";  // horizontal for insertion into arc furnace
    static constexpr const char* SLIDER2_PUTCUP_ARC = "0000A21C"; // vertical to put cup in holder
    static constexpr const char* SLIDER3_PUTCUP_ARC = "0004A8F8"; // horizontal to put cup in holder
    static constexpr const char* SLIDER2_OFFCUP_ARC = "0000A21C"; // vertical to remove from cup
    static constexpr const char* SLIDER3_OFFCUP_ARC = "0003D090"; // horizontal to remove from cup
    static constexpr const char* SLIDER2_BEFORECUP_ARC = "000055F0"; // vertical away from cup
    static constexpr const char* SLIDER3_BEFORECUP_ARC = "0003D090"; // horizontal away from cup
    static constexpr const char* SLIDER2_OUTARC = "000055F0";   // vertical exit without cup
    static constexpr const char* SLIDER3_OUTARC = "00000001";   // horizontal exit without cup

    // Motor Constants
    static constexpr const char* MOTOR_1 = "01";
    static constexpr const char* MOTOR_2 = "02";
    static constexpr const char* MOTOR_3 = "04";
    static constexpr const char* MOTOR_X = "08";
    static constexpr const char* MOTOR_Y = "10";
    static constexpr const char* MOTOR_Z = "20";
    static constexpr const char* MOTOR_7 = "40";
    static constexpr const char* MOTOR_8 = "80";

    // State Constants
    static constexpr const char* ON = "1";
    static constexpr const char* OFF = "0";
    static constexpr int CW = 1;    // Clockwise
    static constexpr int CCW = -1;  // Counter-clockwise
    
    std::string command(std::string command);
    std::string servo_onf(std::string station, std::string state);
    std::string servo_move(std::string station, std::string position, std::string speed = "32");
    std::string status(std::string station);
    std::string length2string(int number);
    std::string count_circle(double radius, double number, double index, std::string center);
    void move(std::string servo, std::string position, std::string speed = "32");
    void curve_move(std::string servo1, std::string servo2, std::string position, std::string speed = "08");
    void check_position(std::string servo);
    void arc_path(int direction, int times = 1, int stop_times = 3);
    void put_cup_arc();
    void take_cup_arc();

    // TCP connection
    tcp_socket slider_tcp;
};

#endif // SLIDER_HPP