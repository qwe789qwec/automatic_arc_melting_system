#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "ros2_utils/service_utils.hpp"
#include "ros2_utils/instrument_node.hpp"


InstrumentControl::InstrumentControl(const std::string& ip, int port)
{
    // Connect to instrument
    instrument_socket_.connect(ip, port);

    // Start working thread
    worker_thread_ = std::thread(&InstrumentControl::worker_loop, this);
}
InstrumentControl::~InstrumentControl()
{    
    // Close socket connection
    instrument_socket_.close();
}

std::future<bool> InstrumentControl::make_action_async(std::string step)
{
    std::promise<bool> action_promise;
    std::future<bool> action_future = action_promise.get_future();

    {
        std::lock_guard<std::mutex> lock(queue_mutex_);
        task_queue_.emplace(step, std::move(action_promise));
    }
    cv_.notify_one();

    return action_future;
}

void InstrumentControl::worker_loop()
{
    while (true) {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        cv_.wait(lock, [this]() { return stop_worker_ || !task_queue_.empty(); });

        if (stop_worker_ && task_queue_.empty()) {
            return;
        }

        auto [step, prom] = std::move(task_queue_.front());
        task_queue_.pop();
        lock.unlock();

        bool result = false;
        try {
            result = this->make_action(step);  // Call the synchronous method
        } catch (const std::exception &e) {
            std::cerr << "[Instrument worker error] " << e.what() << std::endl;
        }

        prom.set_value(result);
    }
}

InstrumentNode::InstrumentNode
(   const std::string& Node_name,
    std::unique_ptr<InstrumentControl> instrument,
    const std::string& process_service_name,
    const std::string& subscription_name)
: Node(Node_name + "_node"),
  instrument_(std::move(instrument))
{
    // initialize parameters
    instrument_name_ = Node_name;
    current_command_ = Node_name + "_first";
    process_service_ = process_service_name;

    // create a client for the process service
    process_client_ = this->create_client<msg_format::srv::ProcessService>(process_service_name);

    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        subscription_name, 10, std::bind(&InstrumentNode::command_action, this, _1));

    RCLCPP_INFO(this->get_logger(), "initialized %s", Node_name.c_str());
}

bool InstrumentNode::test_instrument_action(const std::string& action_param)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", action_param.c_str());
    return instrument_->make_action(action_param);
}

void InstrumentNode::call_service(std::string status)
{
    service_utils::call_service_async(
            process_client_, this->get_logger(), instrument_name_ + status, process_service_);
}

void InstrumentNode::command_action(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    std::string command = service_utils::get_command(message, instrument_name_);
    
    // execute the command asynchronously
    if (instrument_future_valid_ && 
        instrument_future_.wait_for(0s) != std::future_status::ready) {
        // RCLCPP_INFO(this->get_logger(), "Command %s is still running", current_command_.c_str());
        return;
    }
    
    // previous task is done, check the result
    if (instrument_future_valid_)
    {
        try {
            bool result = instrument_future_.get();
            if (result) {
                RCLCPP_INFO(this->get_logger(), "Command %s completed successfully", current_command_.c_str());
                call_service("_standby");
            } else {
                RCLCPP_ERROR(this->get_logger(), "Command %s failed", current_command_.c_str());
                call_service("_error");
            }
        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in command %s: %s", current_command_.c_str(), e.what());
            call_service("_error");
        }
    }

    if(command.compare(current_command_) != 0) {
        current_command_ = command;
        RCLCPP_INFO(this->get_logger(), "Get command: %s", command.c_str());
        instrument_future_ = instrument_->make_action_async(command);
        instrument_future_valid_ = true;
        call_service("_action");
    }

    return;
}
