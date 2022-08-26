// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tcp_format:srv/SocketClose.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__STRUCT_H_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in srv/SocketClose in the package tcp_format.
typedef struct tcp_format__srv__SocketClose_Request
{
  int64_t socket_fd;
} tcp_format__srv__SocketClose_Request;

// Struct for a sequence of tcp_format__srv__SocketClose_Request.
typedef struct tcp_format__srv__SocketClose_Request__Sequence
{
  tcp_format__srv__SocketClose_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__SocketClose_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/SocketClose in the package tcp_format.
typedef struct tcp_format__srv__SocketClose_Response
{
  rosidl_runtime_c__String status;
} tcp_format__srv__SocketClose_Response;

// Struct for a sequence of tcp_format__srv__SocketClose_Response.
typedef struct tcp_format__srv__SocketClose_Response__Sequence
{
  tcp_format__srv__SocketClose_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__SocketClose_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_CLOSE__STRUCT_H_
