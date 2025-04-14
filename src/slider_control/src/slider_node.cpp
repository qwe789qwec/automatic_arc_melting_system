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
    // 檢查client是否已連接到服務
    if (!client_->wait_for_service(3s)) {
        RCLCPP_ERROR(this->get_logger(), "Service not available");
        return false;
    }
    
    // 創建請求
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // 發送異步請求，但不使用 spin_until_future_complete
    // 以下是修改部分
    auto result_future = client_->async_send_request(request);
    
    // 使用更安全的等待方式
    auto future_status = result_future.wait_for(std::chrono::seconds(5));
    
    if (future_status == std::future_status::ready) {
        auto result = result_future.get();
        RCLCPP_INFO(this->get_logger(), "result: %s", result->result.c_str());
        return true;
    } else {
        RCLCPP_ERROR(this->get_logger(), "Failed to call service within timeout");
        return false;
    }
}