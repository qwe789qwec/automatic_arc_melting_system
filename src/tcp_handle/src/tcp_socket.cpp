#include <chrono>
#include <thread>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#include "tcp_handle/tcp_socket.hpp"

#define nonblock 0
#define block 1

tcp_socket::tcp_socket(std::string pkg_ip, int pkg_port)
{
	ip = pkg_ip;
	port = pkg_port;
}

int tcp_socket::create()
{
	// struct timeval timeout;
	// fd_set readfds;
	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	// FD_ZERO(&readfds);
	// FD_SET(sock_fd, &readfds);
	// select(sock_fd+1, &readfds, NULL, NULL, &timeout);

	// int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket: %d", socket_fd);
	if (socket_fd < 0)
	{
		//"\n can't creat Socket\n"
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
	{
		//"\nInvalid address/ Address not supported.\n"
		printf("Invalid address/ Address not supported.");
		return -1;
	}

	connect_fd = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connect_fd < 0)
	{
		end();
		//"\nConnection Failed.\n"
		printf("Connection Failed.");
		return -1;
	}
	if (socket_type(nonblock) < 0)
	{
		end();
		printf("change to non-block error.");
		return -1;
	}
	return 0;
}

int tcp_socket::write(std::string message)
{
	char *write_msg = strcpy(new char[message.length() + 1], message.c_str());
	int errorTimes = 0;
	while (true)
	{
		if (send(socket_fd, write_msg, strlen(write_msg), 0) < 0)
		{
			if (errno == EWOULDBLOCK || errno == EAGAIN)
			{
				// wait
				sleep(3);
				errorTimes++;
				if (errorTimes >= 3)
				{
					// "\ntime out\n"
					return 0;
				}
			}
			else
			{
				// write fail
				printf("write fail");
				end();
				return -1;
			}
		}
		else
		{
			// get data
			return 0;
		}
	}
	return 0;
}

int tcp_socket::receive(std::string cmpmessage, char getmessage[])
{
	char buffer[1024];
	bool testflag = false;
	if (cmpmessage.compare("test\r\n") == 0)
		testflag = true;
	int timeout_seconds = 9;
	std::chrono::seconds timeout(timeout_seconds);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		int ret = recv(socket_fd, buffer, sizeof(buffer), 0);
		if (ret > 0)
		{	
			printf("read len: %d\n", ret);
			printf("buffer: %s\n", buffer);
			strcpy(getmessage, buffer);
			if (strcmp(getmessage, cmpmessage.c_str()) == 0)
			{
				printf("===right message===\n");
				return 0;
			}
		}
		// else if (ret == 0)
		// {
		// 	return 0;
		// }
		else if (ret == -1)
		{
			if (errno == EWOULDBLOCK || errno == EINTR)
			{
				if (std::chrono::steady_clock::now() - start_time >= timeout)
				{
					if (testflag)
					{
						printf("test timeout");
						break;
					}
					return -1;
					break;
				}
			}
			else
			{
				end();
				return -1;
			}
		}
	}
	return 0;
}

int tcp_socket::end()
{
	if (close(socket_fd) < 0)
	{
		return -1;
	}
	return 0;
}

int tcp_socket::socket_type(int type)
{
	int oldSocketFlag = fcntl(socket_fd, F_GETFL, 0);
	int newSocketFlag = oldSocketFlag | O_NONBLOCK;
	if (type == block)
	{
		newSocketFlag = oldSocketFlag & (~O_NONBLOCK);
	}

	if (fcntl(socket_fd, F_SETFL, newSocketFlag) == -1)
	{
		// "\nset socket fd error.\n"
		end();
		return -1;
	}

	return 0;
}