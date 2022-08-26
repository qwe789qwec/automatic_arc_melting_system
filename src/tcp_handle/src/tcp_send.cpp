#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_message.hpp"

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

void send_socket(const std::shared_ptr<tcp_format::srv::SocketMessage::Request>		request,
					std::shared_ptr<tcp_format::srv::SocketMessage::Response>	response)
{
	int sock_fd = request->socket_fd;
    std::string message = request->send_message;

	int oldSocketFlag = fcntl(sock_fd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag & (~O_NONBLOCK);
    if (fcntl(sock_fd, F_SETFL,  newSocketFlag) == -1){
        close(sock_fd);
        response->status = "set socket to nonblock error.\n";
    }

	response->status = "init status\n";
	response->receive_message = "init msg\n";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send message: %s", message.c_str());

	char *message2char = new char[message.length() + 1];
	strcpy(message2char, message.c_str());

	int send_fd = send(sock_fd, message2char, strlen(message2char), 0);

	if(send_fd < 0){
		response->status = "send message error.";
		return;
	}

	oldSocketFlag = fcntl(sock_fd, F_GETFL, 0);
    newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(sock_fd, F_SETFL,  newSocketFlag) == -1){
        close(sock_fd);
        response->status = "set socket to nonblock error.";
    }

	int errorTimes = 0;
	int strlen = 0;
	char buffer[1024];
	while(1) {
        strlen = read(sock_fd, buffer, sizeof(buffer));
		if (strlen > 0){
			printf("read len: %d\n", strlen);
			message = buffer;
			printf("message: %s\n", message.c_str());
			errorTimes = 0;
		}
		else if(strlen == 0){
			response->status = "finish send";
			break;
		}
		else {
			errorTimes++;
			if(errorTimes >= 3){
				close(sock_fd);
				response->status = "time out";
				break;
			}
			else{
				printf("recv failed");
				sleep(3);
			}
		}
    }

	response->receive_message = message;
}

int main(int argc, char **argv){
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<tcp_format::srv::SocketMessage>::SharedPtr service =
    node->create_service<tcp_format::srv::SocketMessage>("socket_message", &send_socket);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send massage");

	rclcpp::spin(node);
	rclcpp::shutdown();
}