#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_format.hpp"

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

int set_socket(int socket_fd, int stat){
	int oldSocketFlag = fcntl(socket_fd, F_GETFL, 0);
	int newSocketFlag;
	if(stat == block){
		newSocketFlag = oldSocketFlag & (~O_NONBLOCK);
	}
	else if(stat == nonblock){
		newSocketFlag = oldSocketFlag | O_NONBLOCK;
	}

    if (fcntl(socket_fd, F_SETFL,  newSocketFlag) == -1) {
		// "\nset socket to nonblock error.\n"
        close(socket_fd);
        return -1;
    }
	return 0;
}

int creat_socket(std::string ip, int port){
	// struct timeval timeout;
	// fd_set readfds;
	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	// FD_ZERO(&readfds);
	// FD_SET(sock_fd, &readfds);
	// select(sock_fd+1, &readfds, NULL, NULL, &timeout);

	// int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket: %d", socket_fd);
	if (socket_fd < 0) {
		//"\n can't creat Socket\n"
		return -1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<= 0) {
		//"\nInvalid address/ Address not supported.\n"
		return -1;
	}

	int connect_fd = connect(socket_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (connect_fd < 0) {
		close(socket_fd);
		//"\nConnection Failed.\n"
        return -1;
    }

	return socket_fd;
}

int recv_socket(int socket_fd, char* message){
	if(set_socket(socket_fd, nonblock) < 0){
		return -1;
	}

	int errorTimes = 0;
	int strlen = 0;
	char buffer[1024];
	while(true) {
        strlen = read(socket_fd, buffer, sizeof(buffer));
		if (strlen > 0){
			printf("read len: %d\n", strlen);
			strcpy(message, buffer);
			printf("buffer: %s\n", message);
			errorTimes = 0;
		}
		else if(strlen == 0){
			break;
		}
		else {
			sleep(3);
			errorTimes++;
			if(errorTimes >= 3){
				close(socket_fd);
				// "\ntime out\n"
				return -1;
			}
			else{
				printf("recv failed\n");
			}
		}
    }
	return 1;
}

void sock_handle(const std::shared_ptr<tcp_format::srv::SocketFormat::Request>		request,
					std::shared_ptr<tcp_format::srv::SocketFormat::Response>	response)
{
	std::string ip, action, message;
	int port_fd;
	ip = request->target_ip;
	port_fd = request->port_fd;
	action = request->action;
	message = request->send_message;
	response->status = "init status";
	response->receive_message = "init msg";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip address: %s", ip.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port: %d", port_fd);
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send message: %s", message.c_str());

	if(action.compare("creat") == 0){
		int socket_fd = creat_socket(ip, port_fd);;
		if(socket_fd < 0){
			response->status = "socket creat/connect error";
			response->receive_message = "no message";
			return;
		}
		else{
			response->socket_fd = socket_fd;
			response->status = "socket creat/connect success";
			response->receive_message = "no message";
		}
	}

	if(action.compare("send") == 0){
		char* message2char = strcpy(new char[message.length() + 1], message.c_str());
		if(send(port_fd, message2char, strlen(message2char), 0) < 0){
			response->status = "send message error";
			response->receive_message = "no message";
			return;
		}
		if(recv_socket(port_fd, message2char) < 0){
			response->status = "recv message error";
			response->receive_message = "no message";
			return;
		}
		else{
			response->status = "send and recv message";
			response->receive_message = message2char;
		}
	}

	if(action.compare("close") == 0){
		if(close(port_fd) < 0){
			response->status = "close socket error";
			response->receive_message = "no message";
			return;
		}
		else{
			response->status = "close socket";
			response->receive_message = "no message";
		}
	}
	return;
}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<tcp_format::srv::SocketFormat>::SharedPtr service =
    node->create_service<tcp_format::srv::SocketFormat>("socket_format", &sock_handle);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send massage");

	rclcpp::spin(node);
	rclcpp::shutdown();
}