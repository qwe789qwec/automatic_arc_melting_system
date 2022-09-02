// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__STRUCT_H_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target_ip'
// Member 'action'
// Member 'send_message'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/SocketFormat in the package tcp_format.
typedef struct tcp_format__srv__SocketFormat_Request
{
  rosidl_runtime_c__String target_ip;
  int64_t port_fd;
  rosidl_runtime_c__String action;
  rosidl_runtime_c__String send_message;
} tcp_format__srv__SocketFormat_Request;

// Struct for a sequence of tcp_format__srv__SocketFormat_Request.
typedef struct tcp_format__srv__SocketFormat_Request__Sequence
{
  tcp_format__srv__SocketFormat_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__SocketFormat_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
// Member 'receive_message'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/SocketFormat in the package tcp_format.
typedef struct tcp_format__srv__SocketFormat_Response
{
  int64_t socket_fd;
  rosidl_runtime_c__String status;
  rosidl_runtime_c__String receive_message;
} tcp_format__srv__SocketFormat_Response;

// Struct for a sequence of tcp_format__srv__SocketFormat_Response.
typedef struct tcp_format__srv__SocketFormat_Response__Sequence
{
  tcp_format__srv__SocketFormat_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__SocketFormat_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__STRUCT_H_
