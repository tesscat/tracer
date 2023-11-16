cmake_minimum_required(VERSION 3.10)
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

project(tracer VERSION 0.0)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/vendor/AdaptiveCpp/build/)
# set(AdaptiveCpp_DIR vendor/AdaptiveCpp/build)

set(SOURCE_FILES src/main.cpp)

# add_subdirectory("vendor/AdaptiveCpp")
find_package(AdaptiveCpp REQUIRED)
add_subdirectory("vendor/argparse")

add_executable(tracer ${SOURCE_FILES})

add_sycl_to_target(TARGET tracer)
file(GLOB_RECURSE sources src/*.cpp)
target_sources(tracer PRIVATE ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC "src/" "vendor/argparse/include" "vendor/OpenSYCL/include" "include/" "vendor/OpenCL-SDK/lib/include" "vendor/OpenCL-SDK/include/cpp" "vendor") # "wild/include" "wild/src/include") # hack to make assimp work
# target_link_libraries(tracer OpenCL::OpenCL)
# target_link_libraries(tame wild) # bgfx bx bimg glfw)
