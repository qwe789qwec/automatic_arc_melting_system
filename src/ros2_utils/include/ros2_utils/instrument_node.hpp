#ifndef INSTRUMENT_SYSTEM_H
#define INSTRUMENT_SYSTEM_H

#include <chrono>
#include <memory>
#include <string>
#include <mutex>
#include <atomic>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "tcp_handle/tcp_socket.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class InstrumentControl
{
    public:
        InstrumentControl(const std::string& ip, int port);
        virtual ~InstrumentControl();
        virtual bool make_action(std::string step) = 0;
        virtual std::future<bool> make_action_async(std::string step);
        
    protected:

        // Thread control
        // Task queue for asynchronous actions
        std::queue<std::pair<std::string, std::promise<bool>>> task_queue_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;
        std::atomic<bool> stop_worker_{false};
        std::thread worker_thread_;
        virtual void worker_loop(); // Worker thread function
    
        tcp_socket instrument_socket_;
};

class InstrumentNode : public rclcpp::Node
{
    public:
        InstrumentNode(
            const std::string& Node_name,
            std::unique_ptr<InstrumentControl> instrument,
            const std::string& process_service_name, 
            const std::string& subscription_name);
        ~InstrumentNode() = default;

        // test instrument action
        bool test_instrument_action(const std::string& action_param);

    protected:
        // parameters
        std::string instrument_name_;
        std::string current_command_;
        std::string process_service_;
        
        // instrument control
        std::unique_ptr<InstrumentControl> instrument_;
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
        rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

        // async instrument control state
        std::future<bool> instrument_future_;
        bool instrument_future_valid_ = false;

        // callback functions
        void call_service(std::string status);
        void command_action(const msg_format::msg::ProcessMsg::SharedPtr msg);
};

#endif // INSTRUMENT_SYSTEM_H