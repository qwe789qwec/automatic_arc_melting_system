// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__TRAITS_HPP_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__TRAITS_HPP_

#include "tcp_format/srv/detail/socket_format__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<tcp_format::srv::SocketFormat_Request>()
{
  return "tcp_format::srv::SocketFormat_Request";
}

template<>
inline const char * name<tcp_format::srv::SocketFormat_Request>()
{
  return "tcp_format/srv/SocketFormat_Request";
}

template<>
struct has_fixed_size<tcp_format::srv::SocketFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<tcp_format::srv::SocketFormat_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<tcp_format::srv::SocketFormat_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<tcp_format::srv::SocketFormat_Response>()
{
  return "tcp_format::srv::SocketFormat_Response";
}

template<>
inline const char * name<tcp_format::srv::SocketFormat_Response>()
{
  return "tcp_format/srv/SocketFormat_Response";
}

template<>
struct has_fixed_size<tcp_format::srv::SocketFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<tcp_format::srv::SocketFormat_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<tcp_format::srv::SocketFormat_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<tcp_format::srv::SocketFormat>()
{
  return "tcp_format::srv::SocketFormat";
}

template<>
inline const char * name<tcp_format::srv::SocketFormat>()
{
  return "tcp_format/srv/SocketFormat";
}

template<>
struct has_fixed_size<tcp_format::srv::SocketFormat>
  : std::integral_constant<
    bool,
    has_fixed_size<tcp_format::srv::SocketFormat_Request>::value &&
    has_fixed_size<tcp_format::srv::SocketFormat_Response>::value
  >
{
};

template<>
struct has_bounded_size<tcp_format::srv::SocketFormat>
  : std::integral_constant<
    bool,
    has_bounded_size<tcp_format::srv::SocketFormat_Request>::value &&
    has_bounded_size<tcp_format::srv::SocketFormat_Response>::value
  >
{
};

template<>
struct is_service<tcp_format::srv::SocketFormat>
  : std::true_type
{
};

template<>
struct is_service_request<tcp_format::srv::SocketFormat_Request>
  : std::true_type
{
};

template<>
struct is_service_response<tcp_format::srv::SocketFormat_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__TRAITS_HPP_
