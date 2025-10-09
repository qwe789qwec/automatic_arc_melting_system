#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "slider_control/slider.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

slider::slider(std::string ip, int port)
: InstrumentControl(ip, port)
{    
    // Activate all required servos
    instrument_socket_.write(servo_onf(MOTOR_1, ON));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_2, ON));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_3, ON));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_X, ON));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_Y, ON));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_Z, ON));
    instrument_socket_.check_receive("#992322C", 3);
    // Optional motors not activated in this implementation
    // instrument_socket_.write(servo_onf(MOTOR_7, ON));
    // instrument_socket_.write(servo_onf(MOTOR_8, ON));
}

std::string slider::command(std::string command)
{
	// Calculate checksum
	uint8_t sum = 0;
    std::string::size_type i;
    for (i = 0; i < command.size(); i++) {
        sum += command[i];
    }
    
    // Convert to 2-digit hex string
    char checksum[3];
    sprintf(checksum, "%02X", sum);
	
    // Format complete command with checksum and terminators
    return command + checksum + "\r\n";
}

std::string slider::servo_onf(std::string station, std::string state)
{    
    // Create servo on/off command: !992320101@@\r\n
    return command("!99232" + station + state);
}

std::string slider::servo_move(std::string station, std::string position, std::string speed)
{    
    // Format speed as 4-digit number
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << speed;
    std::string speedaddzero = oss.str();
    
    // Acceleration is fixed at "0001"
    std::string acc = "0001";
    
    // Create servo move command: !992340100640064006400000000@@\r\n
    return command("!99234" + station + acc + acc + speedaddzero + position);
}

std::string slider::status(std::string station)
{
    // Create status request command: !9921201@@\r\n
    return command("!99212" + station);
}

std::string slider::length2string(int number)
{
    // Convert integer to 8-digit hex string
    std::ostringstream ss;
    ss << std::setfill('0') << std::setw(8) << std::hex << number;
    return ss.str();
}

std::string slider::count_circle(double radius, double number, double index, std::string center)
{
    // Extract center X and Y positions
    std::string centerx = center.substr(0, 8);
    std::string centery = center.substr(8, 15);
    
    // Calculate sin component for Y position
    int sinValue = static_cast<int>(sin((M_PI/(number/2))*index + M_PI/2) * radius);
    int yvalue = strtol(centery.c_str(), NULL, 16) + sinValue;
    
    // Calculate cos component for X position
    int cosValue = static_cast<int>(cos((M_PI/(number/2))*index + M_PI/2) * radius);
    int xvalue = strtol(centerx.c_str(), NULL, 16) + cosValue;
    
    // Return combined X and Y positions
    return length2string(xvalue) + length2string(yvalue);
}

void slider::check_position(std::string servo)
{
    std::string message, compare;
    compare = "#99212" + servo + "1";
    std::chrono::seconds timeout(100);
    auto start_time = std::chrono::steady_clock::now();
    
    // Poll status until servo reports completion or timeout
    while (true) {
        instrument_socket_.write(status(servo));
        instrument_socket_.receive(message);
        
        if (message.substr(0, compare.size()) == compare) {
            // Position reached
            break;
        }
        
        // Check for timeout
        if (std::chrono::steady_clock::now() - start_time >= timeout) {
            printf("Test timeout\n");
            break;
        }
        
        // Wait before next poll
        usleep(50000); // 50ms
    }
}

void slider::move(std::string servo, std::string position, std::string speed)
{
    // Send move command
    instrument_socket_.write(servo_move(servo, position, speed));
    instrument_socket_.check_receive("#99234", 3);
    
    // Wait for move to complete
    check_position(servo);
    
    // Small delay after completion
    usleep(20000); // 20ms
}

