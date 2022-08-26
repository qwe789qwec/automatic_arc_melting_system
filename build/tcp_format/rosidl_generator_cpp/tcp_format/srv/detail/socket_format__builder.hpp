// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__BUILDER_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__BUILDER_HPP_

#include "tcp_format/srv/detail/socket_format__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketFormat_Request_send_message
{
public:
  explicit Init_SocketFormat_Request_send_message(::tcp_format::srv::SocketFormat_Request & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketFormat_Request send_message(::tcp_format::srv::SocketFormat_Request::_send_message_type arg)
  {
    msg_.send_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Request msg_;
};

class Init_SocketFormat_Request_action
{
public:
  explicit Init_SocketFormat_Request_action(::tcp_format::srv::SocketFormat_Request & msg)
  : msg_(msg)
  {}
  Init_SocketFormat_Request_send_message action(::tcp_format::srv::SocketFormat_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_SocketFormat_Request_send_message(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Request msg_;
};

class Init_SocketFormat_Request_port_fd
{
public:
  explicit Init_SocketFormat_Request_port_fd(::tcp_format::srv::SocketFormat_Request & msg)
  : msg_(msg)
  {}
  Init_SocketFormat_Request_action port_fd(::tcp_format::srv::SocketFormat_Request::_port_fd_type arg)
  {
    msg_.port_fd = std::move(arg);
    return Init_SocketFormat_Request_action(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Request msg_;
};

class Init_SocketFormat_Request_target_ip
{
public:
  Init_SocketFormat_Request_target_ip()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketFormat_Request_port_fd target_ip(::tcp_format::srv::SocketFormat_Request::_target_ip_type arg)
  {
    msg_.target_ip = std::move(arg);
    return Init_SocketFormat_Request_port_fd(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketFormat_Request>()
{
  return tcp_format::srv::builder::Init_SocketFormat_Request_target_ip();
}

}  // namespace tcp_format


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketFormat_Response_receive_message
{
public:
  explicit Init_SocketFormat_Response_receive_message(::tcp_format::srv::SocketFormat_Response & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketFormat_Response receive_message(::tcp_format::srv::SocketFormat_Response::_receive_message_type arg)
  {
    msg_.receive_message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Response msg_;
};

class Init_SocketFormat_Response_status
{
public:
  explicit Init_SocketFormat_Response_status(::tcp_format::srv::SocketFormat_Response & msg)
  : msg_(msg)
  {}
  Init_SocketFormat_Response_receive_message status(::tcp_format::srv::SocketFormat_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_SocketFormat_Response_receive_message(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Response msg_;
};

class Init_SocketFormat_Response_socket_fd
{
public:
  Init_SocketFormat_Response_socket_fd()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketFormat_Response_status socket_fd(::tcp_format::srv::SocketFormat_Response::_socket_fd_type arg)
  {
    msg_.socket_fd = std::move(arg);
    return Init_SocketFormat_Response_status(msg_);
  }

private:
  ::tcp_format::srv::SocketFormat_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketFormat_Response>()
{
  return tcp_format::srv::builder::Init_SocketFormat_Response_socket_fd();
}

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__BUILDER_HPP_
