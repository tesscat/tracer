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

# Utility rule file for binaries-device-code.

# Include any custom commands dependencies for this target.
include vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/progress.make

vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code: vendor/OpenCL-SDK/bin/Collatz.cl

vendor/OpenCL-SDK/bin/Collatz.cl: /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/binaries/Collatz.cl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying Collatz.cl"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/binaries && /usr/bin/cmake -E copy_if_different /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/binaries/Collatz.cl /home/tesscat/tracer/build/vendor/OpenCL-SDK/bin/Collatz.cl

binaries-device-code: vendor/OpenCL-SDK/bin/Collatz.cl
binaries-device-code: vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code
binaries-device-code: vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/build.make
.PHONY : binaries-device-code

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/build: binaries-device-code
.PHONY : vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/build

vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/binaries && $(CMAKE_COMMAND) -P CMakeFiles/binaries-device-code.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/clean

vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK/samples/core/binaries /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/binaries /home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/samples/core/binaries/CMakeFiles/binaries-device-code.dir/depend

