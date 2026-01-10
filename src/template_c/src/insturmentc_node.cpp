#include "template_c/instrumentc_node.hpp"
#include "ros2_utils/service_utils.hpp"
#include <iostream>
#include <iomanip>

InstrumentCSystem::InstrumentCSystem() : Node("instrumentc_system")
{    
    // initialize parameters
    insturmentc_ip_ = "192.168.0.999"; // Set your instrument's IP address
    insturmentc_port_ = 7777; // Set your instrument's port
    current_step_ = "insturmentc init";
    
    // initialize insturment
    insturmentc_ = std::make_unique<instrumentc>(insturmentc_ip_, insturmentc_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&InstrumentSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "InstrumentC initialized");
}

bool InstrumentSystem::test_instrumentc_action(const std::string& action_param)
{
    instrumentc test_instrumentc(insturment_ip_, insturment_port_);
    std::string test_action = "Instrumentc_" + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_instrumentc.make_action(test_action);
}

void InstrumentSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    
    if (message.compare(current_step_) != 0) {
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
        current_step_ = message;
        
        bool action_result = instrumentc_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "instrumentc_standby", "Process");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}