void slider::curve_move(std::string servo1, std::string servo2, std::string position, std::string speed)
{
    // Combine servo IDs for simultaneous movement
	int value1 = strtol(servo1.c_str(), nullptr, 16);
    int value2 = strtol(servo2.c_str(), nullptr, 16);
	int combined_value = value1 + value2;
	std::ostringstream oss;
    oss << std::hex << std::setfill('0') << std::setw(2) << combined_value;
    std::string servo = oss.str();
    
    // Send move command for both servos
    instrument_socket_.write(servo_move(servo, position, speed));
    instrument_socket_.check_receive("#99234", 3);
    
    // Wait for both servos to complete movement
    check_position(servo1);
    check_position(servo2);
    
    // Small delay after completion
    usleep(20000); // 20ms
}

void slider::arc_path(int direction, int times, int stop_times)
{   int count_dir = 0;

    // Define key positions
    std::string center_x = length2string(57*1000);
    std::string center_xy = length2string(57*1000) + length2string(30*1000);
    std::string center_yz = length2string(30*1000) + length2string(74.5*1000); // y 30 z 74.5
	std::string home = length2string(70*1000) + length2string(80*1000); // y 70 and z 80
	std::string route_1 = length2string(60*1000) + length2string(75*1000); // y 60 z 75
	std::string route_2 = length2string(50*1000) + length2string(73*1000); // y 50 z 73
	std::string route_3 = length2string(40*1000) + length2string(72*1000); // y 40 z 72

    // Move to initial position
    move(MOTOR_X, center_x, "08"); // x 57
    curve_move(MOTOR_Y, MOTOR_Z, home); // x 57 y 70 z 80
    usleep(5000000); // 5 second delay
    
    // Approach the arc position
    curve_move(MOTOR_Y, MOTOR_Z, route_1); // x 57 y 60 z 75
    curve_move(MOTOR_Y, MOTOR_Z, route_2); // x 57 y 50 z 73
    curve_move(MOTOR_Y, MOTOR_Z, route_3); // x 57 y 40 z 72
    
    // First circular path with larger radius
    int sep = 16; // Number of steps in the circle
    for(int i = 0; i < sep; i++) {
        curve_move(MOTOR_X, MOTOR_Y, count_circle(7000, sep, i * direction, center_xy));
        if(i == 0) {
            move(MOTOR_Z, length2string(74.5*1000), "08");
        }
    }
    times--;
    count_dir++;
    
	while (times > 0) {
		// Move to center and wait
		move(MOTOR_X, center_x, "08"); // x 57
		curve_move(MOTOR_Y, MOTOR_Z, center_yz); // x 57 y 30 z 74.5
		usleep(stop_times * 1000000); // 3 second delay
		
		// Reverse circular path
		for(int i = 0; i < sep; i++) {
			curve_move(MOTOR_X, MOTOR_Y, count_circle(4000, sep,  i * direction * (count_dir % 2 == 0 ? 1 : -1), center_xy));
		}
		times--;
        count_dir++;
	}


    // Return to initial position
    move(MOTOR_X, center_x, "08"); // x 57
    curve_move(MOTOR_Y, MOTOR_Z, center_yz); // x 57 y 30 z 74.5
	usleep(3000000); // 3 second delay
    curve_move(MOTOR_Y, MOTOR_Z, route_3); // x 57 y 40 z 72
    curve_move(MOTOR_Y, MOTOR_Z, route_2); // x 57 y 50 z 73
    curve_move(MOTOR_Y, MOTOR_Z, route_1); // x 57 y 60 z 75
    curve_move(MOTOR_Y, MOTOR_Z, home); // x 57 y 70 z 80
}

void slider::put_cup_arc()
{
    std::string putSpeed = "4";
    
    // Movement sequence to put cup into arc furnace
    move(MOTOR_3, length2string(SLIDER3_INIT));
    move(MOTOR_2, length2string(SLIDER2_INIT));
    move(MOTOR_2, SLIDER2_LIFTCUP);
    move(MOTOR_3, SLIDER3_OFFCUP_ARC);
    move(MOTOR_3, SLIDER3_INTO_ARC, putSpeed);
    move(MOTOR_2, SLIDER2_PUTCUP_ARC, putSpeed);
    move(MOTOR_3, SLIDER3_OFFCUP_ARC, putSpeed);
    move(MOTOR_2, SLIDER2_BEFORECUP_ARC, putSpeed);
    move(MOTOR_3, length2string(SLIDER3_INIT));
    move(MOTOR_2, length2string(SLIDER2_INIT));
}

