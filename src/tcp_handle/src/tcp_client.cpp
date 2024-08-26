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

class TcpClient
{
private:
	int sock;
	std::string address;
	int port;
	struct sockaddr_in server;
	bool is_blocking = true;

public:
	TcpClient() : sock(0), address(""), port(0)
	{
		memset(&server, 0, sizeof(server));
	}

	bool set_blocking(bool blocking)
	{
		int flags = fcntl(sock, F_GETFL, 0);
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
		return fcntl(sock, F_SETFL, flags) == 0;
	}

	bool connect(const std::string &address, const int &port)
	{
		this->address = address;
		this->port = port;

		// create socket
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0)
		{
			return false;
		}

		// set server information
		server.sin_family = AF_INET;
		server.sin_port = htons(port);
		if (inet_pton(AF_INET, address.c_str(), &server.sin_addr) <= 0)
		{
			return false;
		}

		// connect to server
		if (::connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
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

	bool send(const std::string &data)
	{
		int length = ::send(sock, data.c_str(), data.size(), 0);
		if (length < 0)
		{
			return false;
		}
		return true;
	}

	bool receive(std::string &data)
	{
		char buffer[1024] = {0};
		int length = ::recv(sock, buffer, 1024, 0);
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

	bool receive_timeout(std::string compare, int timeout_seconds)
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
			}
			if (std::chrono::steady_clock::now() - start_time >= timeout)
			{
				printf("test timeout");
				break;
			}
		}
		return true;
	}

	void close()
	{
		if (sock > 0)
		{
			::close(sock);
			sock = 0;
		}
		return;
	}

	~TcpClient()
	{
		close();
	}
};

void sock_handle(const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
				 std::shared_ptr<msg_format::srv::ProcessService::Response> response)
{
	std::string ip, port, message;
	// input "192.168.1.100 8080 Hello, World!"
	std::stringstream ss(request->action);
	response->result = "init status";
	ss >> ip;
	ss >> port;
	getline(ss, message);
	message = message + "\r\n";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip address: %s", ip.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port: %s", port.c_str());
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", message.c_str());

	TcpClient client;
	if (!client.connect(ip.c_str(), std::stoi(port)))
	{
		response->result = "socket creat/connect error";
		return;
	}

	client.send(message);

	std::string data;
	client.receive_timeout("QRA 60 7 A", 9);
	response->result = "QRA 60 7 A";
	data = "QRA 60 7 A";

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "recv message: %s", data.c_str());

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