# Install script for directory: /home/tesscat/tracer/vendor/OpenCL-SDK

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/tesscat/tracer/vendor/OpenCL-SDK/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenCL" TYPE FILE FILES "/home/tesscat/tracer/build/vendor/OpenCL-SDK/OpenCL/OpenCLConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/OpenCL" TYPE FILE FILES "/home/tesscat/tracer/build/vendor/OpenCL-SDK/OpenCL/OpenCLConfigVersion.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-Headers/cmake_install.cmake")
  include("/home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-ICD-Loader/cmake_install.cmake")
  include("/home/tesscat/tracer/build/vendor/OpenCL-SDK/external/OpenCL-CLHPP/cmake_install.cmake")
  include("/home/tesscat/tracer/build/_deps/cargs-external-build/cmake_install.cmake")
  include("/home/tesscat/tracer/build/_deps/tclap-external-build/cmake_install.cmake")
  include("/home/tesscat/tracer/build/_deps/glm-external-build/cmake_install.cmake")
  include("/home/tesscat/tracer/build/_deps/glew-external-build/cmake_install.cmake")
  include("/home/tesscat/tracer/build/_deps/sfml-external-build/cmake_install.cmake")
  include("/home/tesscat/tracer/build/vendor/OpenCL-SDK/lib/cmake_install.cmake")
  include("/home/tesscat/tracer/build/vendor/OpenCL-SDK/samples/cmake_install.cmake")

endif()

