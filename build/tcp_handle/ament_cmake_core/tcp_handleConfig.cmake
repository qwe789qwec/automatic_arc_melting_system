# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_tcp_handle_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED tcp_handle_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(tcp_handle_FOUND FALSE)
  elseif(NOT tcp_handle_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(tcp_handle_FOUND FALSE)
  endif()
  return()
endif()
set(_tcp_handle_CONFIG_INCLUDED TRUE)

# output package information
if(NOT tcp_handle_FIND_QUIETLY)
  message(STATUS "Found tcp_handle: 0.0.0 (${tcp_handle_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'tcp_handle' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${tcp_handle_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(tcp_handle_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${tcp_handle_DIR}/${_extra}")
endforeach()
