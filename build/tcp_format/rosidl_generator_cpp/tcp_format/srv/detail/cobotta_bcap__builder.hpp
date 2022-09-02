// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tcp_format:srv/CobottaBcap.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__BUILDER_HPP_
#define TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__BUILDER_HPP_

#include "tcp_format/srv/detail/cobotta_bcap__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_CobottaBcap_Request_target
{
public:
  explicit Init_CobottaBcap_Request_target(::tcp_format::srv::CobottaBcap_Request & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::CobottaBcap_Request target(::tcp_format::srv::CobottaBcap_Request::_target_type arg)
  {
    msg_.target = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::CobottaBcap_Request msg_;
};

class Init_CobottaBcap_Request_action
{
public:
  Init_CobottaBcap_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CobottaBcap_Request_target action(::tcp_format::srv::CobottaBcap_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return Init_CobottaBcap_Request_target(msg_);
  }

private:
  ::tcp_format::srv::CobottaBcap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::CobottaBcap_Request>()
{
  return tcp_format::srv::builder::Init_CobottaBcap_Request_action();
}

}  // namespace tcp_format


namespace tcp_format
{

namespace srv
{

namespace builder
{

class Init_CobottaBcap_Response_message
{
public:
  explicit Init_CobottaBcap_Response_message(::tcp_format::srv::CobottaBcap_Response & msg)
  : msg_(msg)
  {}
  ::tcp_format::srv::CobottaBcap_Response message(::tcp_format::srv::CobottaBcap_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tcp_format::srv::CobottaBcap_Response msg_;
};

class Init_CobottaBcap_Response_status
{
public:
  Init_CobottaBcap_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CobottaBcap_Response_message status(::tcp_format::srv::CobottaBcap_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_CobottaBcap_Response_message(msg_);
  }

private:
  ::tcp_format::srv::CobottaBcap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tcp_format::srv::CobottaBcap_Response>()
{
  return tcp_format::srv::builder::Init_CobottaBcap_Response_status();
}

}  // namespace tcp_format

#endif  // TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__BUILDER_HPP_
