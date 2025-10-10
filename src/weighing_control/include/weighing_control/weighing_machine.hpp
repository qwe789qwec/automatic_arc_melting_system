#ifndef WEIGHING_MACHINE_HPP
#define WEIGHING_MACHINE_HPP

#include <string>
#include <vector>
#include "ros2_utils/instrument_node.hpp"

class weighing_machine : public InstrumentControl
{
public:
    weighing_machine(const std::string& ip, int port);
    ~weighing_machine();
    bool make_action(std::string step) override;

    std::string getsampledata();
    std::string write_datalog() override { return getsampledata(); };

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
    std::string last_material;
};

#endif // WEIGHING_MACHINE_HPP