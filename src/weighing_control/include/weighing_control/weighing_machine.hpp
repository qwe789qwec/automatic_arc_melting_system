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
    
    bool front_door(bool state);
    bool dosing_head(bool state);
    bool set_gram(std::string gram);
    bool start_dosing();
    std::string take_data(const std::string& xml_data, std::string start, std::string end);
    std::string get_action(std::string step);
    
    tcp_socket weiging_tcp;
};

#endif // WEIGHING_MACHINE_HPP