cmake_minimum_required(VERSION 3.10)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project(tracer VERSION 0.0)

set(SOURCE_FILES src/main.cpp)

find_package(OpenCL REQUIRED)
add_subdirectory("vendor/OpenSYCL")
find_package(OpenSYCL REQUIRED)
add_subdirectory("vendor/argparse")
# find_package(wild REQUIRED) TODO: make work
add_executable(tracer ${SOURCE_FILES})

add_sycl_to_target(TARGET tracer)
file(GLOB_RECURSE sources src/*.cpp)
target_sources(tracer PRIVATE ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC "src/" "vendor/argparse/include" "vendor/OpenSYCL/include" "include/" "vendor/OpenCL-SDK/lib/include" "vendor/OpenCL-SDK/include/cpp" "vendor") # "wild/include" "wild/src/include") # hack to make assimp work
# target_link_libraries(tracer OpenCL::OpenCL)
# target_link_libraries(tame wild) # bgfx bx bimg glfw)
