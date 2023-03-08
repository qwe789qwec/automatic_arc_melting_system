#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <chrono>
#include <thread>

class tcp_socket {
	private:
		std::string ip;
		int port;
		int socket_fd;
		int connect_fd;

	public:
		std::string status;
		tcp_socket(std::string , int);
		int create();
		int write(std::string);
		int receive(std::string , char*);
		int end();
		int socket_type(int);
};

#endif