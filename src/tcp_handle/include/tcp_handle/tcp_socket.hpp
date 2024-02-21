#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <chrono>
#include <thread>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>

class tcp_socket
{
public:
	tcp_socket();
	bool set_blocking(bool);
	bool connect(const std::string &, const int &);
	bool write(const std::string &);
	bool writeRaw(const void*, int);
	bool receive(std::string &);
	bool receiveRaw(char* &, int &);
	bool check_receive(std::string, int);
	std::string get_action(std::string, std::string);
	void close();
	~tcp_socket();

private:
	int socket_fd;
	std::string ip;
	int port;
	struct sockaddr_in server;
	bool is_blocking = true;
};

#endif