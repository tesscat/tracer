// #include "hipSYCL/sycl/libkernel/builtins.hpp"
#include "resources/material.hpp"
#include "resources/sphere.hpp"
#include <CL/sycl.hpp>


template<typename T>
using ClArr = cl::sycl::accessor<T, 1, cl::sycl::access::mode::read>;
// TODO: figure out how to get double3s across
void trace(
    const int width,
    const int height,
    const int maxDepth,
    const int subRays,
    int sphCount,
    ClArr<Sphere> spheres,
    ClArr<Material> materials,
    cl::sycl::accessor<double, 1, cl::sycl::access::mode::discard_write> image,
    int x,
    int y,
    double wavelength
);
// #endif
