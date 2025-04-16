#include "plc_control/plc_node.hpp"
#include <iostream>
#include <iomanip>

PlcSystem::PlcSystem() : Node("plc_system")
{    
    // 初始化参数
    plc_ip_ = "192.168.0.5";
    plc_port_ = 9528;
    current_step_ = "plc init";
    
    // 初始化PLC控制器
    plc_ = std::make_unique<plc>(plc_ip_, plc_port_);
    
    // 创建客户端
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // 创建订阅者
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&PlcSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "PlcSystem initialized");
}

bool PlcSystem::test_plc_action(const std::string& action_param)
{
    plc test_plc("192.168.0.5", 9528);
    std::string test_action = "plc " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_plc.make_action(test_action);
}

char* PlcSystem::modbus(const char* function, const char* component, const char* data)
{
    // Allocate memory for the message
    static char message[] = "\x00\x01\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00";
    message[7] = function[0];
    message[8] = component[0];
    message[9] = component[1];
    message[10] = data[0];
    message[11] = data[1];

    return message;
}

void PlcSystem::printchar(const char* message, int size)
{   
    std::cout << "size:" << std::dec << size << " message:";
    for (int i = 0; i < size; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') 
                 << static_cast<unsigned int>(static_cast<unsigned char>(message[i])) << " ";
    }
    std::cout << std::endl;
}

void PlcSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    
    // 仅在DEBUG级别显示频繁的消息
    RCLCPP_DEBUG(this->get_logger(), "Message: %s", message.c_str());
    RCLCPP_DEBUG(this->get_logger(), "Step: %s", current_step_.c_str());
    
    if (message != current_step_) {
        current_step_ = message;
        RCLCPP_INFO(this->get_logger(), "Processing new step: %s", message.c_str());
        
        bool action_result = plc_->make_action(message);
        if (action_result) {
            call_process_service("plc standby");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error executing action: %s", message.c_str());
        }
    }
}

bool PlcSystem::call_process_service(const std::string& action)
{   
    // check if the client is ready
    if (!process_client_->wait_for_service(3s)) {
        RCLCPP_ERROR(this->get_logger(), "Service not available");
        return false;
    }
    
    // make a request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // send the request asynchronously
    auto result_future = process_client_->async_send_request(request);
    
    // wait for the result
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