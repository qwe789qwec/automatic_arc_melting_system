#include "plc_control/plc_node.hpp"
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
    
    if (message != current_step_){
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
    }
    
    if (message != current_step_) {
        current_step_ = message;
        
        bool action_result = plc_->make_action(message);
        if (action_result) {
            call_process_service("plc standby");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}

bool PlcSystem::call_process_service(const std::string& action)
{
    // set timeout
    const std::chrono::seconds timeout(3);
    
    // wait for the service to be available
    if (!process_client_->wait_for_service(timeout))
    {
        RCLCPP_ERROR(this->get_logger(), "Process service not available after timeout");
        return false;
    }
    
    // create a request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // send the request asynchronously
    auto future = process_client_->async_send_request(request);
    
    // wait for the result
    std::future_status status = future.wait_for(timeout);
    
    if (status == std::future_status::ready) {
        try {
            auto result = future.get();
            RCLCPP_INFO(this->get_logger(), "Service result: %s", result->result.c_str());
            return true;
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception getting result: %s", e.what());
            return false;
        }
    }
    else {
        RCLCPP_ERROR(this->get_logger(), "Service call timed out");
        return false;
    }
}