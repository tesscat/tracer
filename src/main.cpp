#pragma OPENCL EXTENSION cl_khr_spir : enable
#pragma OPENCL EXTENSION cl_khr_il_program : enable
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_USE_IL_KHR
#define CL_HPP_TARGET_OPENCL_VERSION 300

#include <CL/opencl.hpp>
#include <CL/cl.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

int imageColourDepth = 1024;
int workGroupSize = 1;

int WriteImage(std::string filename, std::vector<double> data, size_t width, size_t height) {
  std::ofstream file (filename, std::ios::binary);

  file << "P3\n" << width << ' ' << height << '\n' << imageColourDepth << '\n';
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int idx = (i*width + j) * 4;
      double r = data[idx];
      double g = data[idx + 1];
      double b = data[idx + 2];
      double alpha = data[idx + 3];
      // data is 0 to 1 range
      int rval = std::round(r * imageColourDepth);
      int gval = std::round(g * imageColourDepth);
      int bval = std::round(b * imageColourDepth);
      int alphaval = std::round(alpha * imageColourDepth);
      file << rval << ' ' << gval <<  ' ' << bval << '\n';
    }
  }

  file.close();

  return 0;
}

class RGB {
public:
  double r = 0.0;
  double g = 0.0;
  double b = 0.0;
  std::vector<double> Flatten() {
    return {r, g, b};
  }
};

class Material {
public:
  RGB albedo;
  RGB emission;
  double reflection = 0.0;
  double translucency = 0.0;
  double refIndex = 1.0;
  std::vector<double> Flatten() {
    std::vector<double> out = albedo.Flatten();
    std::vector<double> tmp = emission.Flatten();
    out.insert(out.end(), tmp.begin(), tmp.end());
    out.push_back(reflection);
    out.push_back(translucency);
    out.push_back(refIndex);
    return out;
  }
};

