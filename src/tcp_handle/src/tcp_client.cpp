#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/process_service.hpp"

#include <memory>

#include <chrono>
#include <thread>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

#define nonblock 0
#define block 1

int set_socket(int socket_fd, int stat)
{
	int oldSocketFlag = fcntl(socket_fd, F_GETFL, 0);
	int newSocketFlag = oldSocketFlag | O_NONBLOCK;
	if (stat == block)
	{
		newSocketFlag = oldSocketFlag & (~O_NONBLOCK);
	}

	if (fcntl(socket_fd, F_SETFL, newSocketFlag) == -1)
	{
		// "\nset socket fd error.\n"
		close(socket_fd);
		return -1;
	}
	return socket_fd;
}

int creat_socket(std::string ip, std::string port)
{
	// struct timeval timeout;
	// fd_set readfds;
	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	// FD_ZERO(&readfds);
	// FD_SET(sock_fd, &readfds);
	// select(sock_fd+1, &readfds, NULL, NULL, &timeout);

	// int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket: %d\n", socket_fd);
	if (socket_fd < 0)
	{
		//"\n can't creat Socket\n"
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(stoi(port));
	if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
	{
		//"\nInvalid address/ Address not supported.\n"
		return -1;
	}

	int connect_fd = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connect_fd < 0)
	{
		//"\nConnection Failed.\n"
		close(socket_fd);
		return -1;
	}

	return socket_fd;
}

int recv_socket(int socket_fd, char* cmpmessage, char getmessage[])
{
	if (set_socket(socket_fd, nonblock) < 0)
	{
		close(socket_fd);
		return -1;
	}

	int strlen = 0;
	bool testflag = false;
	char buffer[1024];
	if (strcmp(cmpmessage, "test\r\n") == 0)
		testflag = true;
	int timeout_seconds = 9;
	std::chrono::seconds timeout(timeout_seconds);
	auto start_time = std::chrono::steady_clock::now();
	while (true)
	{
		strlen = read(socket_fd, buffer, sizeof(buffer));
		if (strlen > 0)
		{
			printf("read len: %d\n", strlen);
			printf("buffer: %s\n", buffer);
			strcpy(getmessage, buffer);
			if (strcmp(buffer, cmpmessage) == 0)
			{
				printf("right message");
				break;
			}
		}
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
	if (set_socket(socket_fd, block) < 0)
	{
		close(socket_fd);
		return -1;
	}
	return socket_fd;
}

void sock_handle(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
				 std::shared_ptr<msg_format::srv::ProcessService::Response> response)
{
	std::string ip, port, message;
	std::stringstream ss(request->action);
	response->result = "init status";
	ss >> ip;
	ss >> port;
	getline(ss, message);
	message = message + "\r\n";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip address: %s", ip.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port: %s", port.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());

	int socket_fd = creat_socket(ip, port);
	if (socket_fd < 0)
	{
		response->result = "socket creat/connect error";
		return;
	}

	char *message2char = strcpy(new char[message.length() + 1], message.c_str());
	if (send(socket_fd, message2char, strlen(message2char), 0) < 0)
	{
		response->result = "send message error";
		return;
	}

	char *cmpmessage = "test\r\n";
	char getmessage[1024];
	if (recv_socket(socket_fd, cmpmessage, getmessage) < 0)
	{
		if (close(socket_fd) < 0)
		{
			response->result = "recv message error and close socket error";
			return;
		}
		response->result = "recv message error and close socket";
		return;
	}
	response->result = getmessage;
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "recv message: %s", getmessage);

	if (close(socket_fd) < 0)
	{
		response->result = "close socket error";
		return;
	}
	return;
}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<msg_format::srv::ProcessService>::SharedPtr service =
		node->create_service<msg_format::srv::ProcessService>("process_service", &sock_handle);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send massage");

	rclcpp::spin(node);
	rclcpp::shutdown();
}