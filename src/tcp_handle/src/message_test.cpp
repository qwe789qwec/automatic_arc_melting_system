#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/process_service.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<msg_format::srv::ProcessService>::SharedPtr client =
    node->create_client<msg_format::srv::ProcessService>("process_service");

  auto request = std::make_shared<msg_format::srv::ProcessService::Request>();

  // input "192.168.1.100 8080 Hello, World!"
  std::string getstring = argv[1];
  request->action = getstring;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "get string: %s", getstring.c_str());


  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", result.get()->result.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
  }

  rclcpp::shutdown();
  return 0;
}