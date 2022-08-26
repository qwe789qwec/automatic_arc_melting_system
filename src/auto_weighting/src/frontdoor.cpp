#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_format.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int service_process(std::shared_ptr<tcp_format::srv::SocketFormat_Request> request){
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketFormat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketFormat>("socket_format");

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", request->target_ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port_fd: %d", request->port_fd);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", request->action.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message string: %s", request->send_message.c_str());


  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  int socket_fd = 0;
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", result.get()->status.c_str());
    socket_fd = result.get()->socket_fd;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "socket_fd: %d", socket_fd);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", result.get()->receive_message.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
  }
  return socket_fd;
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  auto request = std::make_shared<tcp_format::srv::SocketFormat::Request>();

  int socket_fd = 0;
  request->target_ip = "192.168.0.2";
  request->port_fd = 8001;
  request->action = "creat";
  request->send_message = "init\r\n";
  socket_fd = service_process(request);

  request->port_fd = socket_fd;
  request->action = "send";
  request->send_message = "QRA 60 7 3\r\n";
  socket_fd = service_process(request);

  request->port_fd = socket_fd;
  request->action = "send";
  request->send_message = "QRA 60 7 2\r\n";
  socket_fd = service_process(request);

  request->port_fd = socket_fd;
  request->action = "close";
  socket_fd = service_process(request);

  rclcpp::shutdown();
  return 0;
}