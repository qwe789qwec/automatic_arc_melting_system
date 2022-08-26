# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cobotta_bcap_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cobotta_bcap_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cobotta_bcap_FOUND FALSE)
  elseif(NOT cobotta_bcap_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cobotta_bcap_FOUND FALSE)
  endif()
  return()
endif()
set(_cobotta_bcap_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cobotta_bcap_FIND_QUIETLY)
  message(STATUS "Found cobotta_bcap: 0.0.0 (${cobotta_bcap_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cobotta_bcap' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${cobotta_bcap_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cobotta_bcap_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${cobotta_bcap_DIR}/${_extra}")
endforeach()