void slider::take_cup_arc()
{
    std::string takeSpeed = "4";
    
    // Movement sequence to take cup from arc furnace
    move(MOTOR_3, length2string(SLIDER3_INIT));
    move(MOTOR_2, length2string(SLIDER2_INIT));
    move(MOTOR_2, SLIDER2_LIFTCUP);
    move(MOTOR_3, SLIDER3_BEFORECUP_ARC);
    move(MOTOR_2, SLIDER2_OFFCUP_ARC);
    move(MOTOR_3, SLIDER3_PUTCUP_ARC, takeSpeed);
    move(MOTOR_2, SLIDER2_INTO_ARC, takeSpeed);
    move(MOTOR_3, SLIDER3_BEFORECUP_ARC, takeSpeed);
    move(MOTOR_3, length2string(SLIDER3_INIT));
    move(MOTOR_2, length2string(SLIDER2_INIT));
}

bool slider::make_action(std::string step)
{    
    // Parse the command for slider-specific action
	std::string command = service_utils::get_command(step, "slider");
    std::string action = "none";
    if (command == "test" || command == "init") {
        action = command;
    }
    else if (command == "none") {
        return true;
    }
    else if (command == "error") {
        return false;
    }

	std::vector<std::string>token = service_utils::split_string(command);
    // if no token found, return false
    if (token.size() < 2 && action == "none") {
        return false;
    }
    action = token[1];

    // Process different actions
    if(action == "init") {
        printf("Start init in sub process\n");
        move(MOTOR_1, length2string(SLIDER1_INIT), "100");
        move(MOTOR_3, length2string(SLIDER3_INIT), "100");
        move(MOTOR_2, length2string(SLIDER2_INIT), "100");
        move(MOTOR_Z, length2string(70*1000), "08");
        move(MOTOR_X, length2string(57*1000), "08");
        move(MOTOR_Y, length2string(70*1000), "08");
        move(MOTOR_Z, length2string(80*1000), "08");
    }
    else if(action == "arcinit") {
        printf("Arc init in sub process\n");
        move(MOTOR_Z, length2string(80*1000), "08");
        move(MOTOR_X, length2string(57*1000), "08");
        move(MOTOR_Y, length2string(70*1000), "08");
    }
    else if(action == "pos1") {
        printf("Start move to pos1 in sub process\n");
        move(MOTOR_1, length2string(SLIDER1_INIT), "100");
    }
    else if(action == "shelf") {
        int position = std::stoi(token[2]);
        std::string shelf_pos = length2string(SHELF_POS + (position - 1) * 60000);
        move(MOTOR_1, shelf_pos, "100");
    }
    else if(action == "weightPos") {
        move(MOTOR_1, length2string(WEIGHING_POS), "100");
    }
    else if(action == "putCupArc") {
        put_cup_arc();
    }
    else if(action == "takeCupArc") {
        take_cup_arc();
    }
    else if(action == "cupStockR") {
        move(MOTOR_1, length2string(CUP_STOCK_R), "100");
    }
    else if(action == "productStockR") {
        move(MOTOR_1, length2string(PRODUCT_STOCK_R), "100");
    }
	else if(action == "arc") {
		std::string dir = token[2];
		std::string times = token[3];
		// std::string stop_times = token[4];
		int direction = (dir == "cw") ? CW : CCW;
		int times_int = std::stoi(times);
		// int stop_times_int = std::stoi(stop_times);
		
		arc_path(direction, times_int, 3);
	}
    else {
        return false;
    }

    return true;
}

slider::~slider()
{
    // Turn off all servos before closing connection
    instrument_socket_.write(servo_onf(MOTOR_1, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_2, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_3, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_X, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_Y, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    instrument_socket_.write(servo_onf(MOTOR_Z, OFF));
    instrument_socket_.check_receive("#992322C", 3);
    // Optional motors not deactivated in this implementation
    // instrument_socket_.write(servo_onf(MOTOR_7, OFF));
    // instrument_socket_.write(servo_onf(MOTOR_8, OFF));
}