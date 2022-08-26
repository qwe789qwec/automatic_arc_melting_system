// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "tcp_format/srv/detail/socket_format__rosidl_typesupport_introspection_c.h"
#include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "tcp_format/srv/detail/socket_format__functions.h"
#include "tcp_format/srv/detail/socket_format__struct.h"


// Include directives for member types
// Member `target_ip`
// Member `target_port`
// Member `action`
// Member `send_message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tcp_format__srv__SocketFormat_Request__init(message_memory);
}

void SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_fini_function(void * message_memory)
{
  tcp_format__srv__SocketFormat_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_member_array[4] = {
  {
    "target_ip",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Request, target_ip),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_port",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Request, target_port),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "action",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Request, action),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "send_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Request, send_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_members = {
  "tcp_format__srv",  // message namespace
  "SocketFormat_Request",  // message name
  4,  // number of fields
  sizeof(tcp_format__srv__SocketFormat_Request),
  SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_member_array,  // message members
  SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_type_support_handle = {
  0,
  &SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Request)() {
  if (!SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_type_support_handle.typesupport_identifier) {
    SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &SocketFormat_Request__rosidl_typesupport_introspection_c__SocketFormat_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "tcp_format/srv/detail/socket_format__rosidl_typesupport_introspection_c.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "tcp_format/srv/detail/socket_format__functions.h"
// already included above
// #include "tcp_format/srv/detail/socket_format__struct.h"


// Include directives for member types
// Member `status`
// Member `receive_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tcp_format__srv__SocketFormat_Response__init(message_memory);
}

void SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_fini_function(void * message_memory)
{
  tcp_format__srv__SocketFormat_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "receive_message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketFormat_Response, receive_message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_members = {
  "tcp_format__srv",  // message namespace
  "SocketFormat_Response",  // message name
  2,  // number of fields
  sizeof(tcp_format__srv__SocketFormat_Response),
  SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_member_array,  // message members
  SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_type_support_handle = {
  0,
  &SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Response)() {
  if (!SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_type_support_handle.typesupport_identifier) {
    SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &SocketFormat_Response__rosidl_typesupport_introspection_c__SocketFormat_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "tcp_format/srv/detail/socket_format__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_members = {
  "tcp_format__srv",  // service namespace
  "SocketFormat",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_Request_message_type_support_handle,
  NULL  // response message
  // tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_Response_message_type_support_handle
};

static rosidl_service_type_support_t tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_type_support_handle = {
  0,
  &tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat)() {
  if (!tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_type_support_handle.typesupport_identifier) {
    tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketFormat_Response)()->data;
  }

  return &tcp_format__srv__detail__socket_format__rosidl_typesupport_introspection_c__SocketFormat_service_type_support_handle;
}
