#ifndef WEIGHING_MACHINE_HPP
#define WEIGHING_MACHINE_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include "tcp_handle/tcp_socket.hpp"

class weighing_machine
{
public:
    weighing_machine(std::string ip, int port);
    ~weighing_machine();
    
    bool make_action(std::string step);
    std::string getsampledata();

    bool data_flag;

private:
    enum DoorState {
        DOOR_OPEN = true,
        DOOR_CLOSE = false
    };
    
    enum DosingHeadState {
        DOSE_LOCK = true,
        DOSE_UNLOCK = false
    };
    
    bool frontdoor(bool state);
    bool dosinghead(bool state);
    bool setgram(std::string gram);
    bool startdosing();
    std::string takedata(const std::string& xml_data, std::string start, std::string end);
    
    tcp_socket weiging_tcp;
};

#endif // WEIGHING_MACHINE_HPP