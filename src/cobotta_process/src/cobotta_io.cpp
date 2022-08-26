#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_format.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int creat_socket(){
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketFormat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketFormat>("socket_format");

  auto request = std::make_shared<tcp_format::srv::SocketFormat::Request>();

  std::string message = "123";
  message = message + "\r\n";
  request->target_ip = "172.17.4.71";
  request->port_fd = 40543;
  request->action = "creat";
  request->send_message = message;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", request->target_ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port string: %d", request->port_fd);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", request->action.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message string: %s", message.c_str());


  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  int socket_fd;
  auto result = client->async_send_request(request);
  // Wait for the result.
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

int send_socket(int socket_fd){
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketFormat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketFormat>("socket_format");

  auto request = std::make_shared<tcp_format::srv::SocketFormat::Request>();

  std::string message = "123";
  message = message + "\r\n";
  request->target_ip = "172.17.4.71";
  request->port_fd = socket_fd;
  request->action = "send";
  request->send_message = message;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", request->target_ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port string: %d", request->port_fd);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", request->action.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message string: %s", message.c_str());


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
    socket_fd = result.get()->socket_fd;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "socket_fd: %d", socket_fd);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", result.get()->receive_message.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
  }
  return socket_fd;
}

int close_socket(int socket_fd){
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketFormat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketFormat>("socket_format");

  auto request = std::make_shared<tcp_format::srv::SocketFormat::Request>();

  std::string message = "123";
  message = message + "\r\n";
  request->target_ip = "172.17.4.71";
  request->port_fd = socket_fd;
  request->action = "close";
  request->send_message = message;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", request->target_ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port string: %d", request->port_fd);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", request->action.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message string: %s", message.c_str());


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

  // if (argc != 5) {
  //     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: test socket message");
  //     return 1;
  // }
  int socket_fd = creat_socket();
  if(socket_fd < 0){
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to creat socket");
  }
  else{
    if(send_socket(socket_fd) < 0){
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
    }
    else{
      if(close_socket(socket_fd) < 0){
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to close socket");
      }
    }
  }

  rclcpp::shutdown();
  return 0;
}