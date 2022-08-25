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

std::string send_socket(std::string ip, std::string port, char* message)
{
	// struct timeval timeout;
	// fd_set readfds;
	// timeout.tv_sec = 5;
	// timeout.tv_usec = 0;
	// FD_ZERO(&readfds);
	// FD_SET(sock_fd, &readfds);
	// select(sock_fd+1, &readfds, NULL, NULL, &timeout);

	// int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		return "\n can't creat Socket\n";
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(std::stoi(port));
	if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr)<= 0) {
		return "\nInvalid address/ Address not supported.\n";
	}

	int connect_fd = connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (connect_fd < 0) {
		close(sock_fd);
        return "\nConnection Failed.\n";
    }

	send(sock_fd, message, strlen(message), 0);

	int oldSocketFlag = fcntl(sock_fd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(sock_fd, F_SETFL,  newSocketFlag) == -1) {
        close(sock_fd);
        return "\nset socket to nonblock error.\n";
    }

	int errorTimes = 0;
	int strlen = 0;
	char buffer[1024];
	while(1) {
        strlen = read(sock_fd, buffer, sizeof(buffer));
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
				close(sock_fd);
				return "\ntime out\n";
			}
			else{
				printf("recv failed\n");
			}
		}
    }

	// closing the connected socket
	close(sock_fd);
	return "\nmessage sent close connect\n";
}

void showinfo(const std::shared_ptr<tcp_format::srv::SocketFormat::Request>		request,
					std::shared_ptr<tcp_format::srv::SocketFormat::Response>	response)
{
	std::string ip_address, port, message;
	ip_address = request->target_ip;
	port = request->target_port;
	message = request->send_message;
	response->error = "init error";
	response->receive_message = "init msg";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip address: %s", ip_address.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port: %s", port.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send message: %s", message.c_str());

	char* message2char = strcpy(new char[message.length() + 1], message.c_str());
	response->error = send_socket(ip_address, port, message2char);
	response->receive_message = message2char;
}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");

	rclcpp::Service<tcp_format::srv::SocketFormat>::SharedPtr service =
    node->create_service<tcp_format::srv::SocketFormat>("socket_format", &showinfo);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to send massage");

	rclcpp::spin(node);
	rclcpp::shutdown();
}