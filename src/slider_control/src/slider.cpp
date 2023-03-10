#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "slider_control/slider.hpp"
#include "tcp_handle/tcp_socket.hpp"

slider::slider(std::string ip, int port)
{
	slider_tcp.connect(ip, port);
}

std::string slider::servo_onf(std::string station, std::string state)
{
	return "!99232" + station + state + "@@\r\n";
}
std::string slider::servo_move(std::string station, std::string position)
{
	return "!99234" + station + "006400640064" + position + "@@\r\n";
}
std::string slider::postion(std::string station)
{
	return "!99212" + station + "@@\r\n";
}

void slider::check_position(std::string servo)
{
	std::string message;
	std::chrono::seconds timeout(10);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		slider_tcp.write(postion(servo));
		slider_tcp.receive(message);
		if (message.compare("test") == 0)
		{
			printf("data: %s\n", message.c_str());
		}
		if (message.compare(action_check) == 0)
		{
			break;
		}
		if (std::chrono::steady_clock::now() - start_time >= timeout)
		{
			printf("test timeout");
			break;
		}
		usleep(500 * 1000);
	}
}

void slider::move(std::string servo, std::string position)
{
	slider_tcp.write(servo_onf(servo, "1"));
	slider_tcp.check_receive("#992322C", 3);
	usleep(100 * 1000);
	slider_tcp.write(servo_move(servo, position));
	slider_tcp.check_receive("#99234", 3);
	check_position(servo);
	slider_tcp.write(servo_onf(servo, "0"));
	slider_tcp.check_receive("#992322C", 3);
	usleep(100 * 1000);
}

slider::~slider()
{
	slider_tcp.close();
}