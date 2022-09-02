// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from tcp_format:srv/SocketFormat.idl
// generated code does not contain a copyright notice

#ifndef TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__FUNCTIONS_H_
#define TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "tcp_format/msg/rosidl_generator_c__visibility_control.h"

#include "tcp_format/srv/detail/socket_format__struct.h"

/// Initialize srv/SocketFormat message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * tcp_format__srv__SocketFormat_Request
 * )) before or use
 * tcp_format__srv__SocketFormat_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
bool
tcp_format__srv__SocketFormat_Request__init(tcp_format__srv__SocketFormat_Request * msg);

/// Finalize srv/SocketFormat message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Request__fini(tcp_format__srv__SocketFormat_Request * msg);

/// Create srv/SocketFormat message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * tcp_format__srv__SocketFormat_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
tcp_format__srv__SocketFormat_Request *
tcp_format__srv__SocketFormat_Request__create();

/// Destroy srv/SocketFormat message.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Request__destroy(tcp_format__srv__SocketFormat_Request * msg);


/// Initialize array of srv/SocketFormat messages.
/**
 * It allocates the memory for the number of elements and calls
 * tcp_format__srv__SocketFormat_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
bool
tcp_format__srv__SocketFormat_Request__Sequence__init(tcp_format__srv__SocketFormat_Request__Sequence * array, size_t size);

/// Finalize array of srv/SocketFormat messages.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Request__Sequence__fini(tcp_format__srv__SocketFormat_Request__Sequence * array);

/// Create array of srv/SocketFormat messages.
/**
 * It allocates the memory for the array and calls
 * tcp_format__srv__SocketFormat_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
tcp_format__srv__SocketFormat_Request__Sequence *
tcp_format__srv__SocketFormat_Request__Sequence__create(size_t size);

/// Destroy array of srv/SocketFormat messages.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Request__Sequence__destroy(tcp_format__srv__SocketFormat_Request__Sequence * array);

/// Initialize srv/SocketFormat message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * tcp_format__srv__SocketFormat_Response
 * )) before or use
 * tcp_format__srv__SocketFormat_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
bool
tcp_format__srv__SocketFormat_Response__init(tcp_format__srv__SocketFormat_Response * msg);

/// Finalize srv/SocketFormat message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Response__fini(tcp_format__srv__SocketFormat_Response * msg);

/// Create srv/SocketFormat message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * tcp_format__srv__SocketFormat_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
tcp_format__srv__SocketFormat_Response *
tcp_format__srv__SocketFormat_Response__create();

/// Destroy srv/SocketFormat message.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Response__destroy(tcp_format__srv__SocketFormat_Response * msg);


/// Initialize array of srv/SocketFormat messages.
/**
 * It allocates the memory for the number of elements and calls
 * tcp_format__srv__SocketFormat_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
bool
tcp_format__srv__SocketFormat_Response__Sequence__init(tcp_format__srv__SocketFormat_Response__Sequence * array, size_t size);

/// Finalize array of srv/SocketFormat messages.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Response__Sequence__fini(tcp_format__srv__SocketFormat_Response__Sequence * array);

/// Create array of srv/SocketFormat messages.
/**
 * It allocates the memory for the array and calls
 * tcp_format__srv__SocketFormat_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
tcp_format__srv__SocketFormat_Response__Sequence *
tcp_format__srv__SocketFormat_Response__Sequence__create(size_t size);

/// Destroy array of srv/SocketFormat messages.
/**
 * It calls
 * tcp_format__srv__SocketFormat_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_tcp_format
void
tcp_format__srv__SocketFormat_Response__Sequence__destroy(tcp_format__srv__SocketFormat_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // TCP_FORMAT__SRV__DETAIL__SOCKET_FORMAT__FUNCTIONS_H_
