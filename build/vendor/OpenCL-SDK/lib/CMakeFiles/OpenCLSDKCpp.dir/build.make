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
include vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/flags.make

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/flags.make
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/CLI.cpp
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o -MF CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o.d -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/CLI.cpp

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/CLI.cpp > CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.i

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/CLI.cpp -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.s

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/flags.make
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/Image.cpp
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o -MF CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o.d -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/Image.cpp

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/Image.cpp > CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.i

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/Image.cpp -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.s

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/flags.make
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropContext.cpp
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o -MF CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o.d -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropContext.cpp

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropContext.cpp > CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.i

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropContext.cpp -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.s

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/flags.make
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o: /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropWindow.cpp
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o -MF CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o.d -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o -c /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropWindow.cpp

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.i"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropWindow.cpp > CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.i

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.s"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tesscat/tracer/vendor/OpenCL-SDK/lib/src/SDK/InteropWindow.cpp -o CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.s

# Object files for target OpenCLSDKCpp
OpenCLSDKCpp_OBJECTS = \
"CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o" \
"CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o" \
"CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o" \
"CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o"

# External object files for target OpenCLSDKCpp
OpenCLSDKCpp_EXTERNAL_OBJECTS =

vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/CLI.cpp.o
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/Image.cpp.o
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropContext.cpp.o
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/src/SDK/InteropWindow.cpp.o
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/build.make
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libOpenCLUtilsCppd.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libGL.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libglewd.a
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libGLU.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libsfml-graphics-d.so.2.5.1
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libOpenCLUtilsd.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libOpenCL.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libXext.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libX11.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: /usr/lib/libGL.so
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libsfml-window-d.so.2.5.1
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/libsfml-system-d.so.2.5.1
vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so: vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tesscat/tracer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libOpenCLSDKCpp.so"
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenCLSDKCpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/build: vendor/OpenCL-SDK/lib/libOpenCLSDKCpp.so
.PHONY : vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/build

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/clean:
	cd /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib && $(CMAKE_COMMAND) -P CMakeFiles/OpenCLSDKCpp.dir/cmake_clean.cmake
.PHONY : vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/clean

vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/depend:
	cd /home/tesscat/tracer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tesscat/tracer /home/tesscat/tracer/vendor/OpenCL-SDK/lib /home/tesscat/tracer/build /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib /home/tesscat/tracer/build/vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : vendor/OpenCL-SDK/lib/CMakeFiles/OpenCLSDKCpp.dir/depend
