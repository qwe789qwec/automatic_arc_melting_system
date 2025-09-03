#include "main_process/main_process_node.hpp"

using namespace std::chrono_literals;

MainProcessNode::MainProcessNode(const std::string& node_name, std::string command)
    : Node(node_name), 
    process_controller_(command), 
    last_published_step_("") {
    
    // Create service
    process_service_ = create_service<msg_format::srv::ProcessService>(
        "process_service",
        std::bind(&MainProcessNode::processServiceCallback, this, 
                  std::placeholders::_1, std::placeholders::_2));
                  
    // Create publisher for current step
    step_publisher_ = create_publisher<msg_format::msg::ProcessMsg>("topic", 10);
    
    // Setup timer to periodically publish current step
    publish_timer_ = create_wall_timer(1.5s, 
        std::bind(&MainProcessNode::publishCurrentStep, this));
        
    RCLCPP_INFO(get_logger(), "Main process node initialized");
    RCLCPP_INFO(get_logger(), "Starting with step: %s", process_controller_.getCurrentStep().c_str());
}

void MainProcessNode::processServiceCallback(
    const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
    std::shared_ptr<msg_format::srv::ProcessService::Response> response) {
    
    std::string action = request->action;
    RCLCPP_INFO(get_logger(), "Service request received: %s", action.c_str());
    
    // Update device status
    std::string message = process_controller_.updateDeviceStatuses(action);
    response->result = message;
    RCLCPP_INFO(get_logger(), "Device status updated: %s", message.c_str());
}

void MainProcessNode::publishCurrentStep() {
    
    // Get current step
    if (process_controller_.isSequenceCompleted() && process_controller_.isReadyToNextStep()) {
        RCLCPP_INFO(get_logger(), "Process sequence completed");
    }
    else if (process_controller_.isReadyToNextStep()) {
        process_controller_.moveToNextStep();
    }
    std::string current_step = process_controller_.getCurrentStep();
    
    // Only log when step changes to reduce message volume
    if (current_step != last_published_step_) {
        RCLCPP_INFO(get_logger(), "Publishing step: %s", current_step.c_str());
        last_published_step_ = current_step;
    }
    
    // Publish current step
    auto msg = std::make_unique<msg_format::msg::ProcessMsg>();
    msg->process = current_step;
    step_publisher_->publish(std::move(msg));
}