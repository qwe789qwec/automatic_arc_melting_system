#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>

#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/plc_format.hpp"
#include "msg_format/srv/weighing_format.hpp"

using namespace std::chrono_literals;

int weighing_client(rclcpp::Node::SharedPtr node, std::string action){
    rclcpp::Client<msg_format::srv::WeighingFormat>::SharedPtr main_process =
        node->create_client<msg_format::srv::WeighingFormat>("weighing_format");
    
    auto request = std::make_shared<msg_format::srv::WeighingFormat::Request>();
    request->action = action;

    while (!main_process->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return -1;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = main_process->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "result: %s", result.get()->result.c_str());
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
        return -1;
    }
    return 0;
}

int plc_client(rclcpp::Node::SharedPtr node, std::string action){
    rclcpp::Client<msg_format::srv::PlcFormat>::SharedPtr main_process =
        node->create_client<msg_format::srv::PlcFormat>("plc_format");
    
    auto request = std::make_shared<msg_format::srv::PlcFormat::Request>();
    request->action = action;

    while (!main_process->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
        return -1;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
    }

    auto result = main_process->async_send_request(request);
    // Wait for the result.
    if (rclcpp::spin_until_future_complete(node, result) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "result: %s", result.get()->result.c_str());
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("main_process");

    if (argc != 2) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "main process");
        return 1;
    }

    std::string action = argv[1];
    action = action + "\r\n";
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

    if(action.rfind("plc", 0) == 0){
        action = action.substr(4);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
        plc_client(node, action);
    }
    else if(action.rfind("weighing", 0) == 0){
        action = action.substr(9);
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());
        weighing_client(node, action);
    }

    rclcpp::shutdown();
    return 0;
}