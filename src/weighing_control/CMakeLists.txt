cmake_minimum_required(VERSION 3.5)
project(weighing_control)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

include_directories(include)

find_package(rclcpp REQUIRED)
find_package(msg_format REQUIRED)
find_package(tcp_handle REQUIRED)
find_package(ros2_utils REQUIRED)

add_executable(WeighingMain
src/weighing_main.cpp src/weighing_node.cpp src/weighing_machine.cpp)

ament_target_dependencies(WeighingMain
rclcpp msg_format tcp_handle ros2_utils)

install(
  DIRECTORY include/
  DESTINATION include
)

install(
  TARGETS
  WeighingMain
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
