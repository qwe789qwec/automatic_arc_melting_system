// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tcp_format:srv/SocketCreat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__BUILDER_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__BUILDER_HPP_

#include "tcp_format/srv/detail/socket_creat__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketCreat_Request_target_port
{
public:
  explicit Init_SocketCreat_Request_target_port(::tcp_format::srv::SocketCreat_Request & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketCreat_Request target_port(::tcp_format::srv::SocketCreat_Request::_target_port_type arg)
  {
    msg_.target_port = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketCreat_Request msg_;
};

class Init_SocketCreat_Request_target_ip
{
public:
  Init_SocketCreat_Request_target_ip()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketCreat_Request_target_port target_ip(::tcp_format::srv::SocketCreat_Request::_target_ip_type arg)
  {
    msg_.target_ip = std::move(arg);
    return Init_SocketCreat_Request_target_port(msg_);
  }

private:
  ::tcp_format::srv::SocketCreat_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketCreat_Request>()
{
  return tcp_format::srv::builder::Init_SocketCreat_Request_target_ip();
}

}  // namespace tcp_format


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketCreat_Response_socket_fd
{
public:
  explicit Init_SocketCreat_Response_socket_fd(::tcp_format::srv::SocketCreat_Response & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::SocketCreat_Response socket_fd(::tcp_format::srv::SocketCreat_Response::_socket_fd_type arg)
  {
    msg_.socket_fd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketCreat_Response msg_;
};

class Init_SocketCreat_Response_status
{
public:
  Init_SocketCreat_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SocketCreat_Response_socket_fd status(::tcp_format::srv::SocketCreat_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_SocketCreat_Response_socket_fd(msg_);
  }

private:
  ::tcp_format::srv::SocketCreat_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketCreat_Response>()
{
  return tcp_format::srv::builder::Init_SocketCreat_Response_status();
}

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_CREAT__BUILDER_HPP_
