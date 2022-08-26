// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice
#include "tcp_format/srv/detail/socket_format__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "tcp_format/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "tcp_format/srv/detail/socket_format__struct.h"
#include "tcp_format/srv/detail/socket_format__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // action, send_message, target_ip, target_port
#include "rosidl_runtime_c/string_functions.h"  // action, send_message, target_ip, target_port

// forward declare type support functions


using _SocketFormat_Request__ros_msg_type = tcp_format__srv__SocketFormat_Request;

static bool _SocketFormat_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SocketFormat_Request__ros_msg_type * ros_message = static_cast<const _SocketFormat_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: target_ip
  {
    const rosidl_runtime_c__String * str = &ros_message->target_ip;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: target_port
  {
    const rosidl_runtime_c__String * str = &ros_message->target_port;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: action
  {
    const rosidl_runtime_c__String * str = &ros_message->action;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: send_message
  {
    const rosidl_runtime_c__String * str = &ros_message->send_message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _SocketFormat_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SocketFormat_Request__ros_msg_type * ros_message = static_cast<_SocketFormat_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: target_ip
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->target_ip.data) {
      rosidl_runtime_c__String__init(&ros_message->target_ip);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->target_ip,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'target_ip'\n");
      return false;
    }
  }

  // Field name: target_port
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->target_port.data) {
      rosidl_runtime_c__String__init(&ros_message->target_port);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->target_port,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'target_port'\n");
      return false;
    }
  }

  // Field name: action
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->action.data) {
      rosidl_runtime_c__String__init(&ros_message->action);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->action,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'action'\n");
      return false;
    }
  }

  // Field name: send_message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->send_message.data) {
      rosidl_runtime_c__String__init(&ros_message->send_message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->send_message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'send_message'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tcp_format
size_t get_serialized_size_tcp_format__srv__SocketFormat_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SocketFormat_Request__ros_msg_type * ros_message = static_cast<const _SocketFormat_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name target_ip
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->target_ip.size + 1);
  // field.name target_port
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->target_port.size + 1);
  // field.name action
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->action.size + 1);
  // field.name send_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->send_message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _SocketFormat_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_tcp_format__srv__SocketFormat_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tcp_format
size_t max_serialized_size_tcp_format__srv__SocketFormat_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: target_ip
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: target_port
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: action
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: send_message
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

static size_t _SocketFormat_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_tcp_format__srv__SocketFormat_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_SocketFormat_Request = {
  "tcp_format::srv",
  "SocketFormat_Request",
  _SocketFormat_Request__cdr_serialize,
  _SocketFormat_Request__cdr_deserialize,
  _SocketFormat_Request__get_serialized_size,
  _SocketFormat_Request__max_serialized_size
};

static rosidl_message_type_support_t _SocketFormat_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SocketFormat_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tcp_format, srv, SocketFormat_Request)() {
  return &_SocketFormat_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "tcp_format/srv/detail/socket_format__struct.h"
// already included above
// #include "tcp_format/srv/detail/socket_format__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

// already included above
// #include "rosidl_runtime_c/string.h"  // receive_message, status
// already included above
// #include "rosidl_runtime_c/string_functions.h"  // receive_message, status

// forward declare type support functions


using _SocketFormat_Response__ros_msg_type = tcp_format__srv__SocketFormat_Response;

static bool _SocketFormat_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SocketFormat_Response__ros_msg_type * ros_message = static_cast<const _SocketFormat_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: status
  {
    const rosidl_runtime_c__String * str = &ros_message->status;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: receive_message
  {
    const rosidl_runtime_c__String * str = &ros_message->receive_message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _SocketFormat_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SocketFormat_Response__ros_msg_type * ros_message = static_cast<_SocketFormat_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: status
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->status.data) {
      rosidl_runtime_c__String__init(&ros_message->status);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->status,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'status'\n");
      return false;
    }
  }

  // Field name: receive_message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->receive_message.data) {
      rosidl_runtime_c__String__init(&ros_message->receive_message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->receive_message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'receive_message'\n");
      return false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tcp_format
size_t get_serialized_size_tcp_format__srv__SocketFormat_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SocketFormat_Response__ros_msg_type * ros_message = static_cast<const _SocketFormat_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name status
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->status.size + 1);
  // field.name receive_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->receive_message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _SocketFormat_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_tcp_format__srv__SocketFormat_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_tcp_format
size_t max_serialized_size_tcp_format__srv__SocketFormat_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: status
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: receive_message
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

static size_t _SocketFormat_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_tcp_format__srv__SocketFormat_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_SocketFormat_Response = {
  "tcp_format::srv",
  "SocketFormat_Response",
  _SocketFormat_Response__cdr_serialize,
  _SocketFormat_Response__cdr_deserialize,
  _SocketFormat_Response__get_serialized_size,
  _SocketFormat_Response__max_serialized_size
};

static rosidl_message_type_support_t _SocketFormat_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SocketFormat_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tcp_format, srv, SocketFormat_Response)() {
  return &_SocketFormat_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "tcp_format/srv/socket_format.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SocketFormat__callbacks = {
  "tcp_format::srv",
  "SocketFormat",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tcp_format, srv, SocketFormat_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tcp_format, srv, SocketFormat_Response)(),
};

static rosidl_service_type_support_t SocketFormat__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SocketFormat__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, tcp_format, srv, SocketFormat)() {
  return &SocketFormat__handle;
}

#if defined(__cplusplus)
}
#endif
