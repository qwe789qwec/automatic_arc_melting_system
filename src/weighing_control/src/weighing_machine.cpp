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
        weiging_tcp.write("QRA 60 7 3\r\n"); // open
    else if(state == closedoor)
        weiging_tcp.write("QRA 60 7 2\r\n"); // close
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
    weiging_tcp.check_receive("QRA 61 1 A", 200);
    // <Content Unit="mg">0.000000</Content>
	return ;
}

bool weighing_machine::make_action(std::string step)
{	
	std::string action = weiging_tcp.get_action(step, "weighing");
	if(action.compare("error") == 0 && step.compare("init") != 0){
		return false;
	}
	else if (step.compare("init") == 0){
		action = "init";
	}

	printf("action: %s\n", action.c_str());
	printf("step: %s\n", step.c_str());

	if(action.compare("init") == 0){
		printf("start init in sub process");
        frontdoor(closedoor);
	}
	else if(action.compare("open") == 0){
		frontdoor(opendoor);
	}
	else if(action.compare("close") == 0){
		frontdoor(closedoor);
	}
    else if(action.find("mgram") == 0){
        //remove the "gram" from the string
        action = action.substr(5);
		frontdoor(closedoor);
        dosinghead(lock);
        setgram(action);
        startdosing();
        dosinghead(unlock);
		frontdoor(opendoor);
    }
	else if(action.find("Tmgram") == 0){
        //remove the "gram" from the string
        action = action.substr(6);
        dosinghead(lock);
        setgram(action);
        startdosing();
        dosinghead(unlock);
    }
    else{
        return false;
    }

	return true;
}

weighing_machine::~weighing_machine()
{
	weiging_tcp.close();
}