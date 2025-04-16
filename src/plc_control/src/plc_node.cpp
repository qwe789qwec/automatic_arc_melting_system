#include "plc_control/plc_node.hpp"
#include "ros2_utils/service_utils.hpp"
#include <iostream>
#include <iomanip>

PlcSystem::PlcSystem() : Node("plc_system")
{    
    // initialize parameters
    plc_ip_ = "192.168.0.5";
    plc_port_ = 9528;
    current_step_ = "plc init";
    
    // initialize plc
    plc_ = std::make_unique<plc>(plc_ip_, plc_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&PlcSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "PlcSystem initialized");
}

bool PlcSystem::test_plc_action(const std::string& action_param)
{
    plc test_plc("192.168.0.5", 9528);
    std::string test_action = "plc " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_plc.make_action(test_action);
}

void PlcSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    
    if (message.compare(current_step_) != 0) {
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
        current_step_ = message;
        
        bool action_result = plc_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "plc standby", "Process");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}