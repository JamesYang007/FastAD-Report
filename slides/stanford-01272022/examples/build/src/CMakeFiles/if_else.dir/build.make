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
CMAKE_SOURCE_DIR = /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build

# Include any dependencies generated for this target.
include src/CMakeFiles/if_else.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/if_else.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/if_else.dir/flags.make

src/CMakeFiles/if_else.dir/if_else.cpp.o: src/CMakeFiles/if_else.dir/flags.make
src/CMakeFiles/if_else.dir/if_else.cpp.o: ../src/if_else.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/if_else.dir/if_else.cpp.o"
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/if_else.dir/if_else.cpp.o -c /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/src/if_else.cpp

src/CMakeFiles/if_else.dir/if_else.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/if_else.dir/if_else.cpp.i"
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/src/if_else.cpp > CMakeFiles/if_else.dir/if_else.cpp.i

src/CMakeFiles/if_else.dir/if_else.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/if_else.dir/if_else.cpp.s"
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/src/if_else.cpp -o CMakeFiles/if_else.dir/if_else.cpp.s

# Object files for target if_else
if_else_OBJECTS = \
"CMakeFiles/if_else.dir/if_else.cpp.o"

# External object files for target if_else
if_else_EXTERNAL_OBJECTS =

src/if_else: src/CMakeFiles/if_else.dir/if_else.cpp.o
src/if_else: src/CMakeFiles/if_else.dir/build.make
src/if_else: src/CMakeFiles/if_else.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable if_else"
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/if_else.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/if_else.dir/build: src/if_else

.PHONY : src/CMakeFiles/if_else.dir/build

src/CMakeFiles/if_else.dir/clean:
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src && $(CMAKE_COMMAND) -P CMakeFiles/if_else.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/if_else.dir/clean

src/CMakeFiles/if_else.dir/depend:
	cd /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/src /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src /home/jhyang/sandbox/stanford-phd-collection/2021-winter/dominik-group/stanford-01272022/examples/build/src/CMakeFiles/if_else.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/if_else.dir/depend
