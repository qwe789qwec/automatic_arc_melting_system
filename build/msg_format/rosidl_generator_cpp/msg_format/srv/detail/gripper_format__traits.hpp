// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from msg_format:srv/GripperFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__TRAITS_HPP_
#define MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__TRAITS_HPP_

#include "msg_format/srv/detail/gripper_format__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::GripperFormat_Request>()
{
  return "msg_format::srv::GripperFormat_Request";
}

template<>
inline const char * name<msg_format::srv::GripperFormat_Request>()
{
  return "msg_format/srv/GripperFormat_Request";
}

template<>
struct has_fixed_size<msg_format::srv::GripperFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<msg_format::srv::GripperFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<msg_format::srv::GripperFormat_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::GripperFormat_Response>()
{
  return "msg_format::srv::GripperFormat_Response";
}

template<>
inline const char * name<msg_format::srv::GripperFormat_Response>()
{
  return "msg_format/srv/GripperFormat_Response";
}

template<>
struct has_fixed_size<msg_format::srv::GripperFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<msg_format::srv::GripperFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<msg_format::srv::GripperFormat_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::GripperFormat>()
{
  return "msg_format::srv::GripperFormat";
}

template<>
inline const char * name<msg_format::srv::GripperFormat>()
{
  return "msg_format/srv/GripperFormat";
}

template<>
struct has_fixed_size<msg_format::srv::GripperFormat>
  : std::integral_constant<
    bool,
    has_fixed_size<msg_format::srv::GripperFormat_Request>::value &&
    has_fixed_size<msg_format::srv::GripperFormat_Response>::value
  >
{
};

template<>
struct has_bounded_size<msg_format::srv::GripperFormat>
  : std::integral_constant<
    bool,
    has_bounded_size<msg_format::srv::GripperFormat_Request>::value &&
    has_bounded_size<msg_format::srv::GripperFormat_Response>::value
  >
{
};

template<>
struct is_service<msg_format::srv::GripperFormat>
  : std::true_type
{
};

template<>
struct is_service_request<msg_format::srv::GripperFormat_Request>
  : std::true_type
{
};

template<>
struct is_service_response<msg_format::srv::GripperFormat_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__TRAITS_HPP_
