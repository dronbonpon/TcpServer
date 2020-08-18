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
CMAKE_SOURCE_DIR = /mnt/d/tcp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/tcp/build

# Include any dependencies generated for this target.
include CMakeFiles/tcp_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcp_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcp_server.dir/flags.make

CMakeFiles/tcp_server.dir/tcp_start.cpp.o: CMakeFiles/tcp_server.dir/flags.make
CMakeFiles/tcp_server.dir/tcp_start.cpp.o: ../tcp_start.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/tcp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcp_server.dir/tcp_start.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_server.dir/tcp_start.cpp.o -c /mnt/d/tcp/tcp_start.cpp

CMakeFiles/tcp_server.dir/tcp_start.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_server.dir/tcp_start.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/tcp/tcp_start.cpp > CMakeFiles/tcp_server.dir/tcp_start.cpp.i

CMakeFiles/tcp_server.dir/tcp_start.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_server.dir/tcp_start.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/tcp/tcp_start.cpp -o CMakeFiles/tcp_server.dir/tcp_start.cpp.s

CMakeFiles/tcp_server.dir/server.cpp.o: CMakeFiles/tcp_server.dir/flags.make
CMakeFiles/tcp_server.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/tcp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcp_server.dir/server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_server.dir/server.cpp.o -c /mnt/d/tcp/server.cpp

CMakeFiles/tcp_server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_server.dir/server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/tcp/server.cpp > CMakeFiles/tcp_server.dir/server.cpp.i

CMakeFiles/tcp_server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_server.dir/server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/tcp/server.cpp -o CMakeFiles/tcp_server.dir/server.cpp.s

CMakeFiles/tcp_server.dir/socket.cpp.o: CMakeFiles/tcp_server.dir/flags.make
CMakeFiles/tcp_server.dir/socket.cpp.o: ../socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/tcp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcp_server.dir/socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcp_server.dir/socket.cpp.o -c /mnt/d/tcp/socket.cpp

CMakeFiles/tcp_server.dir/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcp_server.dir/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/tcp/socket.cpp > CMakeFiles/tcp_server.dir/socket.cpp.i

CMakeFiles/tcp_server.dir/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcp_server.dir/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/tcp/socket.cpp -o CMakeFiles/tcp_server.dir/socket.cpp.s

# Object files for target tcp_server
tcp_server_OBJECTS = \
"CMakeFiles/tcp_server.dir/tcp_start.cpp.o" \
"CMakeFiles/tcp_server.dir/server.cpp.o" \
"CMakeFiles/tcp_server.dir/socket.cpp.o"

# External object files for target tcp_server
tcp_server_EXTERNAL_OBJECTS =

tcp_server: CMakeFiles/tcp_server.dir/tcp_start.cpp.o
tcp_server: CMakeFiles/tcp_server.dir/server.cpp.o
tcp_server: CMakeFiles/tcp_server.dir/socket.cpp.o
tcp_server: CMakeFiles/tcp_server.dir/build.make
tcp_server: CMakeFiles/tcp_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/tcp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tcp_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcp_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcp_server.dir/build: tcp_server

.PHONY : CMakeFiles/tcp_server.dir/build

CMakeFiles/tcp_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tcp_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tcp_server.dir/clean

CMakeFiles/tcp_server.dir/depend:
	cd /mnt/d/tcp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/tcp /mnt/d/tcp /mnt/d/tcp/build /mnt/d/tcp/build /mnt/d/tcp/build/CMakeFiles/tcp_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcp_server.dir/depend

