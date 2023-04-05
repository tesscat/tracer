# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/tesscat/tracer/build/_deps/tclap-external-src"
  "/home/tesscat/tracer/build/_deps/tclap-external-build"
  "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix"
  "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/tmp"
  "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/src/tclap-external-populate-stamp"
  "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/src"
  "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/src/tclap-external-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/src/tclap-external-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/tesscat/tracer/build/_deps/tclap-external-subbuild/tclap-external-populate-prefix/src/tclap-external-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
