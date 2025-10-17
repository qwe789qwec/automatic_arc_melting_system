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
        const std::chrono::seconds& timeout = std::chrono::seconds(6));
    
std::string get_command(
    std::string command,
    const std::string device_id);

std::vector<std::string> split_string(
    const std::string& input,
    char delimiter = '_');

} // namespace service_utils


#endif // SERVICE_UTILS_HPP