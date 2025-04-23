#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "weighing_control/weighing_machine.hpp"
#include "tcp_handle/tcp_socket.hpp"
#include "ros2_utils/service_utils.hpp"

weighing_machine::weighing_machine(std::string ip, int port)
{   
	weiging_tcp.connect(ip, port);
    data_flag = false;
}

bool weighing_machine::frontdoor(bool state)
{
	if(state == opendoor){
        weiging_tcp.write("QRA 60 7 3\r\n"); // open
    }
    else if(state == closedoor){
        weiging_tcp.write("QRA 60 7 2\r\n"); // close
    }

	return weiging_tcp.check_receive("QRA 60 7 A", 6);
}

bool weighing_machine::dosinghead(bool state)
{
	if(state == lock_dose){
        weiging_tcp.write("QRA 60 2 4\r\n"); // lock dosing head
    }
    else if(state == unlock_dose){
        weiging_tcp.write("QRA 60 2 3\r\n"); // unlock dosing head
    }

	return weiging_tcp.check_receive("QRA 60 2 A", 6);
}

bool weighing_machine::setgram(std::string gram)
{
    std::string message = "QRD 1 1 5 " + gram + "\r\n";
	weiging_tcp.write(message); // set gram
	return weiging_tcp.check_receive("QRD 1 1 5 A", 6);
}

bool weighing_machine::startdosing()
{
    weiging_tcp.write("QRA 61 1\r\n"); // dosing
    if (weiging_tcp.check_receive("QRA 61 1 A", 200)){
        data_flag = true;
        return true;
    }
    else{
        data_flag = false;
        return false;
    }
}

std::string weighing_machine::getsampledata()
{
    weiging_tcp.write("QRD 2 4 12\r\n"); // ask for gram value
    std::string receivemessage;
    auto start_time = std::chrono::steady_clock::now();
    while (true)
    {
        if (weiging_tcp.receive(receivemessage))
        {   receivemessage = takedata(receivemessage, "<Content Unit=\"mg\">", "</Content>");
            if(receivemessage.compare("none") != 0){
                return receivemessage;
            }
        }
        if (std::chrono::steady_clock::now() - start_time >= std::chrono::seconds(9))
        {
            printf("take data timeout");
            return "take data timeout";
        }
    }
    if (weiging_tcp.check_receive("QRD 2 4 12 A", 5)){
        data_flag = false;
        return receivemessage;
    }
    else{
        return "error";
    }
}

std::string weighing_machine::takedata(const std::string& xml_data,  std::string start, std::string end) {

    // find target
    size_t start_pos = xml_data.find(start);
    if (start_pos != std::string::npos) {
        start_pos += start.length();
        size_t end_pos = xml_data.find(end, start_pos);
        if (end_pos != std::string::npos) {
            // get gram value
            return xml_data.substr(start_pos, end_pos - start_pos);
        }
    }
    
    return "none";
}

bool weighing_machine::make_action(std::string step)
{	
	std::string action = service_utils::get_command(step, "weighing");
	if(action.compare("error") == 0){
		return false;
	}

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
        //remove the "mgram" from the string
        action = action.substr(5);
        usleep(1000 * 1000 * 3);
		frontdoor(closedoor);
        dosinghead(lock_dose);
        setgram(action);
        startdosing();
        dosinghead(unlock_dose);
		frontdoor(opendoor);
    }
	else if(action.find("Tmgram") == 0){
        //remove the "Tmgram" from the string
        action = action.substr(6);
        dosinghead(lock_dose);
        setgram(action);
        startdosing();
        dosinghead(unlock_dose);
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