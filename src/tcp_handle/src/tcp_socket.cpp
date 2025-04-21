#include <chrono>
#include <thread>
#include <cstring>
#include <cerrno>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "tcp_handle/tcp_socket.hpp"

tcp_socket::tcp_socket() : socket_fd(0), ip(""), port(0)
{
	memset(&server, 0, sizeof(server));
}

bool tcp_socket::set_blocking(bool blocking)
{
	int flags = fcntl(socket_fd, F_GETFL, 0);
	if (flags == -1)
	{
		return false;
	}
	if (blocking)
	{
		flags &= ~O_NONBLOCK;
	}
	else
	{
		flags |= O_NONBLOCK;
	}
	return fcntl(socket_fd, F_SETFL, flags) == 0;
}

bool tcp_socket::connect(const std::string &ip, const int &port)
{
	this->ip = ip;
	this->port = port;

	// create socket
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		return false;
	}

	// set server information
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &server.sin_addr) <= 0)
	{
		return false;
	}

	// connect to server
	if (::connect(socket_fd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		if (errno != EINPROGRESS)
		{
			return false;
		}
	}

	// set to unblocking mode
	set_blocking(false);

	return true;
}

bool tcp_socket::write(const std::string &data)
{
	int length = ::send(socket_fd, data.c_str(), data.size(), 0);
	if (length < 0)
	{
		return false;
	}
	return true;
}

bool tcp_socket::writeRaw(const void* data, int size)
{
	int length = ::send(socket_fd, data, size, 0);
	if (length < 0)
	{
		return false;
	}
	return true;
}

bool tcp_socket::receive(std::string &data)
{
	char buffer[1024] = {0};
	int length = ::recv(socket_fd, buffer, 1024, 0);
	if (length < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			return false;
		}
		return true;
	}
	else if (length == 0)
	{
		return false;
	}
	data = std::string(buffer, length);
	return true;
}

bool tcp_socket::receiveRaw(char* &data, int &size)
{
	char buffer[1024] = {0};
	int length = ::recv(socket_fd, buffer, 1024, 0);
	if (length < 0)
	{
		if (errno != EWOULDBLOCK && errno != EAGAIN)
		{
			return false;
		}
		return true;
	}
	else if (length == 0)
	{
		return false;
	}

	size = length;
	data = new char[length];
    std::memcpy(data, buffer, length);

	return true;
}

bool tcp_socket::check_receive(std::string compare, int timeout_seconds)
{
	std::string data;
	std::chrono::seconds timeout(timeout_seconds);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		if (receive(data))
		{
			if (data.substr(0, compare.size()).compare(compare) == 0)
			{
				break;
			}
			else if(compare.compare("test") == 0){
				printf("data: %s\n", data.c_str());
			}
			if(compare.compare("skip") == 0){
				printf("data: %s\n", data.c_str());
				break;
			}
		}
		if (std::chrono::steady_clock::now() - start_time >= timeout)
		{
			printf("test timeout");
			return false;
		}
	}
	return true;
}

std::string tcp_socket::get_action(std::string compare, std::string target)
{	
	if (compare == "test"){
		return "test";
	}
	else if (compare == "init"){
		return "init";
	}

    std::string::size_type pos = compare.find(target);
    if (pos == std::string::npos) {
        return "error";
    }

	// get the position of the underscore
    std::string::size_type underscorePos = pos + target.length();
    if (underscorePos >= compare.length() || compare[underscorePos] != '_') {
        return "error";
    }

	// find the position of the first space after the underscore
    std::string::size_type actionStart = underscorePos + 1;
    std::string::size_type spacePos = compare.find(' ', actionStart);
    
    // extract the action string
    std::string action;
    if (spacePos == std::string::npos) {
        // no space found, take the rest of the string
        action = compare.substr(actionStart);
    } else {
        // space found, take the substring until the space
        action = compare.substr(actionStart, spacePos - actionStart);
    }

    // check if the action is empty
    if (action.empty()) {
        return "error";
    }
    
    return action;
}

void tcp_socket::close()
{
	if (socket_fd > 0)
	{
		::close(socket_fd);
		socket_fd = 0;
	}
	return ;
}

tcp_socket::~tcp_socket()
{
	close();
}