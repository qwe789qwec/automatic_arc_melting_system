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

std::string slider::servo_move(std::string station, std::string position)
{
	return command("!99234" + station + "006400640064" + position);
	// !992340100640064006400000000@@\r\n
}
std::string slider::status(std::string station)
{
	return command("!99212" + station);
	// !9921201@@\r\n
}

void slider::check_position(std::string servo)
{
	std::string message, compare;
	compare = "#99212" + servo + "1";
	std::chrono::seconds timeout(10);
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
		printf("cycle");
		usleep(300 * 1000);
	}
}

void slider::move(std::string servo, std::string position)
{
	slider_tcp.write(servo_onf(servo, on));
	slider_tcp.check_receive("#992322C", 3);
	usleep(100 * 1000);
	slider_tcp.write(servo_move(servo, position));
	slider_tcp.check_receive("#99234", 3);
	check_position(servo);
	slider_tcp.write(servo_onf(servo, off));
	slider_tcp.check_receive("#992322C", 3);
	usleep(100 * 1000);
}

slider::~slider()
{
	slider_tcp.close();
}