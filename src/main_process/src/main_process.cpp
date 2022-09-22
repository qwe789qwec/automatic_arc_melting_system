#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/plc_format.hpp"
#include "msg_format/srv/weighing_format.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 2) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "main process");
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("main_process");
  rclcpp::Client<msg_format::srv::WeighingFormat>::SharedPtr main_process =
    node->create_client<msg_format::srv::WeighingFormat>("weighing_format");

  std::string action = argv[1];
  action = action + "\r\n";

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

  auto request = std::make_shared<msg_format::srv::WeighingFormat::Request>();
  request->action = action;

  while (!main_process->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
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
  }

  rclcpp::shutdown();
  return 0;
}