// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice
#include "tcp_format/srv/detail/socket_format__rosidl_typesupport_fastrtps_cpp.hpp"
#include "tcp_format/srv/detail/socket_format__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace tcp_format
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
cdr_serialize(
  const tcp_format::srv::SocketFormat_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: target_ip
  cdr << ros_message.target_ip;
  // Member: target_port
  cdr << ros_message.target_port;
  // Member: action
  cdr << ros_message.action;
  // Member: send_message
  cdr << ros_message.send_message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  tcp_format::srv::SocketFormat_Request & ros_message)
{
  // Member: target_ip
  cdr >> ros_message.target_ip;

  // Member: target_port
  cdr >> ros_message.target_port;

  // Member: action
  cdr >> ros_message.action;

  // Member: send_message
  cdr >> ros_message.send_message;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
get_serialized_size(
  const tcp_format::srv::SocketFormat_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: target_ip
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.target_ip.size() + 1);
  // Member: target_port
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.target_port.size() + 1);
  // Member: action
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.action.size() + 1);
  // Member: send_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.send_message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
max_serialized_size_SocketFormat_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: target_ip
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: target_port
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: action
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: send_message
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static bool _SocketFormat_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const tcp_format::srv::SocketFormat_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SocketFormat_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<tcp_format::srv::SocketFormat_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SocketFormat_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const tcp_format::srv::SocketFormat_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SocketFormat_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_SocketFormat_Request(full_bounded, 0);
}

static message_type_support_callbacks_t _SocketFormat_Request__callbacks = {
  "tcp_format::srv",
  "SocketFormat_Request",
  _SocketFormat_Request__cdr_serialize,
  _SocketFormat_Request__cdr_deserialize,
  _SocketFormat_Request__get_serialized_size,
  _SocketFormat_Request__max_serialized_size
};

static rosidl_message_type_support_t _SocketFormat_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SocketFormat_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace tcp_format

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_tcp_format
const rosidl_message_type_support_t *
get_message_type_support_handle<tcp_format::srv::SocketFormat_Request>()
{
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tcp_format, srv, SocketFormat_Request)() {
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace tcp_format
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
cdr_serialize(
  const tcp_format::srv::SocketFormat_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: status
  cdr << ros_message.status;
  // Member: receive_message
  cdr << ros_message.receive_message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  tcp_format::srv::SocketFormat_Response & ros_message)
{
  // Member: status
  cdr >> ros_message.status;

  // Member: receive_message
  cdr >> ros_message.receive_message;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
get_serialized_size(
  const tcp_format::srv::SocketFormat_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: status
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.status.size() + 1);
  // Member: receive_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.receive_message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_tcp_format
max_serialized_size_SocketFormat_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: status
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: receive_message
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static bool _SocketFormat_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const tcp_format::srv::SocketFormat_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _SocketFormat_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<tcp_format::srv::SocketFormat_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _SocketFormat_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const tcp_format::srv::SocketFormat_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _SocketFormat_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_SocketFormat_Response(full_bounded, 0);
}

static message_type_support_callbacks_t _SocketFormat_Response__callbacks = {
  "tcp_format::srv",
  "SocketFormat_Response",
  _SocketFormat_Response__cdr_serialize,
  _SocketFormat_Response__cdr_deserialize,
  _SocketFormat_Response__get_serialized_size,
  _SocketFormat_Response__max_serialized_size
};

static rosidl_message_type_support_t _SocketFormat_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SocketFormat_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace tcp_format

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_tcp_format
const rosidl_message_type_support_t *
get_message_type_support_handle<tcp_format::srv::SocketFormat_Response>()
{
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tcp_format, srv, SocketFormat_Response)() {
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace tcp_format
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _SocketFormat__callbacks = {
  "tcp_format::srv",
  "SocketFormat",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tcp_format, srv, SocketFormat_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tcp_format, srv, SocketFormat_Response)(),
};

static rosidl_service_type_support_t _SocketFormat__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_SocketFormat__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace tcp_format

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_tcp_format
const rosidl_service_type_support_t *
get_service_type_support_handle<tcp_format::srv::SocketFormat>()
{
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, tcp_format, srv, SocketFormat)() {
  return &tcp_format::srv::typesupport_fastrtps_cpp::_SocketFormat__handle;
}

#ifdef __cplusplus
}
#endif
