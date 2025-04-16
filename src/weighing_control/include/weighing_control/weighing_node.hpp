#ifndef WEIGHING_NODE_H
#define WEIGHING_NODE_H

#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "weighing_control/weighing_machine.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class WeighingSystem : public rclcpp::Node
{
    public:
        WeighingSystem();
        ~WeighingSystem() = default;

        // test weighing machine action
        static bool test_weighing_machine(const std::string& action_param);

    private:
        // parameters
        std::string weighing_ip_;
        int weighing_port_;
        std::string first_material_;
        std::string second_material_;
        std::string current_step_;
        
        // weighing machine control
        std::unique_ptr<weighing_machine> weighing_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr data_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // callback functions
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
        bool call_process_service(const std::string& action);
        bool call_data_service(const std::string& action);
};

#endif // WEIGHING_NODE_H