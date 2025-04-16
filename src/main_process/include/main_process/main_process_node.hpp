#ifndef MAIN_PROCESS_NODE_HPP
#define MAIN_PROCESS_NODE_HPP

#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "main_process/process_control.hpp"

/**
 * @brief Main process node class that handles ROS services and message publishing
 */
class MainProcessNode : public rclcpp::Node {
    public:
        /**
         * @brief Constructor
         * @param node_name The name of the node
         * @param is_test_mode Whether to run in test mode
         */
        explicit MainProcessNode(const std::string& node_name, bool is_test_mode = true);
        
    private:
        // Process controller
        ProcessController process_controller_;
        
        // Last published step (to reduce logging)
        std::string last_published_step_;
        
        // Service, publisher, and timer
        rclcpp::Service<msg_format::srv::ProcessService>::SharedPtr process_service_;
        rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr step_publisher_;
        rclcpp::TimerBase::SharedPtr publish_timer_;
        
        /**
         * @brief Service callback handler
         */
        void processServiceCallback(
            const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
            std::shared_ptr<msg_format::srv::ProcessService::Response> response);
        
        /**
         * @brief Publish the current step
         */
        void publishCurrentStep();
};

#endif // MAIN_PROCESS_NODE_HPP