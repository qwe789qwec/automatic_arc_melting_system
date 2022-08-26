// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from tcp_format:srv/SocketClose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "tcp_format/srv/detail/socket_close__rosidl_typesupport_introspection_c.h"
#include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "tcp_format/srv/detail/socket_close__functions.h"
#include "tcp_format/srv/detail/socket_close__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tcp_format__srv__SocketClose_Request__init(message_memory);
}

void SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_fini_function(void * message_memory)
{
  tcp_format__srv__SocketClose_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_member_array[1] = {
  {
    "socket_fd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketClose_Request, socket_fd),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_members = {
  "tcp_format__srv",  // message namespace
  "SocketClose_Request",  // message name
  1,  // number of fields
  sizeof(tcp_format__srv__SocketClose_Request),
  SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_member_array,  // message members
  SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_type_support_handle = {
  0,
  &SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Request)() {
  if (!SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_type_support_handle.typesupport_identifier) {
    SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &SocketClose_Request__rosidl_typesupport_introspection_c__SocketClose_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "tcp_format/srv/detail/socket_close__rosidl_typesupport_introspection_c.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "tcp_format/srv/detail/socket_close__functions.h"
// already included above
// #include "tcp_format/srv/detail/socket_close__struct.h"


// Include directives for member types
// Member `status`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  tcp_format__srv__SocketClose_Response__init(message_memory);
}

void SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_fini_function(void * message_memory)
{
  tcp_format__srv__SocketClose_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_member_array[1] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(tcp_format__srv__SocketClose_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_members = {
  "tcp_format__srv",  // message namespace
  "SocketClose_Response",  // message name
  1,  // number of fields
  sizeof(tcp_format__srv__SocketClose_Response),
  SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_member_array,  // message members
  SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_type_support_handle = {
  0,
  &SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Response)() {
  if (!SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_type_support_handle.typesupport_identifier) {
    SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &SocketClose_Response__rosidl_typesupport_introspection_c__SocketClose_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "tcp_format/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "tcp_format/srv/detail/socket_close__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_members = {
  "tcp_format__srv",  // service namespace
  "SocketClose",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_Request_message_type_support_handle,
  NULL  // response message
  // tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_Response_message_type_support_handle
};

static rosidl_service_type_support_t tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_type_support_handle = {
  0,
  &tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_tcp_format
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose)() {
  if (!tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_type_support_handle.typesupport_identifier) {
    tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, tcp_format, srv, SocketClose_Response)()->data;
  }

  return &tcp_format__srv__detail__socket_close__rosidl_typesupport_introspection_c__SocketClose_service_type_support_handle;
}
