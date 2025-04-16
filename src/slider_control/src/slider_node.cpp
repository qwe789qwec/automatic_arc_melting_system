#include "slider_control/slider_node.hpp"
#include <string>
#include <future>
#include <thread>

using std::placeholders::_1;
using namespace std::chrono_literals;

SliderSystem::SliderSystem() : Node("slider_system")
{
    // initialize parameters
    slider_ip_ = "192.168.0.3";
    slider_port_ = 64511;
    current_step_ = "slider init";
    
    // initialize slider
    slider_ = std::make_unique<slider>(slider_ip_, slider_port_);
    
    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>("process_service");
    
    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        "topic", 10, std::bind(&SliderSystem::topic_callback, this, _1));
        
    RCLCPP_INFO(this->get_logger(), "SliderSystem initialized");
}
    
bool SliderSystem::test_slider_action(const std::string& action_param)
{
    slider test_slider("192.168.0.3", 64511);
    std::string test_action = "slider " + action_param;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", test_action.c_str());
    return test_slider.make_action(test_action);
}

void SliderSystem::topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg)
{
    std::string message = msg->process;
    
    if (message != current_step_){
        RCLCPP_INFO(this->get_logger(), "Message: %s", message.c_str());
    }
    
    if (message.compare(current_step_) != 0) {
        current_step_ = message;
        
        bool action_result = slider_->make_action(message);
        if (action_result) {
            auto future = call_process_service("slider standby");
            
            std::thread([this, future]() {
                auto status = future.wait_for(std::chrono::seconds(5));
                if (status != std::future_status::ready) {
                    RCLCPP_WARN(this->get_logger(), "Service call timeout after waiting in background");
                }
                else if (!future.get()) {
                    RCLCPP_WARN(this->get_logger(), "Service call failed (reported in background)");
                }
            }).detach();
        } else {
            RCLCPP_ERROR(this->get_logger(), "Error cannot make action");
        }
    }
}

std::shared_future<bool> SliderSystem::call_process_service(const std::string& action)
{
    auto promise = std::make_shared<std::promise<bool>>();
    auto future = promise->get_future().share();
    
    // set timeout
    if (!process_client_->service_is_ready()) {
        const std::chrono::milliseconds short_timeout(100);
        if (!process_client_->wait_for_service(short_timeout)) {
            RCLCPP_ERROR(this->get_logger(), "Process service not available");
            promise->set_value(false);
            return future;
        }
    }
    
    // create a request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // create a callback for the response
    auto response_callback = [this, promise, action](
        rclcpp::Client<msg_format::srv::ProcessService>::SharedFuture future) {
        try {
            auto result = future.get();
            RCLCPP_INFO(this->get_logger(), "Service result for '%s': %s", 
                       action.c_str(), result->result.c_str());
            promise->set_value(true);
        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in service call '%s': %s", 
                        action.c_str(), e.what());
            promise->set_value(false);
        }
    };
    
    // send the request asynchronously
    process_client_->async_send_request(request, response_callback);
    
    RCLCPP_DEBUG(this->get_logger(), "Service request '%s' sent asynchronously", action.c_str());
    return future;
}