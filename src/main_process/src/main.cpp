#include <chrono>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/process_service.hpp"
#include "main_process/process_control.hpp"
#include "main_process/main_process_node.hpp"

// Global variables for sharing state between nodes
std::string step = "slider init cobotta init weighing init plc init";
ProcessController process_controller(true); // Default to test mode

/**
 * @brief Service callback for processing requests
 */
void process_callback(
    const std::shared_ptr<msg_format::srv::ProcessService::Request> request,
    std::shared_ptr<msg_format::srv::ProcessService::Response> response)
{
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("service"), "Received action: %s", action.c_str());
    
    // Process the request
    std::string result = process_controller.processRequest(action);
    response->result = result;
    
    // Update global step variable for publisher
    step = process_controller.getCurrentStep();
    
    RCLCPP_INFO(rclcpp::get_logger("service"), "Result: %s, Step: %s", 
                result.c_str(), step.c_str());
}

int main(int argc, char* argv[])
{
    // Disable stdout buffering
    setvbuf(stdout, nullptr, _IONBF, BUFSIZ);
    
    // Initialize ROS2
    rclcpp::init(argc, argv);
    
    // Parse command line for test mode
    bool test_mode = true;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--production" || arg == "-p") {
            test_mode = false;
            break;
        }
    }
    
    // Initialize process controller with correct mode
    process_controller = ProcessController(test_mode);
    
    // Create multi-threaded executor for true parallelism
    rclcpp::executors::MultiThreadedExecutor executor;
    
    // Create service node
    auto service_node = rclcpp::Node::make_shared("process_server");
    auto service = service_node->create_service<msg_format::srv::ProcessService>(
        "process_service", &process_callback);
    executor.add_node(service_node);
    
    // Create publisher node
    auto publisher_node = std::make_shared<MainProcessNode>("process_publisher", "topic");
    executor.add_node(publisher_node);
    
    RCLCPP_INFO(rclcpp::get_logger("main"), "Starting arc melting system in %s mode...", 
               test_mode ? "TEST" : "PRODUCTION");
    
    // Start spinning
    executor.spin();
    
    // Shutdown
    rclcpp::shutdown();
    return 0;
}