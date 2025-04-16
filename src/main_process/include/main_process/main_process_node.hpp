#ifndef MAIN_PROCESS_NODE_HPP
#define MAIN_PROCESS_NODE_HPP

#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/msg/process_msg.hpp"

/**
 * @brief Publisher node that publishes the current process step
 */
class MainProcessNode : public rclcpp::Node {
public:
    MainProcessNode(const std::string& name, const std::string& topic);

private:
    rclcpp::Publisher<msg_format::msg::ProcessMsg>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::string last_message_;
    void timerCallback();
};

#endif // MAIN_PROCESS_NODE_HPP