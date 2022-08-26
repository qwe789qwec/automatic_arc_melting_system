#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_creat.hpp"

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

void creat_socket(const std::shared_ptr<tcp_format::srv::SocketCreat::Request>		request,
					std::shared_ptr<tcp_format::srv::SocketCreat::Response>	response){
	// struct timeval timeout;
	// fd_set readfds;
	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	// FD_ZERO(&readfds);
	// FD_SET(sock_fd, &readfds);
	// select(sock_fd+1, &readfds, NULL, NULL, &timeout);

	// int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);

	std::string ip_address = request->target_ip;
	std::string port = request->target_port;
	response->status = "init";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip address: %s", ip_address.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port: %s", port.c_str());

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_fd < 0){
		//can't creat Socket
		response->status = "Can't creat Socket.\n";
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(std::stoi(port));
	if (inet_pton(AF_INET, ip_address.c_str(), &serv_addr.sin_addr)<= 0){
		//Invalid address/ Address not supported.
		response->status = "Invalid address/ Address not supported.\n";
	}

	int connect_fd = connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (connect_fd < 0) {
		close(sock_fd);
		//socket connect error
        response->status = "Socket connect error.\n";
    }

	response->status = "Scoket creat success";
	response->socket_fd = sock_fd;
}

int main(int argc, char **argv){
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<tcp_format::srv::SocketCreat>::SharedPtr service =
    node->create_service<tcp_format::srv::SocketCreat>("socket_creat", &creat_socket);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to creat socket");

	rclcpp::spin(node);
	rclcpp::shutdown();
}