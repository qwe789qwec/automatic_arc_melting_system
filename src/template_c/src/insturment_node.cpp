#include "template_c/instrument_node.hpp"
#include "ros2_utils/service_utils.hpp"
#include <iostream>
#include <iomanip>

InstrumentSystem::InstrumentSystem() : Node("instrument_system")
{    
    // initialize parameters
    insturment_ip_ = "192.168.0.999"; // Set your instrument's IP address
    insturment_port_ = 7777; // Set your instrument's port
    current_step_ = "insturment init";
    
    // initialize insturment
    insturment_ = std::make_unique<instrument>(insturment_ip_, insturment_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&InstrumentSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "Instrument initialized");
}

bool InstrumentSystem::test_instrument_action(const std::string& action_param)
{
    instrument test_instrument(insturment_ip_, insturment_port_);
    std::string test_action = "Instrument_" + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_instrument.make_action(test_action);
}

void InstrumentSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    
    if (message.compare(current_step_) != 0) {
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
        current_step_ = message;
        
        bool action_result = instrument_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "Instrument_standby", "Process");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}