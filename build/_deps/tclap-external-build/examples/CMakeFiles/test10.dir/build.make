# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tesscat/tracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tesscat/tracer/build

# Include any dependencies generated for this target.
include _deps/tclap-external-build/examples/CMakeFiles/test10.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/tclap-external-build/examples/CMakeFiles/test10.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/tclap-external-build/examples/CMakeFiles/test10.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/tclap-external-build/examples/CMakeFiles/test10.dir/flags.make

_deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o: _deps/tclap-external-build/examples/CMakeFiles/test10.dir/flags.make
_deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o: _deps/tclap-external-src/examples/test10.cpp
_deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o: _deps/tclap-external-build/examples/CMakeFiles/test10.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o"
	cd /home/tesscat/tracer/build/_deps/tclap-external-build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o -MF CMakeFiles/test10.dir/test10.cpp.o.d -o CMakeFiles/test10.dir/test10.cpp.o -c /home/tesscat/tracer/build/_deps/tclap-external-src/examples/test10.cpp

_deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test10.dir/test10.cpp.i"
	cd /home/tesscat/tracer/build/_deps/tclap-external-build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/build/_deps/tclap-external-src/examples/test10.cpp > CMakeFiles/test10.dir/test10.cpp.i

_deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test10.dir/test10.cpp.s"
	cd /home/tesscat/tracer/build/_deps/tclap-external-build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/build/_deps/tclap-external-src/examples/test10.cpp -o CMakeFiles/test10.dir/test10.cpp.s

# Object files for target test10
test10_OBJECTS = \
"CMakeFiles/test10.dir/test10.cpp.o"

# External object files for target test10
test10_EXTERNAL_OBJECTS =

_deps/tclap-external-build/examples/test10: _deps/tclap-external-build/examples/CMakeFiles/test10.dir/test10.cpp.o
_deps/tclap-external-build/examples/test10: _deps/tclap-external-build/examples/CMakeFiles/test10.dir/build.make
_deps/tclap-external-build/examples/test10: _deps/tclap-external-build/examples/CMakeFiles/test10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test10"
	cd /home/tesscat/tracer/build/_deps/tclap-external-build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/tclap-external-build/examples/CMakeFiles/test10.dir/build: _deps/tclap-external-build/examples/test10
.PHONY : _deps/tclap-external-build/examples/CMakeFiles/test10.dir/build

_deps/tclap-external-build/examples/CMakeFiles/test10.dir/clean:
	cd /home/tesscat/tracer/build/_deps/tclap-external-build/examples && $(CMAKE_COMMAND) -P CMakeFiles/test10.dir/cmake_clean.cmake
.PHONY : _deps/tclap-external-build/examples/CMakeFiles/test10.dir/clean

_deps/tclap-external-build/examples/CMakeFiles/test10.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/build/_deps/tclap-external-src/examples /home/tesscat/tracer/build /home/tesscat/tracer/build/_deps/tclap-external-build/examples /home/tesscat/tracer/build/_deps/tclap-external-build/examples/CMakeFiles/test10.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/tclap-external-build/examples/CMakeFiles/test10.dir/depend

