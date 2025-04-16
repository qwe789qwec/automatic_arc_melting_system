#include "main_process/main_process_node.hpp"

using namespace std::chrono_literals;

MainProcessNode::MainProcessNode(const std::string& node_name, bool is_test_mode)
    : Node(node_name), process_controller_(is_test_mode), last_published_step_("") {
    
    // Create service
    process_service_ = create_service<msg_format::srv::ProcessService>(
        "process_service",
        std::bind(&MainProcessNode::processServiceCallback, this, 
                  std::placeholders::_1, std::placeholders::_2));
                  
    // Create publisher for current step
    step_publisher_ = create_publisher<msg_format::msg::ProcessMsg>("topic", 10);
    
    // Setup timer to periodically publish current step
    publish_timer_ = create_wall_timer(1s, 
        std::bind(&MainProcessNode::publishCurrentStep, this));
        
    RCLCPP_INFO(get_logger(), "Main process node initialized");
    RCLCPP_INFO(get_logger(), "Starting with step: %s", process_controller_.getCurrentStep().c_str());
    RCLCPP_INFO(get_logger(), "Running in %s mode", 
               process_controller_.isTestMode() ? "TEST" : "PRODUCTION");
}

void MainProcessNode::processServiceCallback(
    const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
    std::shared_ptr<msg_format::srv::ProcessService::Response> response) {
    
    std::string action = request->action;
    RCLCPP_INFO(get_logger(), "Service request received: %s", action.c_str());
    
    // Update device status
    process_controller_.processDeviceAction(action);
    
    // Check if all devices are in standby state
    if (process_controller_.areAllDevicesStandby()) {
        // Process next step
        std::string result = process_controller_.moveToNextStep();
        response->result = result;
        
        if (result == "OK") {
            RCLCPP_INFO(get_logger(), "Moving to next step: %s", 
                       process_controller_.getCurrentStep().c_str());
        } else if (result == "Finished") {
            RCLCPP_INFO(get_logger(), "Process sequence completed");
        } else {
            RCLCPP_ERROR(get_logger(), "Error processing step: %s", result.c_str());
        }
    } else {
        // Devices not ready yet
        response->result = "Waiting for devices";
        RCLCPP_INFO(get_logger(), "Waiting for all devices to be ready");
    }
}

void MainProcessNode::publishCurrentStep() {
    // Get current step
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