#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_close.hpp"

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

void close_socket(const std::shared_ptr<tcp_format::srv::SocketClose::Request>		request,
					std::shared_ptr<tcp_format::srv::SocketClose::Response>	response)
{
	response->status = "init";

	close(request->socket_fd);
	response->status = "close the socket\n";
}

int main(int argc, char **argv){
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<tcp_format::srv::SocketClose>::SharedPtr service =
    node->create_service<tcp_format::srv::SocketClose>("socket_close", &close_socket);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to close socket_fd");

	rclcpp::spin(node);
	rclcpp::shutdown();
}