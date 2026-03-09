#ifndef MAIN_PROCESS_NODE_HPP
#define MAIN_PROCESS_NODE_HPP

#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "main_process/process_control.hpp"

class MainProcessNode : public rclcpp::Node {
public:
    explicit MainProcessNode(const std::string& node_name, std::string command = "init");
    
private:
    // Process controller
    ProcessController process_controller_;
    
    // Last published step (to reduce logging)
    std::string last_published_step_ = "start";

    // Current task ID for CSV workflow
    std::string current_task_id_;
    
    // Service for process control
    rclcpp::Service<msg_format::srv::ProcessService>::SharedPtr process_service_;

    // Publisher for current step
    rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr step_publisher_;

    // Publisher for task status (CSV workflow)
    rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr task_status_publisher_;

    // Timer for periodic publishing
    rclcpp::TimerBase::SharedPtr publish_timer_;
    
    void processServiceCallback(
        const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
        std::shared_ptr<msg_format::srv::ProcessService::Response> response);
    
    void publishCurrentStep();
    
    // Utility function to extract key-value pairs from action string
    static std::string get_kv(const std::string& action, const std::string& key);
};

#endif // MAIN_PROCESS_NODE_HPP