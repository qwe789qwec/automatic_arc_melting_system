#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "main_process/main_process_node.hpp"

int main(int argc, char *argv[]) {
    // Disable stdout buffering
    setvbuf(stdout, nullptr, _IONBF, BUFSIZ);
    
    // Initialize ROS2
    rclcpp::init(argc, argv);
    
    // Parse command line arguments to determine test mode
    bool test = true;  // Default to test mode
    std::string command = "init";
    if (test && argc > 1) {
        std::string command = argv[1];
    }
    
    // Create main process node
    auto main_process_node = std::make_shared<MainProcessNode>("main_process", command);
    
    // Create executor and add node
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(main_process_node);
    
    // Start execution
    RCLCPP_INFO(rclcpp::get_logger("main"), "Starting main process...");
    executor.spin();
    
    // Shutdown ROS2
    rclcpp::shutdown();
    return 0;
}