# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arc/Documents/automatic_arc_melting_system/src/plc_control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arc/Documents/automatic_arc_melting_system/build/plc_control

# Include any dependencies generated for this target.
include CMakeFiles/plc_socket.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plc_socket.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plc_socket.dir/flags.make

CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o: CMakeFiles/plc_socket.dir/flags.make
CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o: /home/arc/Documents/automatic_arc_melting_system/src/plc_control/src/plc_socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arc/Documents/automatic_arc_melting_system/build/plc_control/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o -c /home/arc/Documents/automatic_arc_melting_system/src/plc_control/src/plc_socket.cpp

CMakeFiles/plc_socket.dir/src/plc_socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plc_socket.dir/src/plc_socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arc/Documents/automatic_arc_melting_system/src/plc_control/src/plc_socket.cpp > CMakeFiles/plc_socket.dir/src/plc_socket.cpp.i

CMakeFiles/plc_socket.dir/src/plc_socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plc_socket.dir/src/plc_socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arc/Documents/automatic_arc_melting_system/src/plc_control/src/plc_socket.cpp -o CMakeFiles/plc_socket.dir/src/plc_socket.cpp.s

# Object files for target plc_socket
plc_socket_OBJECTS = \
"CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o"

# External object files for target plc_socket
plc_socket_EXTERNAL_OBJECTS =

libplc_socket.a: CMakeFiles/plc_socket.dir/src/plc_socket.cpp.o
libplc_socket.a: CMakeFiles/plc_socket.dir/build.make
libplc_socket.a: CMakeFiles/plc_socket.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arc/Documents/automatic_arc_melting_system/build/plc_control/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libplc_socket.a"
	$(CMAKE_COMMAND) -P CMakeFiles/plc_socket.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plc_socket.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plc_socket.dir/build: libplc_socket.a

.PHONY : CMakeFiles/plc_socket.dir/build

CMakeFiles/plc_socket.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plc_socket.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plc_socket.dir/clean

CMakeFiles/plc_socket.dir/depend:
	cd /home/arc/Documents/automatic_arc_melting_system/build/plc_control && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arc/Documents/automatic_arc_melting_system/src/plc_control /home/arc/Documents/automatic_arc_melting_system/src/plc_control /home/arc/Documents/automatic_arc_melting_system/build/plc_control /home/arc/Documents/automatic_arc_melting_system/build/plc_control /home/arc/Documents/automatic_arc_melting_system/build/plc_control/CMakeFiles/plc_socket.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plc_socket.dir/depend

