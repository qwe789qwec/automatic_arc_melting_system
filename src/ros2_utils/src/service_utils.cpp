#include "ros2_utils/service_utils.hpp"

namespace service_utils {

bool call_service(
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
    rclcpp::Logger logger,
    const std::string& action,
    const std::string& service_name,
    const std::chrono::seconds& timeout)
{
    // wait for service to be available
    if (!client->wait_for_service(timeout))
    {
        RCLCPP_ERROR(logger, "%s service not available after timeout", 
                    service_name.c_str());
        return false;
    }
    
    // create request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // send request
    auto future = client->async_send_request(request);
    
    // wait for response
    std::future_status status = future.wait_for(timeout);
    
    if (status == std::future_status::ready) {
        try {
            auto result = future.get();
            RCLCPP_INFO(logger, "%s result: %s", 
                      service_name.c_str(), result->result.c_str());
            return true;
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(logger, "Exception getting %s result: %s", 
                        service_name.c_str(), e.what());
            return false;
        }
    }
    else {
        RCLCPP_ERROR(logger, "%s call timed out", service_name.c_str());
        return false;
    }
}

std::shared_future<bool> call_service_async(
    rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client,
    rclcpp::Logger logger,
    const std::string& action,
    const std::string& service_name)
{
    // create a shared promise and future
    auto promise = std::make_shared<std::promise<bool>>();
    auto future = promise->get_future().share();
    
    // check if the service is available
    if (!client->service_is_ready()) {
        const std::chrono::milliseconds short_timeout(100);
        if (!client->wait_for_service(short_timeout)) {
            RCLCPP_ERROR(logger, "%s service not available", service_name.c_str());
            promise->set_value(false);
            return future;
        }
    }
    
    // create request
    auto request = std::make_shared<msg_format::srv::ProcessService::Request>();
    request->action = action;
    
    // create a callback for the response
    auto response_callback = [promise, action, service_name, logger](
        rclcpp::Client<msg_format::srv::ProcessService>::SharedFuture future) {
        try {
            auto result = future.get();
            RCLCPP_INFO(logger, "%s result for '%s': %s", 
                       service_name.c_str(), action.c_str(), result->result.c_str());
            promise->set_value(true);
        } catch (const std::exception& e) {
            RCLCPP_ERROR(logger, "Exception in %s call '%s': %s", 
                        service_name.c_str(), action.c_str(), e.what());
            promise->set_value(false);
        }
    };
    
    // send request asynchronously
    client->async_send_request(request, response_callback);
    
    RCLCPP_DEBUG(logger, "%s request '%s' sent asynchronously", 
                service_name.c_str(), action.c_str());
    return future;
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

std::vector<std::string> split_string(const std::string& input, char delimiter = '_') {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

} // namespace service_utils