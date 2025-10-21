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

        auto task = std::move(task_queue_.front());
        auto step = std::move(task.first);
        auto prom = std::move(task.second);
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
  instrument_control_(std::move(instrument))
{
    // initialize parameters
    instrument_name_ = Node_name;
    current_command_ = Node_name + "_first";

    // create a client
    process_client_ = this->create_client<msg_format::srv::ProcessService>(process_service_name);
    data_client_ = this->create_client<msg_format::srv::ProcessService>("write_data");

    // create a subscription for the process message
    subscription_ = this->create_subscription<msg_format::msg::ProcessMsg>(
        subscription_name, 10, std::bind(&InstrumentNode::command_action, this, _1));

    RCLCPP_INFO(this->get_logger(), "initialized %s", Node_name.c_str());
}

bool InstrumentNode::test_instrument_action(const std::string& action_param)
{
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Test action: %s", action_param.c_str());
    return instrument_control_->make_action(action_param);
}

void InstrumentNode::command_action(const msg_format::msg::ProcessMsg::SharedPtr msg)
{    
    const std::string& message = msg->process;
    std::string command = service_utils::get_command(message, instrument_name_);
    std::string status = "_action";

    if(command.compare(current_command_) != 0) {
        current_command_ = command;
        RCLCPP_INFO(this->get_logger(), "Get command: %s", command.c_str());
        if (instrument_future_valid_ == false) {
            instrument_future_ = instrument_control_->make_action_async(current_command_);
            instrument_future_valid_ = true;
            status = "_action";
        }
        else {
            // instrument_future_ = instrument_control_->make_action_async(current_command_);
            status = "_error";
        }
        service_utils::call_service(process_client_, this->get_logger(), instrument_name_ + status);
        return;
    }
    
    if (instrument_future_valid_ && 
    instrument_future_.wait_for(0s) == std::future_status::ready) {
        try {
            bool result = instrument_future_.get();
            if (result) {
                RCLCPP_INFO(this->get_logger(), "Command %s completed successfully", current_command_.c_str());
                status = "_standby";
                if (instrument_control_->data_flag) {
                    std::string datalog = instrument_control_->write_datalog();
                    service_utils::call_service(
                        data_client_, this->get_logger(), datalog);
                }
            } else {
                RCLCPP_ERROR(this->get_logger(), "Command %s failed", current_command_.c_str());
                status = "_error";
            }
        } catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Exception in command %s: %s", current_command_.c_str(), e.what());
            status = "_error";
        }
        instrument_future_valid_ = false;
        service_utils::call_service(process_client_, this->get_logger(), instrument_name_ + status);
    }

    return;
}