int main() {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);
  // cl::Context ctx = cl::sdk::get_context(cl::sdk::options::DeviceTriplet);
  //
  if (platforms.size() == 0) {
    std::cerr << "Failed to find platforms" << std::endl;
    std::exit(1);
  }

  std::cout << "Available platforms:\n";
  for (auto platform : platforms) {
    std::cout << "\t" << platform.getInfo<CL_PLATFORM_NAME>() << "\n";
  }
  cl::Platform platform = platforms[0];
  std::cout << "Using platform " << platform.getInfo<CL_PLATFORM_NAME>() << "\n";

  cl::Platform newP = cl::Platform::setDefault(platform);
  if (newP != platform) {
    std::cerr << "Error setting default platform" << std::endl;
    std::exit(1);
  }

  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL ,&devices);
  if (devices.size() == 0) {
    std::cerr << "Failed to find devices" << std::endl;
    std::exit(0);
  }

  std::cout << "Available devices:\n";
  for (auto device : devices) {
    std::cout << "\t" << device.getInfo<CL_DEVICE_NAME>() << "\n";
  }

  cl::Device device = devices.back();
  // device.
  std::cout << "Using device " << device.getInfo<CL_DEVICE_NAME>() << "\n";
  cl::Context context {device}; // enables communication
  // cl::CommandQueue queue {context, device};
  //
  std::ifstream file ("kernel/trace.c", std::ios::binary);
  std::string spirvData;
  std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(spirvData));
  std::cout << "Read " << spirvData.size() << " bytes\n";
  std::vector<std::string> programStrings;
  programStrings.push_back(spirvData);
  // cl_program program_ = clCreateProgramWithIL(context.get(), spirvData.data(), spirvData.size(), nullptr);
  cl_int err = 0;
  cl::Program program (programStrings);
  if (err != 0) {
    std::cerr << "Error constructing program: " << err << std::endl;
    std::exit(err);
  }

  _cl_device_id* const* c = &device();
  // program.build(device);
  err = clBuildProgram(program.get(), 1, (c), "", nullptr, nullptr);
  char buffer[2048];
  size_t length;
  clGetProgramBuildInfo(program.get(), *c, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &length);
  std::cout << "Build log, code " << err << '\n' << buffer << '\n';
  
  // program.getBuildInfo()
  program.build(device, "");

  // int n = 10;
  
  // std::vector<int> a {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::vector<int> b {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  // std::vector<int> output (n, 0);

  // cl_mem_flags flags = CL_MEM_READ_WRITE;

  int width = 512;
  int height = 512;

  std::vector<double> image (width * height * 4, 1.0);
  std::cout << "Image is " << sizeof(double) * width * height * 4 << " bytes big, with 4x" << sizeof(double) << " bytes per pixel\n";
  
  int sphCount = 5;
  std::vector<std::vector<double>> sphCenters = {{3.0, 0.0, 10.0}, {-3.0, 0.0, 10.0}, {0.0, 1.0, 10.0}, {0.0, -401.0, 10}, {-3.0, 3.0, 6.0}};
  std::vector<int> sphMatIndexes = {1, 2, 3, 4, 5};
  std::vector<cl_double> sphCentersFlat;// (sphCenters.size() * 3, 0);
  for (auto sphCenter : sphCenters) {
    for (double coord: sphCenter) {
      sphCentersFlat.push_back(coord);
    }
    // sphCentersFlat.insert(sphCentersFlat.end(), sphCenter.begin(), sphCenter.end());
  }
  std::cout << "Length of sphere centers flattened: " << sphCentersFlat.size() << "\n";
  std::vector<cl_double> sphRadii = {1.0, 1.0, 1.5, 400, 3};
  
  Material air; // only care abt refInd but makes it easier
  Material m1;
  Material m2;
  Material m3;
  Material m4;
  Material m5;
  m1.albedo.r = 1.0;
  m1.albedo.g = 1.0;
  m1.albedo.b = 1.0;
  m2.albedo.g = 1.0;
  m3.albedo.r = 1.0;
  m3.albedo.g = 1.0;
  m3.albedo.b = 1.0;
  m3.emission.r = 3.0;
  m3.emission.g = 3.0;
  m3.emission.b = 3.0;
  m4.albedo.r = 1.0;
  m4.albedo.g = 1.0;
  m4.albedo.b = 1.0;
  m4.emission.r = 0.0;
  m4.emission.g = 1.0;
  m4.emission.b = 1.0;
  m4.reflection = 0.0;
  m5.translucency = 1.0;
  m5.reflection = 0.0;
  m5.albedo.r = 1.0;
  m5.albedo.g = 1.0;
  m5.albedo.b = 1.0;
  m5.refIndex = 1.0;
  // m4.reflection.g = 1.0;
  // m4.reflection.b = 1.0;
  // m3.emission.g = 1.0;
  // m3.emission.b = 1.0;
  
  std::vector<Material> materials = {air, m1, m2, m3, m4, m5};
  std::vector<double> materialsFlat;
  for (auto material: materials) {
    std::vector<double> flat = material.Flatten();
    materialsFlat.insert(materialsFlat.end(), flat.begin(), flat.end());
  }
  std::cout << "Length of materials flattened: " << materialsFlat.size() << "\n";

  // for (int x : output) {
    // std::cout << x << " ";
  // }
  // std::cout << "\n";
  // cl::Buffer outputBuffer {begin(output), end(output), false};
  // cl::Buffer aBuffer {begin(a), end(a), true};
  // cl::Buffer bBuffer {begin(b), end(b), true};
  cl::Buffer sphCentersBuffer (std::begin(sphCentersFlat), std::end(sphCentersFlat), true);
  cl::Buffer sphRadiiBuffer (std::begin(sphRadii), std::end(sphRadii), true);
  cl::Buffer matBuffer (std::begin(materialsFlat), std::end(materialsFlat), true);
  cl::Buffer matIndexes (std::begin(sphMatIndexes), std::end(sphMatIndexes), true);
  cl::Buffer output (std::begin(image), std::end(image), false);
  cl_int w_int = width;
  cl_int h_int = height;

  cl::DeviceCommandQueue deviceCommandQueue = cl::DeviceCommandQueue::makeDefault(context, device);
  std::cout << "Buffers and queues initialized" << std::endl;
  err = 0;
  cl::Kernel kernel (program, "trace", &err);
  if (err != 0) {
    std::cerr << "Error constructing kernel: " << err << std::endl;
    std::exit(err);
  }
  std::cout << "Kernel constructed\n";
  // cl::KernelFunctor<> kFunctor (program, "trace");
  cl::KernelFunctor<cl_int, cl_int, cl_int, cl::Buffer, cl::Buffer, cl::Buffer, cl::Buffer, cl::Buffer> kFunctor {program, "trace"};
  cl_int error;
  std::cout << "Starting execution\n";
  kFunctor(cl::EnqueueArgs(cl::NDRange(width * height)), width, height, sphCount, sphCentersBuffer, sphRadiiBuffer, matBuffer, matIndexes, output, error);

  std::cout << "Done starting executing\n";

  cl::copy(output, begin(image), end(image));

  std::cout << "Done copying\n";

  WriteImage("out.ppm", image, width, height);

  // stbi_write_png("out.png", width, height, 0, image.data(), sizeof(float) * 4);
  // program.build(device);
  // // cl::Kernel kernel {program, "vadd"};
  //
  //
  // int n = 10;
  //
  //
  // // cl::Buffer bufferC {context, CL_MEM_READ_WRITE, sizeof(int) * n};
  //
  // std::valarray<cl_int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  // std::valarray<cl_int> b = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::valarray<cl_int> c = {0, 2, 0, 2, 0, 2, 0, 2, 0, 2};
  // cl::Buffer bufferA {context, std::begin(a), std::end(a), true};
  // cl::Buffer bufferB {context, std::begin(b), std::end(b), true};
  // cl::Buffer bufferC {context, std::begin(c), std::end(c), false};
  //
  // cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::Buffer> functor {program, "vadd"};
  // // cl::KernelFunctor<cl::Buffer, cl::Buffer, cl::Buffer> functor {kernel, bufferA, bufferB, bufferC};
  // cl::EnqueueArgs args {queue, cl::NDRange(10)};
  // functor(args, bufferA, bufferB, bufferC);
  //
  // cl::copy(queue, bufferC, std::begin(c), std::end(c));
  // // queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, sizeof(int) * n, c);
  //
  // for (int x : output) {
    // std::cout << x << " ";
  // }
  // std::cout << "\n";

  return 0;
}
