// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from msg_format:srv/GripperFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__BUILDER_HPP_
#define MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__BUILDER_HPP_

#include "msg_format/srv/detail/gripper_format__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace msg_format
{

namespace srv
{

namespace builder
{

class Init_GripperFormat_Request_action
{
public:
  Init_GripperFormat_Request_action()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msg_format::srv::GripperFormat_Request action(::msg_format::srv::GripperFormat_Request::_action_type arg)
  {
    msg_.action = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msg_format::srv::GripperFormat_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msg_format::srv::GripperFormat_Request>()
{
  return msg_format::srv::builder::Init_GripperFormat_Request_action();
}

}  // namespace msg_format


namespace msg_format
{

namespace srv
{

namespace builder
{

class Init_GripperFormat_Response_result
{
public:
  Init_GripperFormat_Response_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::msg_format::srv::GripperFormat_Response result(::msg_format::srv::GripperFormat_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::msg_format::srv::GripperFormat_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::msg_format::srv::GripperFormat_Response>()
{
  return msg_format::srv::builder::Init_GripperFormat_Response_result();
}

}  // namespace msg_format

#endif  // MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__BUILDER_HPP_
