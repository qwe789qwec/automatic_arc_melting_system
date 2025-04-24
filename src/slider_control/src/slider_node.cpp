#include "slider_control/slider_node.hpp"
#include "ros2_utils/service_utils.hpp"
#include <string>
#include <future>
#include <thread>

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
    
    if (message.compare(current_step_) != 0) {
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
        current_step_ = message;
        
        bool action_result = slider_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "slider_standby", "Process");
            
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error cannot make action");
        }
    }
}