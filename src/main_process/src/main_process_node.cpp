#include "main_process/main_process_node.hpp"
#include <functional>

// External variable declared in main.cpp that stores current step
extern std::string step;

using namespace std::chrono_literals;

MainProcessNode::MainProcessNode(const std::string& name, const std::string& topic)
    : Node(name), last_message_("") {
    
    // Create publisher
    publisher_ = this->create_publisher<msg_format::msg::ProcessMsg>(topic, 10);
    
    // Create timer that calls the callback at 1Hz
    timer_ = this->create_wall_timer(
        1s, std::bind(&MainProcessNode::timerCallback, this));
        
    RCLCPP_INFO(this->get_logger(), "Process publisher initialized");
}

void MainProcessNode::timerCallback() {
    // Create message
    auto msg = std::make_unique<msg_format::msg::ProcessMsg>();
    msg->process = step;
    
    // Log changes to reduce console spam
    if (msg->process != last_message_) {
        RCLCPP_INFO(this->get_logger(), "Publishing new step: %s", msg->process.c_str());
        last_message_ = msg->process;
    }
    
    // Publish message
    publisher_->publish(std::move(msg));
}