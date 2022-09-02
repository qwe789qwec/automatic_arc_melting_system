// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from tcp_format:srv/CobottaBcap.idl
// generated code does not contain a copyright notice
#include "tcp_format/srv/detail/cobotta_bcap__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `action`
// Member `target`
#include "rosidl_runtime_c/string_functions.h"

bool
tcp_format__srv__CobottaBcap_Request__init(tcp_format__srv__CobottaBcap_Request * msg)
{
  if (!msg) {
    return false;
  }
  // action
  if (!rosidl_runtime_c__String__init(&msg->action)) {
    tcp_format__srv__CobottaBcap_Request__fini(msg);
    return false;
  }
  // target
  if (!rosidl_runtime_c__String__init(&msg->target)) {
    tcp_format__srv__CobottaBcap_Request__fini(msg);
    return false;
  }
  return true;
}

void
tcp_format__srv__CobottaBcap_Request__fini(tcp_format__srv__CobottaBcap_Request * msg)
{
  if (!msg) {
    return;
  }
  // action
  rosidl_runtime_c__String__fini(&msg->action);
  // target
  rosidl_runtime_c__String__fini(&msg->target);
}

tcp_format__srv__CobottaBcap_Request *
tcp_format__srv__CobottaBcap_Request__create()
{
  tcp_format__srv__CobottaBcap_Request * msg = (tcp_format__srv__CobottaBcap_Request *)malloc(sizeof(tcp_format__srv__CobottaBcap_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(tcp_format__srv__CobottaBcap_Request));
  bool success = tcp_format__srv__CobottaBcap_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
tcp_format__srv__CobottaBcap_Request__destroy(tcp_format__srv__CobottaBcap_Request * msg)
{
  if (msg) {
    tcp_format__srv__CobottaBcap_Request__fini(msg);
  }
  free(msg);
}


bool
tcp_format__srv__CobottaBcap_Request__Sequence__init(tcp_format__srv__CobottaBcap_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  tcp_format__srv__CobottaBcap_Request * data = NULL;
  if (size) {
    data = (tcp_format__srv__CobottaBcap_Request *)calloc(size, sizeof(tcp_format__srv__CobottaBcap_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = tcp_format__srv__CobottaBcap_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        tcp_format__srv__CobottaBcap_Request__fini(&data[i - 1]);
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
tcp_format__srv__CobottaBcap_Request__Sequence__fini(tcp_format__srv__CobottaBcap_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      tcp_format__srv__CobottaBcap_Request__fini(&array->data[i]);
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

tcp_format__srv__CobottaBcap_Request__Sequence *
tcp_format__srv__CobottaBcap_Request__Sequence__create(size_t size)
{
  tcp_format__srv__CobottaBcap_Request__Sequence * array = (tcp_format__srv__CobottaBcap_Request__Sequence *)malloc(sizeof(tcp_format__srv__CobottaBcap_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = tcp_format__srv__CobottaBcap_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
tcp_format__srv__CobottaBcap_Request__Sequence__destroy(tcp_format__srv__CobottaBcap_Request__Sequence * array)
{
  if (array) {
    tcp_format__srv__CobottaBcap_Request__Sequence__fini(array);
  }
  free(array);
}


// Include directives for member types
// Member `status`
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
tcp_format__srv__CobottaBcap_Response__init(tcp_format__srv__CobottaBcap_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  if (!rosidl_runtime_c__String__init(&msg->status)) {
    tcp_format__srv__CobottaBcap_Response__fini(msg);
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    tcp_format__srv__CobottaBcap_Response__fini(msg);
    return false;
  }
  return true;
}

void
tcp_format__srv__CobottaBcap_Response__fini(tcp_format__srv__CobottaBcap_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  rosidl_runtime_c__String__fini(&msg->status);
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

tcp_format__srv__CobottaBcap_Response *
tcp_format__srv__CobottaBcap_Response__create()
{
  tcp_format__srv__CobottaBcap_Response * msg = (tcp_format__srv__CobottaBcap_Response *)malloc(sizeof(tcp_format__srv__CobottaBcap_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(tcp_format__srv__CobottaBcap_Response));
  bool success = tcp_format__srv__CobottaBcap_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
tcp_format__srv__CobottaBcap_Response__destroy(tcp_format__srv__CobottaBcap_Response * msg)
{
  if (msg) {
    tcp_format__srv__CobottaBcap_Response__fini(msg);
  }
  free(msg);
}


bool
tcp_format__srv__CobottaBcap_Response__Sequence__init(tcp_format__srv__CobottaBcap_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  tcp_format__srv__CobottaBcap_Response * data = NULL;
  if (size) {
    data = (tcp_format__srv__CobottaBcap_Response *)calloc(size, sizeof(tcp_format__srv__CobottaBcap_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = tcp_format__srv__CobottaBcap_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        tcp_format__srv__CobottaBcap_Response__fini(&data[i - 1]);
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
tcp_format__srv__CobottaBcap_Response__Sequence__fini(tcp_format__srv__CobottaBcap_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      tcp_format__srv__CobottaBcap_Response__fini(&array->data[i]);
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

tcp_format__srv__CobottaBcap_Response__Sequence *
tcp_format__srv__CobottaBcap_Response__Sequence__create(size_t size)
{
  tcp_format__srv__CobottaBcap_Response__Sequence * array = (tcp_format__srv__CobottaBcap_Response__Sequence *)malloc(sizeof(tcp_format__srv__CobottaBcap_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = tcp_format__srv__CobottaBcap_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
tcp_format__srv__CobottaBcap_Response__Sequence__destroy(tcp_format__srv__CobottaBcap_Response__Sequence * array)
{
  if (array) {
    tcp_format__srv__CobottaBcap_Response__Sequence__fini(array);
  }
  free(array);
}
