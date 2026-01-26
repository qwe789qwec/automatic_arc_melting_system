#ifndef SLIDERXRD_NODE_H
#define SLIDERXRD_NODE_H

#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "slider_control/sliderxrd.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class SliderxrdSystem : public rclcpp::Node
{
public:
    SliderxrdSystem();
    ~SliderxrdSystem() = default;

    // test slider action
    static bool test_slider_action(const std::string& action_param);

private:
    // parameters
    std::string sliderxrd_ip_;
    int sliderxrd_port_;
    std::string current_step_;
    
    // slider control
    std::unique_ptr<sliderxrd> sliderxrd_;
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr process_client_;
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;

    // callback functions
    void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
};

#endif // SLIDERXRD_NODE_Hs