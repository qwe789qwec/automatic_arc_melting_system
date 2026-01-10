#ifndef PLCXRD_NODE_H
#define PLCXRD_NODE_H

#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "plc_control/plcxrd.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class PlcxrdSystem : public rclcpp::Node
{
    public:
        PlcxrdSystem();
        ~PlcxrdSystem() = default;

        // test plc action
        static bool test_plc_action(const std::string& action_param);

    private:
        // parameters
        std::string plcxrd_ip_;
        int plcxrd_port_;
        std::string current_step_;
        
        // plc control
        std::unique_ptr<plcxrd> plcxrd_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // callback functions
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
};

#endif // PLC_NODE_H