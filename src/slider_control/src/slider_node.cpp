#include "slider_control/slider_node.hpp"
#include <string>

using std::placeholders::_1;
using namespace std::chrono_literals;

SliderSystem::SliderSystem() : Node("slider_system")
{
    // initialize parameters
    slider_ip_ = "192.168.0.3";
    slider_port_ = 64511;
    current_step_ = "slider init";
    
    // initialize slider
    slider_ = std::make_unique<slider>(slider_ip_, slider_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&SliderSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "SliderSystem initialized");
}
    
bool SliderSystem::test_slider_action(const std::string& action_param)
{
    slider test_slider("192.168.0.3", 64511);
    std::string test_action = "slider " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_slider.make_action(test_action);
}

void SliderSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{
    std::string message = msg->process;
    
    if (message != current_step_){
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
    }
    
    if (message.compare(current_step_) != 0) {
        current_step_ = message;
        
        bool action_result = slider_->make_action(message);
        if (action_result) {
            call_process_service("slider standby");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error cannot make action");
        }
    }
}

bool SliderSystem::call_process_service(const std::string& action)
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