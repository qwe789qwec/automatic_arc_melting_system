// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msg_format:srv/WeighingFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_H_
#define MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/WeighingFormat in the package msg_format.
typedef struct msg_format__srv__WeighingFormat_Request
{
  rosidl_runtime_c__String action;
} msg_format__srv__WeighingFormat_Request;

// Struct for a sequence of msg_format__srv__WeighingFormat_Request.
typedef struct msg_format__srv__WeighingFormat_Request__Sequence
{
  msg_format__srv__WeighingFormat_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_format__srv__WeighingFormat_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/WeighingFormat in the package msg_format.
typedef struct msg_format__srv__WeighingFormat_Response
{
  rosidl_runtime_c__String result;
} msg_format__srv__WeighingFormat_Response;

// Struct for a sequence of msg_format__srv__WeighingFormat_Response.
typedef struct msg_format__srv__WeighingFormat_Response__Sequence
{
  msg_format__srv__WeighingFormat_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_format__srv__WeighingFormat_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSG_FORMAT__SRV__DETAIL__WEIGHING_FORMAT__STRUCT_H_
