// 在 common/include/common/service_utils.hpp
#ifndef SERVICE_UTILS_HPP
#define SERVICE_UTILS_HPP

#include <string>
#include <memory>
#include <future>
#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/process_service.hpp"

namespace service_utils {

// 阻塞式服务调用
bool call_service(
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
        rclcpp::Logger logger,
        const std::string& action,
        const std::string& service_name,
        const std::chrono::seconds& timeout = std::chrono::seconds(3));

    // 非阻塞式服务调用（返回future）
    std::shared_future<bool> call_service_async(
        rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
        rclcpp::Logger logger,
        const std::string& action,
        const std::string& service_name);

} // namespace service_utils

#endif // SERVICE_UTILS_HPP