#include "weighing_control/weighing_node.hpp"

WeighingSystem::WeighingSystem() : Node("weighing_system")
{
    // initialize parameters
    weighing_ip_ = "192.168.0.2";
    weighing_port_ = 8001;
    first_material_ = "396.7";
    second_material_ = "103.3";
    current_step_ = "weighing init";
    
    // initialize weighing machine
    weighing_ = std::make_unique<weighing_machine>(weighing_ip_, weighing_port_);
    
    // create clients
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    data_client_ = this->create_client<msg_format::srv::ProcessService>("write_data");
    
    // create subscriber
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&WeighingSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "WeighingSystem initialized");
}

bool WeighingSystem::test_weighing_machine(const std::string& action_param)
{
    weighing_machine weighing("192.168.0.2", 8001);
    std::string test_action = "weighing " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return weighing.make_action(test_action);
}

void WeighingSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{
    std::string message = msg->process;
    
    if (message != current_step_){
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
    }
    
    if (message.compare(current_step_) != 0) {
        current_step_ = message;
        
        bool action_result = weighing_->make_action(message);
        if (action_result) {
            call_process_service("weighing standby");
            if (weighing_->data_flag) {
                std::string gramdata = weighing_->getsampledata();
                call_data_service(gramdata + " mg");
            }
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error cannot make action");
        }
    }
}

bool WeighingSystem::call_process_service(const std::string& action)
{
    // set timeout
    const std::chrono::seconds timeout(3);
    
    // wait for the service to be available
    if (!process_client_->wait_for_service(timeout))
    {
        RCLCPP_ERROR(this->get_logger(), "Process service not available after timeout");
        return false;
    }
    
    // create a request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // send the request asynchronously
    auto future = process_client_->async_send_request(request);
    
    // wait for the result
    std::future_status status = future.wait_for(timeout);
    
    if (status == std::future_status::ready) {
        try {
            auto result = future.get();
            RCLCPP_INFO(this->get_logger(), "Service result: %s", result->result.c_str());
            return true;
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception getting result: %s", e.what());
            return false;
        }
    }
    else {
        RCLCPP_ERROR(this->get_logger(), "Service call timed out");
        return false;
    }
}

bool WeighingSystem::call_data_service(const std::string& action)
{   
    // set timeout
    const std::chrono::seconds timeout(3);

    if (!data_client_->wait_for_service(3s)) {
        RCLCPP_ERROR(this->get_logger(), "Data service not available");
        return false;
    }
    
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    auto future = data_client_->async_send_request(request);
    
    // wait for the result
    std::future_status status = future.wait_for(timeout);
    
    if (status == std::future_status::ready) {
        try {
            auto result = future.get();
            RCLCPP_INFO(this->get_logger(), "Service result: %s", result->result.c_str());
            return true;
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception getting result: %s", e.what());
            return false;
        }
    }
    else {
        RCLCPP_ERROR(this->get_logger(), "Service call timed out");
        return false;
    }
}