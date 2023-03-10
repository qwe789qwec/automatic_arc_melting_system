#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "weighing_control/weighing_machine.hpp"
#include "tcp_handle/tcp_socket.hpp"

weighing_machine::weighing_machine(std::string ip, int port)
{   
	weiging_tcp.connect(ip, port);
}

void weighing_machine::frontdoor(bool state)
{
	if(state == opendoor)
        weiging_tcp.write("QRA 60 7 3\r\n"); // close
    else if(state == closedoor)
        weiging_tcp.write("QRA 60 7 2\r\n"); // open
    weiging_tcp.check_receive("QRA 60 7 A", 6);
	return ;
}

void weighing_machine::dosinghead(bool state)
{
	if(state == lock)
        weiging_tcp.write("QRA 60 2 4\r\n"); // lock dosing head
    else if(state == unlock)
        weiging_tcp.write("QRA 60 2 3\r\n"); // unlock dosing head
    weiging_tcp.check_receive("QRA 60 2 A", 6);
	return ;
}

void weighing_machine::setgram(std::string gram)
{
    std::string message = "QRD 1 1 5 " + gram + "\r\n";
	weiging_tcp.write(message); // set gram
    weiging_tcp.check_receive("QRD 1 1 5 A", 6);
	return ;
}

void weighing_machine::startdosing()
{
    weiging_tcp.write("QRA 61 1\r\n"); // dosing
    weiging_tcp.check_receive("QRA 61 1 A", 120);
	return ;
}

weighing_machine::~weighing_machine()
{
	weiging_tcp.close();
}