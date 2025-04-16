#include "weighing_control/weighing_node.hpp"
#include "ros2_utils/service_utils.hpp"

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
    
    if (message.compare(current_step_) != 0) {
        current_step_ = message;
        
        bool action_result = weighing_->make_action(message);
        if (action_result) {
            // call process service
            auto future = service_utils::call_service_async(
                process_client_, this->get_logger(), "weighing standby", "Process");
                
            if (weighing_->data_flag) {
                std::string gramdata = weighing_->getsampledata();
                service_utils::call_service_async(
                    data_client_, this->get_logger(), gramdata + " mg", "Data");
            }
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error cannot make action");
        }
    }
}

bool WeighingSystem::call_process_service(const std::string& action)
{
    return service_utils::call_service(
        process_client_, this->get_logger(), action, "Process");
}

bool WeighingSystem::call_data_service(const std::string& action)
{
    return service_utils::call_service(
        data_client_, this->get_logger(), action, "Data");
}