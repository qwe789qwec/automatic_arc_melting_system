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
	std::string acc = "0001";
	std::string speedaddzero = oss.str();
	return command("!99234" + station + acc + acc + speedaddzero + position);
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
	// std::cout << "x:" << centerx << "  y:" << centery << std::endl;
	int sinValue = static_cast<int>(sin((M_PI/(unmber/2))*index + M_PI/2) * radius);
	int yvalue = strtol(centery.c_str(), NULL, 16) + sinValue;
	int cosValue = static_cast<int>(cos((M_PI/(unmber/2))*index + M_PI/2) * radius);
    int xvalue = strtol(centerx.c_str(), NULL, 16) + cosValue;
	return length2string(xvalue) + length2string(yvalue);
}

void slider::check_position(std::string servo)
{
	std::string message, compare;
	compare = "#99212" + servo + "1";
	std::chrono::seconds timeout(100);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		slider_tcp.write(status(servo));
		slider_tcp.receive(message);
		if (message.substr(0, compare.size()).compare(compare) == 0)
		{
			// printf("compare");
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



void slider::arc_path(int direction)
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
	// curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	
	int sep = 16;
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(7000, sep, i * direction, center_xy));
		if(i == 0){
			move(motor_z, length2string(74.5*1000), "08");
		}
	}
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(4000, sep, i * direction, center_xy));
	}

	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	// slider.move(motor_x, "0000EA60");
}



void slider::arc_path_2(int direction)
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
	// curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	
	int sep = 16;
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(7000, sep, i * direction, center_xy));
		if(i == 0){
			move(motor_z, length2string(74.5*1000), "08");
		}
	}
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(4000, sep, -i * direction, center_xy));
	}
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(4000, sep, i * direction, center_xy));
	}

	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	// slider.move(motor_x, "0000EA60");
}



void slider::arc_path_3(int direction)
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
	// curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	
	int sep = 16;
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(7000, sep, i * direction, center_xy));
		if(i == 0){
			move(motor_z, length2string(74.5*1000), "08");
		}
	}
	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	usleep(1000 * 6000);
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(4000, sep, -i * direction, center_xy));
	}
	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	usleep(1000 * 2000);
	for(int i = 0; i < sep; i++){
		curve_move(motor_x, motor_y, count_circle(4000, sep, i * direction, center_xy));
	}

	move(motor_x, center_x, "08");// x 57
	curve_move(motor_y, motor_z, center_yz);// x 57 y 30 z 74.5
	usleep(1000 * 2000);
	curve_move(motor_y, motor_z, route_3);// x 57 y 40 z 72
	curve_move(motor_y, motor_z, route_2);// x 57 y 50 z 73
	curve_move(motor_y, motor_z, route_1);// x 57 y 60 z 75
	curve_move(motor_y, motor_z, home);// x 57 y 70 z 80
	// slider.move(motor_x, "0000EA60");
}





void slider::put_cup_arc()
{
	std::string putSpeed = "4";
	move(motor_3, slider3_init);
	move(motor_2, slider2_init);
	move(motor_2, slider2_liftcup);
	move(motor_3, slider3_offcup_arc);
	move(motor_3, slider3_into_arc, putSpeed);
	move(motor_2, slider2_putcup_arc, putSpeed);
	move(motor_3, slider3_offcup_arc, putSpeed);
	move(motor_2, slider2_beforecup_arc, putSpeed);
	move(motor_3, slider3_init);
	move(motor_2, slider2_init);
}

void slider::take_cup_arc()
{
	std::string putSpeed = "4";
	move(motor_3, slider3_init);
	move(motor_2, slider2_init);
	move(motor_2, slider2_liftcup);
	move(motor_3, slider3_beforecup_arc);
	move(motor_2, slider2_offcup_arc);
	move(motor_3, slider3_putcup_arc, putSpeed);
	move(motor_2, slider2_into_arc, putSpeed);
	move(motor_3, slider3_beforecup_arc, putSpeed);
	move(motor_3, slider3_init);
	move(motor_2, slider2_init);
}

bool slider::make_action(std::string step)
{	
	std::string action = slider_tcp.get_action(step, "slider");
	if(action.compare("error") == 0){
		action = slider_tcp.get_action(step, "slider1");
	}
	if(action.compare("error") == 0){
		action = slider_tcp.get_action(step, "slider2");
	}
	if(action.compare("error") == 0){
		action = slider_tcp.get_action(step, "slider3");
	}
	if(action.compare("error") == 0 && step.compare("init") != 0){
		return false;
	}
	else if (step.compare("init") == 0){
		action = "init";
	}

	printf("action: %s\n", action.c_str());
	printf("step: %s\n", step.c_str());

	if(action.compare("init") == 0){
		printf("start init in sub process");
		move(motor_1, slider1_init);
		move(motor_3, slider3_init);
		move(motor_2, slider2_init);
		move(motor_z, length2string(70*1000), "08");
		move(motor_x, length2string(57*1000), "08");
		move(motor_y, length2string(70*1000), "08");
		move(motor_z, length2string(80*1000), "08");
	}
	else if(action.compare("arcinit") == 0){
		printf("arc init in sub process");
		move(motor_z, length2string(80*1000), "08");
		move(motor_x, length2string(57*1000), "08");
		move(motor_y, length2string(70*1000), "08");
	}
	else if(action.compare("pos1") == 0){
		printf("start move to pos1 in sub process");
		move(motor_1, slider1_init, "100");
	}
	else if(action.compare("shelf1") == 0){
		move(motor_1, shelf_pos1, "100");
	}
	else if(action.compare("shelf2") == 0){
		move(motor_1, shelf_pos2, "100");
	}
	else if(action.compare("shelf3") == 0){
		move(motor_1, shelf_pos3, "100");
	}
	else if(action.compare("shelf4") == 0){
		move(motor_1, shelf_pos4, "100");
	}
	else if(action.compare("shelf5") == 0){
		move(motor_1, shelf_pos5, "100");
	}
	else if(action.compare("weight_pos") == 0){
		move(motor_1, weighing_pos, "100");
	}
	else if(action.compare("arc_cw") == 0){
		arc_path(cw);
	}
	else if(action.compare("arc_ccw") == 0){
		arc_path(ccw);
	}
	else if(action.compare("arc_cw_2") == 0){
		arc_path_2(cw);
	}
	else if(action.compare("arc_ccw_2") == 0){
		arc_path_2(ccw);
	}
	else if(action.compare("arc_cw_3") == 0){
		arc_path_3(cw);
	}
	else if(action.compare("arc_ccw_3") == 0){
		arc_path_3(ccw);
	}
	else if(action.compare("put_cup_arc") == 0){
		put_cup_arc();
	}
	else if(action.compare("take_cup_arc") == 0){
		take_cup_arc();
	}
	else if(action.compare("cup_stock_r") == 0){
		move(motor_1, cup_stock_r, "100");
	}
	else if(action.compare("product_stock_r") == 0){
		move(motor_1, product_stock_r, "100");
	}
	else{
		return false;
	}

	return true;
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