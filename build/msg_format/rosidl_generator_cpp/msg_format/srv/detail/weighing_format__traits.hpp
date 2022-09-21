// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from msg_format:srv/WeighingFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__TRAITS_HPP_
#define MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__TRAITS_HPP_

#include "msg_format/srv/detail/weighing_format__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::WeighingFormat_Request>()
{
  return "msg_format::srv::WeighingFormat_Request";
}

template<>
inline const char * name<msg_format::srv::WeighingFormat_Request>()
{
  return "msg_format/srv/WeighingFormat_Request";
}

template<>
struct has_fixed_size<msg_format::srv::WeighingFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<msg_format::srv::WeighingFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<msg_format::srv::WeighingFormat_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::WeighingFormat_Response>()
{
  return "msg_format::srv::WeighingFormat_Response";
}

template<>
inline const char * name<msg_format::srv::WeighingFormat_Response>()
{
  return "msg_format/srv/WeighingFormat_Response";
}

template<>
struct has_fixed_size<msg_format::srv::WeighingFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<msg_format::srv::WeighingFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<msg_format::srv::WeighingFormat_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<msg_format::srv::WeighingFormat>()
{
  return "msg_format::srv::WeighingFormat";
}

template<>
inline const char * name<msg_format::srv::WeighingFormat>()
{
  return "msg_format/srv/WeighingFormat";
}

template<>
struct has_fixed_size<msg_format::srv::WeighingFormat>
  : std::integral_constant<
    bool,
    has_fixed_size<msg_format::srv::WeighingFormat_Request>::value &&
    has_fixed_size<msg_format::srv::WeighingFormat_Response>::value
  >
{
};

template<>
struct has_bounded_size<msg_format::srv::WeighingFormat>
  : std::integral_constant<
    bool,
    has_bounded_size<msg_format::srv::WeighingFormat_Request>::value &&
    has_bounded_size<msg_format::srv::WeighingFormat_Response>::value
  >
{
};

template<>
struct is_service<msg_format::srv::WeighingFormat>
  : std::true_type
{
};

template<>
struct is_service_request<msg_format::srv::WeighingFormat_Request>
  : std::true_type
{
};

template<>
struct is_service_response<msg_format::srv::WeighingFormat_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__TRAITS_HPP_
