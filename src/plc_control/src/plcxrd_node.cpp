#include "plc_control/plcxrd_node.hpp"
#include "ros2_utils/service_utils.hpp"
#include <iostream>
#include <iomanip>

PlcxrdSystem::PlcxrdSystem() : Node("plcxrd_system")
{    
    // initialize parameters
    plcxrd_ip_ = "192.168.0.4";
    plcxrd_port_ = 9528;
    current_step_ = "plcxrd_init";
    
    // initialize plc
    plcxrd_ = std::make_unique<plcxrd>(plcxrd_ip_, plcxrd_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&PlcxrdSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "PlcxrdSystem initialized");
}

bool PlcxrdSystem::test_plc_action(const std::string& action_param)
{
    plcxrd test_plc("192.168.0.4", 9528);
    std::string test_action = "plcxrd " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_plc.make_action(test_action);
}


void PlcxrdSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    
    if (message.compare(current_step_) != 0) {
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
        current_step_ = message;
        
        bool action_result = plcxrd_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "plcxrd_standby", "Process");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}