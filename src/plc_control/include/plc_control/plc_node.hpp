#ifndef PLC_NODE_H
#define PLC_NODE_H

#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "plc_control/plc.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class PlcSystem : public rclcpp::Node
{
    public:
        PlcSystem();
        ~PlcSystem() = default;

        // test plc action
        static bool test_plc_action(const std::string& action_param);

    private:
        // parameters
        std::string plc_ip_;
        int plc_port_;
        std::string current_step_;
        
        // plc control
        std::unique_ptr<plc> plc_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // callback functions
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
        bool call_process_service(const std::string& action);
};

#endif // PLC_NODE_H