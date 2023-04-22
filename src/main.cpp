// #pragma OPENCL EXTENSION cl_khr_spir : enable
// #pragma OPENCL EXTENSION cl_khr_il_program : enable
// #define CL_HPP_ENABLE_EXCEPTIONS
// #define CL_HPP_USE_IL_KHR
// #define CL_HPP_TARGET_OPENCL_VERSION 300

// #include <CL/opencl.hpp>
// #include <CL/cl.h>

#include <trace.hpp>
#include <argparse/argparse.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

int imageColourDepth = 1024;
int workGroupSize = 1;

int WriteImage(std::string filename, std::vector<RGB> data, size_t width, size_t height) {
  std::ofstream file (filename, std::ios::binary);

  file << "P3\n" << width << ' ' << height << '\n' << imageColourDepth << '\n';
  for (int i = height - 1; i >= 0; i--) {
    for (int j = 0; j < width; j++) {
      int idx = (i*width + j);
      // double r = data[idx];
      // double g = data[idx + 1];
      // double b = data[idx + 2];
      // double alpha = data[idx + 4];
      // data is 0 to 1 range
      int rval = std::round(data[idx].r * imageColourDepth);
      int gval = std::round(data[idx].g * imageColourDepth);
      int bval = std::round(data[idx].b * imageColourDepth);
      // int alphaval = std::round(alpha * imageColourDepth);
      file << rval << ' ' << gval <<  ' ' << bval << '\n';
    }
  }

  file.close();

  return 0;
}


int main(int argc, char** argv) {
  argparse::ArgumentParser parser("tracer");
  parser.add_argument("-o", "--output")
    .default_value(std::string("out.ppm"))
    .required()
    .help("specify the output file.");
  parser.add_argument("-w", "--width")
    .default_value(std::string("800"))
    .required()
    .help("specify the width.");
  parser.add_argument("-h", "--height")
    .default_value(std::string("600"))
    .required()
    .help("specify the height.");
  parser.add_argument("-b", "--bounces")
    .default_value(std::string("4"))
    .required()
    .help("specify the number of bounces.");
  parser.add_argument("-s", "--subrays")
    .default_value(std::string("5"))
    .required()
    .help("specify the number of sub-rays per bounce.");

  parser.parse_args(argc, argv);

  int width = std::stoi(parser.get<std::string>("--width"));
  int height = std::stoi(parser.get<std::string>("--height"));
  int subRays = std::stoi(parser.get<std::string>("--subrays"));
  int bounces = std::stoi(parser.get<std::string>("--bounces"));

  std::vector<RGB> image (width * height);
  std::cout << "Image is " << sizeof(RGB) * width * height << " bytes big, with " << sizeof(RGB) << " bytes per pixel\n";
  
  int sphCount = 1;
  // std::vector<std::vector<double>> sphCenters = {{3.0, 0.0, 10.0}, {-3.0, 0.0, 10.0}, {0.0, 1.0, 10.0}, {0.0, -401.0, 10}, {-3.0, 3.0, 6.0}};
  // std::vector<int> sphMatIndexes = {1, 2, 3, 4, 5};
  // std::vector<double> sphCentersFlat;// (sphCenters.size() * 3, 0);
  // for (auto sphCenter : sphCenters) {
    // for (double coord: sphCenter) {
      // sphCentersFlat.push_back(coord);
    // }
    // sphCentersFlat.insert(sphCentersFlat.end(), sphCenter.begin(), sphCenter.end());
  // }
  // std::cout << "Length of sphere centers flattened: " << sphCentersFlat.size() << "\n";
  // std::vector<double> sphRadii = {1.0, 1.0, 1.5, 400, 3};
  std::vector<Sphere> spheres;
  spheres.push_back(Sphere({0.0, 1.0, 10.0}, 1.5, 3));
  spheres.push_back(Sphere({3.0, 0.0, 10.0}, 1, 2));
  
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

  std::vector<Material> materials = {air, m1, m2, m3, m4, m5};

  cl::sycl::context ctx;
  std::cout << "Available devices:\n";
  for (auto dev : ctx.get_devices()) {
    std::cout << '\t' << dev.get_info<cl::sycl::info::device::name>() << '\n';
  }

  cl::sycl::default_selector device_selector;

  cl::sycl::queue queue(device_selector);
  std::cout << "Running on "
             << queue.get_device().get_info<cl::sycl::info::device::name>()
             << "\n";

  {
      
      cl::sycl::buffer<RGB, 1> img_sycl(image.data(), cl::sycl::range<1>(width * height));
      cl::sycl::buffer<Material, 1> mats_sycl(materials.data(), cl::sycl::range<1>{materials.size()});
      // cl::sycl::buffer<int, 1> matidx_sycl(sphMatIndexes.data(), cl::sycl::range<1>{sphMatIndexes.size()});
      // cl::sycl::buffer<double, 1> sph_centers_sycl(sphCentersFlat.data(), cl::sycl::range<1>{sphCentersFlat.size()});
      // cl::sycl::buffer<double, 1> sph_;radii_sycl(sphRadii.data(), cl::sycl::range<1>{sphRadii.size()});
      cl::sycl::buffer<Sphere, 1> sph_sycl(spheres.data(), cl::sycl::range<1>{spheres.size()});
      queue.submit([&] (cl::sycl::handler& cgh) {
        auto img = img_sycl.get_access<cl::sycl::access::mode::discard_write>(cgh);
        auto mats = mats_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        // auto matsidx = matidx_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        // auto centers = sph_centers_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        // auto radii = sph_radii_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        auto spheres = sph_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        cgh.parallel_for(cl::sycl::range<1>(width * height), [=](cl::sycl::id<1> pos){
          int x = pos.get(0) % width;
          int y = floor(pos.get(0) / width);
          img[pos.get(0)].r = x/(double)width;
          trace(width, height, bounces, subRays, spheres.size(), spheres, mats, img, x, y);
          // c_acc[id] = t_acc[id].b;
        });
      });
   }

  std::cout << "Finished executing\n";

  WriteImage(parser.get<std::string>("--output"), image, width, height);

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
