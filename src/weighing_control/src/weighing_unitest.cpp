#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "weighing_control/weighing_machine.hpp"
#include <unistd.h>

#include <memory>

std::string weighing_ip = "192.168.0.2";
int weighing_port = 8001;
weighing_machine weighing(weighing_ip, weighing_port);

std::string first_material = "396.7";
std::string second_material = "103.3";

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    weighing.frontdoor(closedoor);
    weighing.dosinghead(lock);
    weighing.setgram(first_material);
    weighing.startdosing();
    weighing.dosinghead(unlock);
    weighing.frontdoor(opendoor);

    rclcpp::shutdown();
}
