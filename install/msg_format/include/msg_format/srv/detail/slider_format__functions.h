// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from msg_format:srv/SliderFormat.idl
// generated code does not contain a copyright notice

#ifndef MSG_FORMAT__SRV__DETAIL__SLIDER_FORMAT__FUNCTIONS_H_
#define MSG_FORMAT__SRV__DETAIL__SLIDER_FORMAT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "msg_format/msg/rosidl_generator_c__visibility_control.h"

#include "msg_format/srv/detail/slider_format__struct.h"

/// Initialize srv/SliderFormat message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * msg_format__srv__SliderFormat_Request
 * )) before or use
 * msg_format__srv__SliderFormat_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
bool
msg_format__srv__SliderFormat_Request__init(msg_format__srv__SliderFormat_Request * msg);

/// Finalize srv/SliderFormat message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Request__fini(msg_format__srv__SliderFormat_Request * msg);

/// Create srv/SliderFormat message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * msg_format__srv__SliderFormat_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
msg_format__srv__SliderFormat_Request *
msg_format__srv__SliderFormat_Request__create();

/// Destroy srv/SliderFormat message.
/**
 * It calls
 * msg_format__srv__SliderFormat_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Request__destroy(msg_format__srv__SliderFormat_Request * msg);


/// Initialize array of srv/SliderFormat messages.
/**
 * It allocates the memory for the number of elements and calls
 * msg_format__srv__SliderFormat_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
bool
msg_format__srv__SliderFormat_Request__Sequence__init(msg_format__srv__SliderFormat_Request__Sequence * array, size_t size);

/// Finalize array of srv/SliderFormat messages.
/**
 * It calls
 * msg_format__srv__SliderFormat_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Request__Sequence__fini(msg_format__srv__SliderFormat_Request__Sequence * array);

/// Create array of srv/SliderFormat messages.
/**
 * It allocates the memory for the array and calls
 * msg_format__srv__SliderFormat_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
msg_format__srv__SliderFormat_Request__Sequence *
msg_format__srv__SliderFormat_Request__Sequence__create(size_t size);

/// Destroy array of srv/SliderFormat messages.
/**
 * It calls
 * msg_format__srv__SliderFormat_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Request__Sequence__destroy(msg_format__srv__SliderFormat_Request__Sequence * array);

/// Initialize srv/SliderFormat message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * msg_format__srv__SliderFormat_Response
 * )) before or use
 * msg_format__srv__SliderFormat_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
bool
msg_format__srv__SliderFormat_Response__init(msg_format__srv__SliderFormat_Response * msg);

/// Finalize srv/SliderFormat message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Response__fini(msg_format__srv__SliderFormat_Response * msg);

/// Create srv/SliderFormat message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * msg_format__srv__SliderFormat_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
msg_format__srv__SliderFormat_Response *
msg_format__srv__SliderFormat_Response__create();

/// Destroy srv/SliderFormat message.
/**
 * It calls
 * msg_format__srv__SliderFormat_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Response__destroy(msg_format__srv__SliderFormat_Response * msg);


/// Initialize array of srv/SliderFormat messages.
/**
 * It allocates the memory for the number of elements and calls
 * msg_format__srv__SliderFormat_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
bool
msg_format__srv__SliderFormat_Response__Sequence__init(msg_format__srv__SliderFormat_Response__Sequence * array, size_t size);

/// Finalize array of srv/SliderFormat messages.
/**
 * It calls
 * msg_format__srv__SliderFormat_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Response__Sequence__fini(msg_format__srv__SliderFormat_Response__Sequence * array);

/// Create array of srv/SliderFormat messages.
/**
 * It allocates the memory for the array and calls
 * msg_format__srv__SliderFormat_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
msg_format__srv__SliderFormat_Response__Sequence *
msg_format__srv__SliderFormat_Response__Sequence__create(size_t size);

/// Destroy array of srv/SliderFormat messages.
/**
 * It calls
 * msg_format__srv__SliderFormat_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_msg_format
void
msg_format__srv__SliderFormat_Response__Sequence__destroy(msg_format__srv__SliderFormat_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // MSG_FORMAT__SRV__DETAIL__SLIDER_FORMAT__FUNCTIONS_H_
