// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from msg_format:srv/GripperFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__STRUCT_H_
#define MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__STRUCT_H_

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

// Struct defined in srv/GripperFormat in the package msg_format.
typedef struct msg_format__srv__GripperFormat_Request
{
  rosidl_runtime_c__String action;
} msg_format__srv__GripperFormat_Request;

// Struct for a sequence of msg_format__srv__GripperFormat_Request.
typedef struct msg_format__srv__GripperFormat_Request__Sequence
{
  msg_format__srv__GripperFormat_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_format__srv__GripperFormat_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/GripperFormat in the package msg_format.
typedef struct msg_format__srv__GripperFormat_Response
{
  rosidl_runtime_c__String result;
} msg_format__srv__GripperFormat_Response;

// Struct for a sequence of msg_format__srv__GripperFormat_Response.
typedef struct msg_format__srv__GripperFormat_Response__Sequence
{
  msg_format__srv__GripperFormat_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} msg_format__srv__GripperFormat_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MSG_FORMAT__SRV__DETAIL__GRIPPER_FORMAT__STRUCT_H_
