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
include vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/flags.make

vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o: vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/flags.make
vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/reduce/main.cpp
vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o: vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o -MF CMakeFiles/reducecpp.dir/main.cpp.o.d -o CMakeFiles/reducecpp.dir/main.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/reduce/main.cpp

vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reducecpp.dir/main.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/reduce/main.cpp > CMakeFiles/reducecpp.dir/main.cpp.i

vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reducecpp.dir/main.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/reduce/main.cpp -o CMakeFiles/reducecpp.dir/main.cpp.s

# Object files for target reducecpp
reducecpp_OBJECTS = \
"CMakeFiles/reducecpp.dir/main.cpp.o"

# External object files for target reducecpp
reducecpp_EXTERNAL_OBJECTS =

vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/main.cpp.o
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/build.make
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libOpenCLSDK.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so
vendor/OpenCL-SDK/bin/reducecpp: _deps/cargs-external-build/libcargs.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libOpenCLUtilsCppd.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libOpenCLUtilsd.so
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libglewd.a
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libXext.so
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libX11.so
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libGLU.so
vendor/OpenCL-SDK/bin/reducecpp: /usr/lib/libGL.so
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libsfml-graphics-d.so.2.5.1
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libsfml-window-d.so.2.5.1
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/lib/libsfml-system-d.so.2.5.1
vendor/OpenCL-SDK/bin/reducecpp: vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/reducecpp"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reducecpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/build: vendor/OpenCL-SDK/bin/reducecpp
.PHONY : vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/build

vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce && $(CMAKE_COMMAND) -P CMakeFiles/reducecpp.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/clean

vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/reduce /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/samples/core/reduce/CMakeFiles/reducecpp.dir/depend
