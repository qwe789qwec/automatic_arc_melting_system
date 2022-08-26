#include "rclcpp/rclcpp.hpp"
#include "tcp_format/srv/socket_creat.hpp"
#include "tcp_format/srv/socket_message.hpp"
#include "tcp_format/srv/socket_close.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int creat_socket(std::string ip, std::string port){
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start creat socket");

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketCreat>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketCreat>("socket_creat");

  auto request = std::make_shared<tcp_format::srv::SocketCreat::Request>();

	// std::replace( argv_message.begin(), argv_message.end(), '^', ' '); // replace all '^' to ' '
  request->target_ip = ip;
  request->target_port = port;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "ip string: %s", ip.c_str());
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "port string: %s", port.c_str());


  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.

  auto service_status = rclcpp::spin_until_future_complete(node, result);
  std::string sock_status = "init sock";
  int sock_fd = -1;
  if (service_status == rclcpp::FutureReturnCode::SUCCESS)
  { sock_status = result.get()->status.c_str();
    sock_fd = result.get()->socket_fd;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", sock_status.c_str());
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sock_fd: %d", sock_fd);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to creat socket");
    return -1;
  }
  return sock_fd;
}

int send_socket(int sock_fd, std::string message){
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start send socket");
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketMessage>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketMessage>("socket_message");

  auto request = std::make_shared<tcp_format::srv::SocketMessage::Request>();

	// std::replace( argv_message.begin(), argv_message.end(), '^', ' '); // replace all '^' to ' '
  request->socket_fd = sock_fd;
  request->send_message = message;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "socket_fd: %d", sock_fd);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "send message: %s", message.c_str());

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.

  auto service_status = rclcpp::spin_until_future_complete(node, result);
  std::string sock_status = "init sock";
  std::string recive_message = "init msg";
  if (service_status == rclcpp::FutureReturnCode::SUCCESS)
  { sock_status = result.get()->status.c_str();
    recive_message = result.get()->receive_message;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", sock_status.c_str());
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "message: %s", recive_message.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
    return -1;
  }
  return sock_fd;
}

int close_socket(int sock_fd){
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "start close socket");
  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("tcp_communicate");
  rclcpp::Client<tcp_format::srv::SocketClose>::SharedPtr client =
    node->create_client<tcp_format::srv::SocketClose>("socket_close");

  auto request = std::make_shared<tcp_format::srv::SocketClose::Request>();

	// std::replace( argv_message.begin(), argv_message.end(), '^', ' '); // replace all '^' to ' '
  request->socket_fd = sock_fd;

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "socket_fd: %d", sock_fd);


  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.

  auto service_status = rclcpp::spin_until_future_complete(node, result);
  std::string sock_status = "init sock";
  std::string recive_message = "init msg";
  if (service_status == rclcpp::FutureReturnCode::SUCCESS)
  { sock_status = result.get()->status.c_str();
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "status: %s", sock_status.c_str());
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to send socket");
    return -1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  if (argc != 4) {
      RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: test socket message");
      return 1;
  }

  std::string argv_ip = argv[1];
  std::string argv_port = argv[2];
  std::string argv_message = argv[3];
  argv_message = argv_message + "\r\n";

  int sock_fd = creat_socket(argv_ip, argv_port);
  if(sock_fd < 0){
    rclcpp::shutdown();
    return 0;
  }
  else{
    sock_fd = send_socket(sock_fd, argv_message);
  }

  if(sock_fd < 0){
    rclcpp::shutdown();
    return 0;
  }
  else{
    close_socket(sock_fd);
  }

  rclcpp::shutdown();
  return 0;
}