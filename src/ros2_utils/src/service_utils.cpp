#include "ros2_utils/service_utils.hpp"

namespace service_utils {

bool call_service(
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
    rclcpp::Logger logger,
    const std::string& action,
    const std::chrono::seconds& timeout)
{
    const std::string service_name = client->get_service_name();
    if (service_name.empty()) {
        RCLCPP_ERROR(logger, "Client has no service name");
        return false;
    }

    if (!client->wait_for_service(timeout)) {
        RCLCPP_ERROR(logger, "%s service not available after %ld seconds", 
                     service_name.c_str(), timeout.count());
        return false;
    }

    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;

    auto future = client->async_send_request(request);

    auto ret = rclcpp::spin_until_future_complete(
        rclcpp::Node::make_shared("temp_node"), future, timeout);

    if (ret == rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_INFO(logger, "status: %s", future.get()->result.c_str());
        return true;
    } else {
        RCLCPP_ERROR(logger, "Failed to call service %s", service_name.c_str());
        return false;
    }
}

std::string get_command(
    std::string command,
    const std::string device_id) {
    
    if (command == "test" || command == "init"){
        return command;
    }

    std::string::size_type pos = command.find(device_id);
    if (pos == std::string::npos) {
        return "none";
    }

    // get the position of the underscore
    std::string::size_type underscorePos = pos + device_id.length();
    if (underscorePos >= command.length() || command[underscorePos] != '_') {
        return "error";
    }
    // get the command
    std::string::size_type spacePos = command.find(' ', underscorePos + 1);
    std::string device_command = command.substr(pos, spacePos - pos);

    // check if the action is empty
    if (device_command.empty()) {
        return "error";
    }
    
    return device_command;
}

std::vector<std::string> split_string(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

} // namespace service_utils