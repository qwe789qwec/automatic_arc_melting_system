#include "slider_control/slider_node.hpp"
#include <string>

using std::placeholders::_1;
using namespace std::chrono_literals;

SliderNode::SliderNode(slider& slider_controller)
    : Node("slider_node"), slider_(slider_controller)
{
    // initialize the subscriber
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&SliderNode::topic_callback, this, _1));
        
    // initialize the client
    client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
}

void SliderNode::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{
    std::string message = msg->process;
    static std::string step = "slider init";

    RCLCPP_INFO(this->get_logger(), "message: %s", message.c_str());
    RCLCPP_INFO(this->get_logger(), "step: %s", step.c_str());
    
    if(message.compare(step) != 0){
        step = message;
        RCLCPP_INFO(this->get_logger(), "step message: %s", message.c_str());
        bool action_result = slider_.make_action(message);
        if(!action_result){
            RCLCPP_INFO(this->get_logger(), "error cannot make action");
        }
        else{
            send_slider_client_request("slider standby");
        }
    }
}

bool SliderNode::send_slider_client_request(const std::string& action)
{
    // check if the client is ready
    if (!client_->wait_for_service(3s)) {
        RCLCPP_ERROR(this->get_logger(), "Service not available");
        return false;
    }
    
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // send the request
    auto result_future = client_->async_send_request(request);
    
    // wait for the result
    if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(this->get_logger(), "result: %s", result_future.get()->result.c_str());
        return true;
    }
    else
    {
        RCLCPP_ERROR(this->get_logger(), "Failed to call service");
        return false;
    }
}