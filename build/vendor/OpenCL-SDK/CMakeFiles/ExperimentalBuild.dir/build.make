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

# Utility rule file for ExperimentalBuild.

# Include any custom commands dependencies for this target.
include vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/progress.make

vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK && /usr/bin/ctest -D ExperimentalBuild

ExperimentalBuild: vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild
ExperimentalBuild: vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/build.make
.PHONY : ExperimentalBuild

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/build: ExperimentalBuild
.PHONY : vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/build

vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalBuild.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/clean

vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK /home/tesscat/tracer/build/vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/CMakeFiles/ExperimentalBuild.dir/depend

