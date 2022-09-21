// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from msg_format:srv/WeighingFormat.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "msg_format/srv/detail/weighing_format__rosidl_typesupport_introspection_c.h"
#include "msg_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "msg_format/srv/detail/weighing_format__functions.h"
#include "msg_format/srv/detail/weighing_format__struct.h"


// Include directives for member types
// Member `action`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msg_format__srv__WeighingFormat_Request__init(message_memory);
}

void WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_fini_function(void * message_memory)
{
  msg_format__srv__WeighingFormat_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_member_array[1] = {
  {
    "action",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_format__srv__WeighingFormat_Request, action),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_members = {
  "msg_format__srv",  // message namespace
  "WeighingFormat_Request",  // message name
  1,  // number of fields
  sizeof(msg_format__srv__WeighingFormat_Request),
  WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_member_array,  // message members
  WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_type_support_handle = {
  0,
  &WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msg_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Request)() {
  if (!WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_type_support_handle.typesupport_identifier) {
    WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &WeighingFormat_Request__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "msg_format/srv/detail/weighing_format__rosidl_typesupport_introspection_c.h"
// already included above
// #include "msg_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "msg_format/srv/detail/weighing_format__functions.h"
// already included above
// #include "msg_format/srv/detail/weighing_format__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  msg_format__srv__WeighingFormat_Response__init(message_memory);
}

void WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_fini_function(void * message_memory)
{
  msg_format__srv__WeighingFormat_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_member_array[1] = {
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(msg_format__srv__WeighingFormat_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_members = {
  "msg_format__srv",  // message namespace
  "WeighingFormat_Response",  // message name
  1,  // number of fields
  sizeof(msg_format__srv__WeighingFormat_Response),
  WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_member_array,  // message members
  WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_type_support_handle = {
  0,
  &WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msg_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Response)() {
  if (!WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_type_support_handle.typesupport_identifier) {
    WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &WeighingFormat_Response__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "msg_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "msg_format/srv/detail/weighing_format__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_members = {
  "msg_format__srv",  // service namespace
  "WeighingFormat",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_Request_message_type_support_handle,
  NULL  // response message
  // msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_Response_message_type_support_handle
};

static rosidl_service_type_support_t msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_type_support_handle = {
  0,
  &msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_msg_format
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat)() {
  if (!msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_type_support_handle.typesupport_identifier) {
    msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, msg_format, srv, WeighingFormat_Response)()->data;
  }

  return &msg_format__srv__detail__weighing_format__rosidl_typesupport_introspection_c__WeighingFormat_service_type_support_handle;
}
