#ifndef PLC_SOCKET_H
#define PLC_SOCKET_H

#include <chrono>
#include <thread>

class plc_socket {
	private:
		std::string ip;
		int port;
		int socket_fd;
		int connect_fd;

	public:
		std::string status;
		plc_socket(std::string plc_ip, int plc_port);
		int create();
		int write(char* message);
		int receive(char message[]);
		int end();
		int socket_type(int type);
};

#endif