#ifndef PLC_SYSTEM_H
#define PLC_SYSTEM_H

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
        std::string process_service_;
        std::string subscription_name_;
        std::string current_command_;
        
        // plc control
        std::unique_ptr<plc> plc_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // async plc control state
        std::future<bool> plc_future_;
        bool plc_future_valid_ = false;

        // callback functions
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
};

#endif // PLC_SYSTEM_H