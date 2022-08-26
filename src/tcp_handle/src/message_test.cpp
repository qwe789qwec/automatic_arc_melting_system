#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_format.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 5) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: test socket message");
      return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketFormat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketFormat>("socket_format");

  auto request = std::make_shared<tcp_format::srv::SocketFormat::Request>();

  // for(i=0; i < argc; i++) {
  //   RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "online example: arg %2d: %s\n", i, argv[i]);
  //   // printf("Command line arg %2d: %s\n", i, argv[i]);
  // }

  std::string argv_ip = argv[1];
  std::string argv_port = argv[2];
  std::string argv_action = argv[3];
  std::string argv_message = argv[4];
  // request->target_ip = atoll(argv_ip);
  argv_message = argv_message + "\r\n";
	// std::replace( argv_message.begin(), argv_message.end(), '^', ' '); // replace all '^' to ' '
  request->target_ip = argv_ip;
  request->target_port = argv_port;
  request->action = argv_action;
  request->send_message = argv_message;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", argv_ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port string: %s", argv_port.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", argv_action.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message string: %s", argv_message.c_str());


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
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", result.get()->status.c_str());
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", result.get()->receive_message.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
  }

  rclcpp::shutdown();
  return 0;
}