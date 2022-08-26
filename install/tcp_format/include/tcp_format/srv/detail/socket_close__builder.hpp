// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tcp_format:srv/SocketClose.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__BUILDER_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__BUILDER_HPP_

#include "tcp_format/srv/detail/socket_close__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketClose_Request_socket_fd
{
public:
  Init_SocketClose_Request_socket_fd()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::tcp_format::srv::SocketClose_Request socket_fd(::tcp_format::srv::SocketClose_Request::_socket_fd_type arg)
  {
    msg_.socket_fd = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketClose_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketClose_Request>()
{
  return tcp_format::srv::builder::Init_SocketClose_Request_socket_fd();
}

}  // namespace tcp_format


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_SocketClose_Response_status
{
public:
  Init_SocketClose_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::tcp_format::srv::SocketClose_Response status(::tcp_format::srv::SocketClose_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::SocketClose_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::SocketClose_Response>()
{
  return tcp_format::srv::builder::Init_SocketClose_Response_status();
}

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__BUILDER_HPP_
