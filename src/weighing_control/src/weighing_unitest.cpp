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

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    if(argv[1] == NULL){
        std::cout << "Please enter the weight" << std::endl;
        return 0;
    }

    weighing.frontdoor(closedoor);
    weighing.dosinghead(lock);
    weighing.setgram(argv[1]);
    weighing.startdosing();
    weighing.dosinghead(unlock);
    weighing.frontdoor(opendoor);

    rclcpp::shutdown();
}
