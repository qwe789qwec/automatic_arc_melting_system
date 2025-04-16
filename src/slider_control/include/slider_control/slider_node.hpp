#ifndef SLIDER_NODE_H
#define SLIDER_NODE_H

#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "slider_control/slider.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class SliderSystem : public rclcpp::Node
{
public:
    SliderSystem();
    ~SliderSystem() = default;

    // test slider action
    static bool test_slider_action(const std::string& action_param);

private:
    // parameters
    std::string slider_ip_;
    int slider_port_;
    std::string current_step_;
    
    // slider control
    std::unique_ptr<slider> slider_;
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

    // callback functions
    void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
    std::shared_future<bool> call_process_service(const std::string& action);
};

#endif // SLIDER_NODE_Hs