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
include vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/flags.make

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/flags.make
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample.cpp
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o -MF CMakeFiles/headerexample.dir/headerexample.cpp.o.d -o CMakeFiles/headerexample.dir/headerexample.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample.cpp

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/headerexample.dir/headerexample.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample.cpp > CMakeFiles/headerexample.dir/headerexample.cpp.i

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/headerexample.dir/headerexample.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample.cpp -o CMakeFiles/headerexample.dir/headerexample.cpp.s

# Object files for target headerexample
headerexample_OBJECTS = \
"CMakeFiles/headerexample.dir/headerexample.cpp.o"

# External object files for target headerexample
headerexample_EXTERNAL_OBJECTS =

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/headerexample.cpp.o
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/build.make
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample: vendor/OpenCL-SDK/external/OpenCL-ICD-Loader/libOpenCL.so.1.2
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable headerexample"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/headerexample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/build: vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/headerexample
.PHONY : vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/build

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src && $(CMAKE_COMMAND) -P CMakeFiles/headerexample.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/clean

vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src /home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/external/OpenCL-CLHPP/examples/src/CMakeFiles/headerexample.dir/depend

