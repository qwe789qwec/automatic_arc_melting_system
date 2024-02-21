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

slider::slider(std::string ip, int port)
{
	slider_tcp.connect(ip, port);
	slider_tcp.write(servo_onf(motor_1, on));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_2, on));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_3, on));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_x, on));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_y, on));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_z, on));
	slider_tcp.check_receive("#992322C", 3);
	// slider_tcp.write(servo_onf(motor7, on));
	// slider_tcp.write(servo_onf(motor8, on));
}


std::string slider::checksum(std::string input) {
	// calculate checksum
	uint8_t sum = 0;
	std::string::size_type i;
    for (i = 0; i < input.size(); i++) {
        sum += input[i];
    }
    
	// change uint8_t to hex string and keep 2 digits
	char checksum[3];
	sprintf(checksum, "%02X", sum);

    return checksum;
}

std::string slider::command(std::string command)
{
	return command + checksum(command) +"\r\n";
}

std::string slider::servo_onf(std::string station, std::string state)
{	
	return command("!99232" + station + state);
	// !992320101@@\r\n
}

std::string slider::servo_move(std::string station, std::string position, std::string speed)
{	
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(4) << speed;
	std::string speedaddzero = oss.str();
	return command("!99234" + station + speedaddzero + speedaddzero + speedaddzero + position);
	// !992340100640064006400000000@@\r\n
}

std::string slider::status(std::string station)
{
	return command("!99212" + station);
	// !9921201@@\r\n
}

std::string slider::length2string(int number)
{
	std::ostringstream ss;
    ss << std::setfill('0') << std::setw(8) << std::hex << number;
    std::string result = ss.str();

	return result;
}

std::string slider::compute_string(std::string number1, std::string number2, std::string sign)
{	
	int number = 0;
	if (sign.compare("+") == 0)
	{
		number = strtol(number1.c_str(), NULL, 16) + strtol(number2.c_str(), NULL, 16);
	}
	else{
		number = strtol(number1.c_str(), NULL, 16) - strtol(number2.c_str(), NULL, 16);
	}
	std::ostringstream ss;
    ss << std::hex << number;
    std::string result = ss.str();
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << result;
	std::string addzero = oss.str();

	return addzero;
}

std::string slider::relative_position(std::string number1, std::string number2, std::string sign)
{	
	std::string result = compute_string(number1, number2, sign);
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(8) << result;
	std::string addzero = oss.str();

	return addzero;
}

std::string slider::count_circle(double radius, double unmber, double index, std::string center)
{
	std::string centerx = center.substr(0, 8);
	std::string centery = center.substr(8, 15);
	std::cout << "x:" << centerx << "  y:" << centery << std::endl;
	int sinValue = static_cast<int>(sin((M_PI/(unmber/2))*index) * radius);
	int yvalue = strtol(centery.c_str(), NULL, 16) + sinValue;
	int cosValue = static_cast<int>(cos((M_PI/(unmber/2))*index) * radius);
    int xvalue = strtol(centerx.c_str(), NULL, 16) + cosValue;
	return length2string(xvalue) + length2string(yvalue);
}

void slider::check_position(std::string servo)
{
	std::string message, compare;
	compare = "#99212" + servo + "1";
	std::chrono::seconds timeout(30);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		slider_tcp.write(status(servo));
		slider_tcp.receive(message);
		if (message.substr(0, compare.size()).compare(compare) == 0)
		{
			printf("compare");
			break;
		}
		else if (message.compare("test") == 0)
		{
			printf("data: %s\n", message.c_str());
		}
		if (std::chrono::steady_clock::now() - start_time >= timeout)
		{
			printf("test timeout");
			break;
		}
		// printf("cycle");
		// std::cout << message;
		usleep(100 * 500);
	}
}

void slider::move(std::string servo, std::string position, std::string speed)
{
	slider_tcp.write(servo_move(servo, position, speed));
	slider_tcp.check_receive("#99234", 3);
	check_position(servo);
	usleep(100 * 200);
}

void slider::curve_move(std::string servo1, std::string servo2, std::string position, std::string speed)
{
	std::string servo = compute_string(servo1, servo2, "+");
	slider_tcp.write(servo_move(servo, position, speed));
	slider_tcp.check_receive("#99234", 3);
	check_position(servo1);
	check_position(servo2);
	usleep(100 * 200);
}

void slider::arc_path()
{
	std::string center_x = length2string(57*1000);
	std::string center_xy = length2string(57*1000) + length2string(30*1000);
	std::string center_yz = length2string(30*1000) + length2string(74.5*1000);// y 30 z 74.5
	// std::string center_yz = "0000753000012304";// y 30 z 74.5
	std::string zero = "0000000000000000";
	std::string home = "0001117000013880";// y 70 and z 80
	std::string route_1 = "0000EA60000124F8";// y 60 z 75
	std::string route_2 = "0000C35000011D28";// y 50 z 73
	std::string route_3 = "00009C4000011940";// y 40 z 72


	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	usleep(1000 * 5000);
	curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	

	int sep = 16;
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(7000, sep, i, center_xy));
	}
	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	// slider.move(motor_x, "0000EA60");
}

slider::~slider()
{
	slider_tcp.write(servo_onf(motor_1, off));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_2, off));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_3, off));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_x, off));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_y, off));
	slider_tcp.check_receive("#992322C", 3);
	slider_tcp.write(servo_onf(motor_z, off));
	slider_tcp.check_receive("#992322C", 3);
	// slider_tcp.write(servo_onf(motor7, off));
	// slider_tcp.write(servo_onf(motor8, off));
	slider_tcp.close();
}