// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from tcp_format:srv/CobottaBcap.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_H_
#define TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'action'
// Member 'target'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/CobottaBcap in the package tcp_format.
typedef struct tcp_format__srv__CobottaBcap_Request
{
  rosidl_runtime_c__String action;
  rosidl_runtime_c__String target;
} tcp_format__srv__CobottaBcap_Request;

// Struct for a sequence of tcp_format__srv__CobottaBcap_Request.
typedef struct tcp_format__srv__CobottaBcap_Request__Sequence
{
  tcp_format__srv__CobottaBcap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__CobottaBcap_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/CobottaBcap in the package tcp_format.
typedef struct tcp_format__srv__CobottaBcap_Response
{
  rosidl_runtime_c__String status;
  rosidl_runtime_c__String message;
} tcp_format__srv__CobottaBcap_Response;

// Struct for a sequence of tcp_format__srv__CobottaBcap_Response.
typedef struct tcp_format__srv__CobottaBcap_Response__Sequence
{
  tcp_format__srv__CobottaBcap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} tcp_format__srv__CobottaBcap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TCP_FORMAT__SRV__DETAIL__COBOTTA_BCAP__STRUCT_H_
