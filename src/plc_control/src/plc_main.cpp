#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "plc_control/plc_system.hpp"
#include "ros2_utils/service_utils.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test plc action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        PlcSystem::test_plc_action(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<PlcSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

PlcSystem::PlcSystem() : Node("plc_system")
{    
    // initialize parameters
    plc_ip_ = "192.168.0.5";
    plc_port_ = 9528;
    current_command_ = "plcsys_init";
    process_service_ = "Process_service";
    subscription_name_ = "topic";

    // initialize plc
    plc_ = std::make_unique<plc>(plc_ip_, plc_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>(process_service_);
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        subscription_name_, 10, std::bind(&PlcSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "PlcSystem initialized");
}

bool PlcSystem::test_plc_action(const std::string& action_param)
{
    plc test_plc("192.168.0.5", 9528);
    std::string test_action = "plc_" + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_plc.make_action(test_action);
}

void PlcSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    std::string command = service_utils::get_command(message, "plc");

    // still busy with previous PLC task
    if (plc_future_valid_ && 
        plc_future_.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
    {
        RCLCPP_INFO(this->get_logger(), "PLC busy, calling plc_action...");
        service_utils::call_service_async(
            process_client_, this->get_logger(), "plc_action", process_service_);
        return;
    }

    // previous PLC task finished, check result
    if (plc_future_valid_)
    {
        try {
            bool last_result = plc_future_.get();
            if (last_result) {
                RCLCPP_INFO(this->get_logger(), "PLC finished successfully, calling plc_standby");
                plc_future_valid_ = false;
                service_utils::call_service_async(
                    process_client_, this->get_logger(), "plc_standby", process_service_);
            } else {
                RCLCPP_ERROR(this->get_logger(), "PLC finished with error, calling plc_error");
                service_utils::call_service_async(
                    process_client_, this->get_logger(), "plc_error", process_service_);
            }
        } catch (const std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Exception getting future: %s", e.what());
            service_utils::call_service_async(
                process_client_, this->get_logger(), "plc_error", process_service_);
        }
    }

    if (command.compare(current_command_) != 0) {
        RCLCPP_INFO(this->get_logger(), "get command: %s", command.c_str());
        current_command_ = command;

        // start new PLC task
        RCLCPP_INFO(this->get_logger(), "Starting new PLC task...");
        plc_future_ = plc_->make_action_async(command);
        plc_future_valid_ = true;
    }
}