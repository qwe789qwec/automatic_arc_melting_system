#ifndef INSTRUMENT_NODE_H
#define INSTRUMENT_NODE_H

#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "template_c/instrumentc.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class InstrumentCSystem : public rclcpp::Node
{
    public:
        InstrumentCSystem();
        ~InstrumentCSystem() = default;

        // test plc action
        static bool test_instrumentc_action(const std::string& action_param);

    private:
        // parameters
        std::string instrumentc_ip_;
        int instrumentc_port_;
        std::string current_step_;
        
        // instrument control
        std::unique_ptr<instrument> instrumentc_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // callback functions
        void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
};

#endif // INSTRUMENT_NODE_H