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
include vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/flags.make

vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o: vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/flags.make
vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o: /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/enumopencl/main.c
vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o: vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o -MF CMakeFiles/enumopencl.dir/main.c.o.d -o CMakeFiles/enumopencl.dir/main.c.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/enumopencl/main.c

vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/enumopencl.dir/main.c.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/enumopencl/main.c > CMakeFiles/enumopencl.dir/main.c.i

vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/enumopencl.dir/main.c.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/enumopencl/main.c -o CMakeFiles/enumopencl.dir/main.c.s

# Object files for target enumopencl
enumopencl_OBJECTS = \
"CMakeFiles/enumopencl.dir/main.c.o"

# External object files for target enumopencl
enumopencl_EXTERNAL_OBJECTS =

vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/main.c.o
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/build.make
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libOpenCLSDK.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so
vendor/OpenCL-SDK/bin/enumopencl: _deps/cargs-external-build/libcargs.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libOpenCLUtilsCppd.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libOpenCLUtilsd.so
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libglewd.a
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libXext.so
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libX11.so
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libGLU.so
vendor/OpenCL-SDK/bin/enumopencl: /usr/lib/libGL.so
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libsfml-graphics-d.so.2.5.1
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libsfml-window-d.so.2.5.1
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/lib/libsfml-system-d.so.2.5.1
vendor/OpenCL-SDK/bin/enumopencl: vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../../../bin/enumopencl"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/enumopencl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/build: vendor/OpenCL-SDK/bin/enumopencl
.PHONY : vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/build

vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl && $(CMAKE_COMMAND) -P CMakeFiles/enumopencl.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/clean

vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/enumopencl /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/samples/core/enumopencl/CMakeFiles/enumopencl.dir/depend

