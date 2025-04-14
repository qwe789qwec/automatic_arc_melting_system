#ifndef SLIDER_NODE_HPP
#define SLIDER_NODE_HPP

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"
#include "msg_format/srv/process_service.hpp"
#include "slider_control/slider.hpp"

class SliderNode : public rclcpp::Node
{
public:
    SliderNode(slider& slider_controller);

private:
    // Subscriber
    void topic_callback(const msg_format::msg::ProcessMsg::SharedPtr msg);
    
    // Client
    bool send_slider_client_request(const std::string& action);
    
    rclcpp::Subscription<msg_format::msg::ProcessMsg>::SharedPtr subscription_;
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client_;
    slider& slider_;
};

#endif // SLIDER_NODE_HPP