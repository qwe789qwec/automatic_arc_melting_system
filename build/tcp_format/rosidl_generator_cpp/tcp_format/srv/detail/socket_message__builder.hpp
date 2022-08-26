// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tcp_format:srv/SocketMessage.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_MESSAGE__BUILDER_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_MESSAGE__BUILDER_HPP_

#include "tcp_format/srv/detail/socket_message__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketMessage_Request_send_message
{
public:
  explicit Init_SocketMessage_Request_send_message(::tcp_format::srv::SocketMessage_Request & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketMessage_Request send_message(::tcp_format::srv::SocketMessage_Request::_send_message_type arg)
  {
    msg_.send_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketMessage_Request msg_;
};

class Init_SocketMessage_Request_socket_fd
{
public:
  Init_SocketMessage_Request_socket_fd()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketMessage_Request_send_message socket_fd(::tcp_format::srv::SocketMessage_Request::_socket_fd_type arg)
  {
    msg_.socket_fd = std::move(arg);
    return Init_SocketMessage_Request_send_message(msg_);
  }

private:
  ::tcp_format::srv::SocketMessage_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketMessage_Request>()
{
  return tcp_format::srv::builder::Init_SocketMessage_Request_socket_fd();
}

}  // namespace tcp_format


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketMessage_Response_receive_message
{
public:
  explicit Init_SocketMessage_Response_receive_message(::tcp_format::srv::SocketMessage_Response & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketMessage_Response receive_message(::tcp_format::srv::SocketMessage_Response::_receive_message_type arg)
  {
    msg_.receive_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketMessage_Response msg_;
};

class Init_SocketMessage_Response_status
{
public:
  Init_SocketMessage_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketMessage_Response_receive_message status(::tcp_format::srv::SocketMessage_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_SocketMessage_Response_receive_message(msg_);
  }

private:
  ::tcp_format::srv::SocketMessage_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketMessage_Response>()
{
  return tcp_format::srv::builder::Init_SocketMessage_Response_status();
}

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_MESSAGE__BUILDER_HPP_
