# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.25.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(sfml-external-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[/usr/bin/git]==])
set(GIT_VERSION_STRING [==[2.39.2]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[/usr/bin/git;2.39.2]==]
)


include(ExternalProject)
ExternalProject_Add(sfml-external-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/SFML/SFML.git" "GIT_TAG" "2.5.1" "PATCH_COMMAND" "/usr/bin/cmake" "-E" "copy" "/home/tesscat/tracer/vendor/OpenCL-SDK/cmake/Dependencies/SFML/CMakeLists.txt" "/home/tesscat/tracer/build/vendor/OpenCL-SDK/_deps/sfml-external-src/src/SFML/Graphics/CMakeLists.txt"
                    SOURCE_DIR          "/home/tesscat/tracer/build/_deps/sfml-external-src"
                    BINARY_DIR          "/home/tesscat/tracer/build/_deps/sfml-external-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


