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
CMAKE_SOURCE_DIR = /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug

# Include any dependencies generated for this target.
include server/CMakeFiles/quoridor_server.dir/depend.make

# Include the progress variables for this target.
include server/CMakeFiles/quoridor_server.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/quoridor_server.dir/flags.make

server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.o: server/CMakeFiles/quoridor_server.dir/flags.make
server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.o: ../server/PasswordEncrypter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.o"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/quoridor_server.dir/PasswordEncrypter.o -c /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/server/PasswordEncrypter.cpp

server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quoridor_server.dir/PasswordEncrypter.i"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/server/PasswordEncrypter.cpp > CMakeFiles/quoridor_server.dir/PasswordEncrypter.i

server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quoridor_server.dir/PasswordEncrypter.s"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/server/PasswordEncrypter.cpp -o CMakeFiles/quoridor_server.dir/PasswordEncrypter.s

# Object files for target quoridor_server
quoridor_server_OBJECTS = \
"CMakeFiles/quoridor_server.dir/PasswordEncrypter.o"

# External object files for target quoridor_server
quoridor_server_EXTERNAL_OBJECTS =

server/libquoridor_server.a: server/CMakeFiles/quoridor_server.dir/PasswordEncrypter.o
server/libquoridor_server.a: server/CMakeFiles/quoridor_server.dir/build.make
server/libquoridor_server.a: server/CMakeFiles/quoridor_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libquoridor_server.a"
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && $(CMAKE_COMMAND) -P CMakeFiles/quoridor_server.dir/cmake_clean_target.cmake
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quoridor_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/quoridor_server.dir/build: server/libquoridor_server.a

.PHONY : server/CMakeFiles/quoridor_server.dir/build

server/CMakeFiles/quoridor_server.dir/clean:
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server && $(CMAKE_COMMAND) -P CMakeFiles/quoridor_server.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/quoridor_server.dir/clean

server/CMakeFiles/quoridor_server.dir/depend:
	cd /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/server /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server /mnt/c/Users/louis/Documents/uni/repos/202122_INFOF209_5/src/cmake-build-debug/server/CMakeFiles/quoridor_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/CMakeFiles/quoridor_server.dir/depend
