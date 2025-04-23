// 在 common/include/common/service_utils.hpp
#ifndef SERVICE_UTILS_HPP
#define SERVICE_UTILS_HPP

#include <string>
#include <memory>
#include <future>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/process_service.hpp"

namespace service_utils {

// non-blocking service call
bool call_service(
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
        rclcpp::Logger logger,
        const std::string& action,
        const std::string& service_name,
        const std::chrono::seconds& timeout = std::chrono::seconds(3));

std::shared_future<bool> call_service_async(
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
    rclcpp::Logger logger,
    const std::string& action,
    const std::string& service_name);

} // namespace service_utils

std::string get_commend(
    const std::string& command,
    const std::string& device_id);

#endif // SERVICE_UTILS_HPP