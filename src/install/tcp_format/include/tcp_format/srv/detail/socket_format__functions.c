// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice
#include "tcp_format/srv/detail/socket_format__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `target_ip`
// Member `action`
// Member `send_message`
#include "rosidl_runtime_c/string_functions.h"

bool
tcp_format__srv__SocketFormat_Request__init(tcp_format__srv__SocketFormat_Request * msg)
{
  if (!msg) {
    return false;
  }
  // target_ip
  if (!rosidl_runtime_c__String__init(&msg->target_ip)) {
    tcp_format__srv__SocketFormat_Request__fini(msg);
    return false;
  }
  // port_fd
  // action
  if (!rosidl_runtime_c__String__init(&msg->action)) {
    tcp_format__srv__SocketFormat_Request__fini(msg);
    return false;
  }
  // send_message
  if (!rosidl_runtime_c__String__init(&msg->send_message)) {
    tcp_format__srv__SocketFormat_Request__fini(msg);
    return false;
  }
  return true;
}

void
tcp_format__srv__SocketFormat_Request__fini(tcp_format__srv__SocketFormat_Request * msg)
{
  if (!msg) {
    return;
  }
  // target_ip
  rosidl_runtime_c__String__fini(&msg->target_ip);
  // port_fd
  // action
  rosidl_runtime_c__String__fini(&msg->action);
  // send_message
  rosidl_runtime_c__String__fini(&msg->send_message);
}

tcp_format__srv__SocketFormat_Request *
tcp_format__srv__SocketFormat_Request__create()
{
  tcp_format__srv__SocketFormat_Request * msg = (tcp_format__srv__SocketFormat_Request *)malloc(sizeof(tcp_format__srv__SocketFormat_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(tcp_format__srv__SocketFormat_Request));
  bool success = tcp_format__srv__SocketFormat_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
tcp_format__srv__SocketFormat_Request__destroy(tcp_format__srv__SocketFormat_Request * msg)
{
  if (msg) {
    tcp_format__srv__SocketFormat_Request__fini(msg);
  }
  free(msg);
}


bool
tcp_format__srv__SocketFormat_Request__Sequence__init(tcp_format__srv__SocketFormat_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  tcp_format__srv__SocketFormat_Request * data = NULL;
  if (size) {
    data = (tcp_format__srv__SocketFormat_Request *)calloc(size, sizeof(tcp_format__srv__SocketFormat_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = tcp_format__srv__SocketFormat_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        tcp_format__srv__SocketFormat_Request__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
tcp_format__srv__SocketFormat_Request__Sequence__fini(tcp_format__srv__SocketFormat_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      tcp_format__srv__SocketFormat_Request__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

tcp_format__srv__SocketFormat_Request__Sequence *
tcp_format__srv__SocketFormat_Request__Sequence__create(size_t size)
{
  tcp_format__srv__SocketFormat_Request__Sequence * array = (tcp_format__srv__SocketFormat_Request__Sequence *)malloc(sizeof(tcp_format__srv__SocketFormat_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = tcp_format__srv__SocketFormat_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
tcp_format__srv__SocketFormat_Request__Sequence__destroy(tcp_format__srv__SocketFormat_Request__Sequence * array)
{
  if (array) {
    tcp_format__srv__SocketFormat_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `status`
// Member `receive_message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
tcp_format__srv__SocketFormat_Response__init(tcp_format__srv__SocketFormat_Response * msg)
{
  if (!msg) {
    return false;
  }
  // socket_fd
  // status
  if (!rosidl_runtime_c__String__init(&msg->status)) {
    tcp_format__srv__SocketFormat_Response__fini(msg);
    return false;
  }
  // receive_message
  if (!rosidl_runtime_c__String__init(&msg->receive_message)) {
    tcp_format__srv__SocketFormat_Response__fini(msg);
    return false;
  }
  return true;
}

void
tcp_format__srv__SocketFormat_Response__fini(tcp_format__srv__SocketFormat_Response * msg)
{
  if (!msg) {
    return;
  }
  // socket_fd
  // status
  rosidl_runtime_c__String__fini(&msg->status);
  // receive_message
  rosidl_runtime_c__String__fini(&msg->receive_message);
}

tcp_format__srv__SocketFormat_Response *
tcp_format__srv__SocketFormat_Response__create()
{
  tcp_format__srv__SocketFormat_Response * msg = (tcp_format__srv__SocketFormat_Response *)malloc(sizeof(tcp_format__srv__SocketFormat_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(tcp_format__srv__SocketFormat_Response));
  bool success = tcp_format__srv__SocketFormat_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
tcp_format__srv__SocketFormat_Response__destroy(tcp_format__srv__SocketFormat_Response * msg)
{
  if (msg) {
    tcp_format__srv__SocketFormat_Response__fini(msg);
  }
  free(msg);
}


bool
tcp_format__srv__SocketFormat_Response__Sequence__init(tcp_format__srv__SocketFormat_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  tcp_format__srv__SocketFormat_Response * data = NULL;
  if (size) {
    data = (tcp_format__srv__SocketFormat_Response *)calloc(size, sizeof(tcp_format__srv__SocketFormat_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = tcp_format__srv__SocketFormat_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        tcp_format__srv__SocketFormat_Response__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
tcp_format__srv__SocketFormat_Response__Sequence__fini(tcp_format__srv__SocketFormat_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      tcp_format__srv__SocketFormat_Response__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

tcp_format__srv__SocketFormat_Response__Sequence *
tcp_format__srv__SocketFormat_Response__Sequence__create(size_t size)
{
  tcp_format__srv__SocketFormat_Response__Sequence * array = (tcp_format__srv__SocketFormat_Response__Sequence *)malloc(sizeof(tcp_format__srv__SocketFormat_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = tcp_format__srv__SocketFormat_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
tcp_format__srv__SocketFormat_Response__Sequence__destroy(tcp_format__srv__SocketFormat_Response__Sequence * array)
{
  if (array) {
    tcp_format__srv__SocketFormat_Response__Sequence__fini(array);
  }
  free(array);
}
