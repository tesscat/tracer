#include <trace.hpp>
#include <argparse/argparse.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

int imageColourDepth = 1024;
int workGroupSize = 1;

int WriteImage(std::string filename, std::vector<double> r, std::vector<double> g, std::vector<double> b, size_t width, size_t height) {
  std::ofstream file (filename, std::ios::binary);

  file << "P3\n" << width << ' ' << height << '\n' << imageColourDepth << '\n';
  for (int i = height - 1; i >= 0; i--) {
    for (int j = 0; j < width; j++) {
      int idx = (i*width + j);

      // std::cout << "poly ";
      // for (auto coeff : data[idx].poly.coefficients)
        // std::cout << coeff << ' ';
      // std::cout << '\n';
      // double r = data[idx];
      // double g = data[idx + 1];
      // double b = data[idx + 2];
      // double alpha = data[idx + 4];
      // data is 0 to 1 range
      int rval = std::round(r[idx] * imageColourDepth);
      int gval = std::round(g[idx] * imageColourDepth);
      int bval = std::round(b[idx] * imageColourDepth);
      if ((rval > imageColourDepth) || (gval > imageColourDepth) || (bval > imageColourDepth))
        std::cout << "Warning: violation of imageColourDepth by " << (rval - imageColourDepth) << '/' << (gval - imageColourDepth) << '/' << (bval - imageColourDepth) << '\n';
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

  std::cout << "Dimensions: " << width << "x" << height << "; " << subRays << " subrays and " << bounces << " bounces.\n";

  std::vector<double> r (width * height);
  std::vector<double> g (width * height);
  std::vector<double> b (width * height);
  std::cout << "Image is " << sizeof(double) * width * height *3 << " bytes big, with " << sizeof(double) * 3 << " effective bytes per pixel, maybe\n";
  
  int sphCount = 0;

  std::vector<Sphere> spheres;
  spheres.push_back(Sphere({0.0, 1.0, 10.0}, 1.5, 1));
  spheres.push_back(Sphere({3.0, 0.0, 10.0}, 1, 1));
  spheres.push_back(Sphere({0.0, -101.0, 0.0}, 100, 2));
  
  Material air; // only care abt refInd but makes it easier
  Material m1;
  m1.reflection = 0.0;
  m1.albedo = Colour(std::vector<double>({1.0, 0.0}));
  m1.emission = Colour(std::vector<double>({0.5, 0.5, 0.0}));
  Material m2;
  m2.reflection = 0.0;
  m2.albedo = Colour(std::vector<double>({1.0, 1.0}));
  m2.emission = Colour(std::vector<double>({0.0, 0.0, 0.0}));
  // Material m3;
  // Material m4;
  // Material m5;
  // m1.albedo.r = 1.0;
  // m1.albedo.g = 1.0;
  // m1.albedo.b = 1.0;
  // m2.albedo.g = 1.0;
  // m3.albedo.r = 1.0;
  // m3.albedo.g = 1.0;
  // m3.albedo.b = 1.0;
  // m3.emission.r = 3.0;
  // m3.emission.g = 3.0;
  // m3.emission.b = 3.0;
  // m4.albedo.r = 1.0;
  // m4.albedo.g = 1.0;
  // m4.albedo.b = 1.0;
  // m4.emission.r = 0.0;
  // m4.emission.g = 1.0;
  // m4.emission.b = 1.0;
  // m4.reflection = 0.0;
  // m5.translucency = 1.0;
  // m5.reflection = 0.0;
  // m5.albedo.r = 1.0;
  // m5.albedo.g = 1.0;
  // m5.albedo.b = 1.0;
  // m5.refIndex = 1.0;

  std::vector<Material> materials = {air, m1, m2}; // , m1, m2, m3, m4, m5};

  // exit(1);
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
    cl::sycl::buffer<double, 1> rimg_sycl(r.data(), cl::sycl::range<1>(width * height));
    cl::sycl::buffer<double, 1> gimg_sycl(g.data(), cl::sycl::range<1>(width * height));
    cl::sycl::buffer<double, 1> bimg_sycl(b.data(), cl::sycl::range<1>(width * height));
    cl::sycl::buffer<Material, 1> mats_sycl(materials.data(), cl::sycl::range<1>{materials.size()});
    // cl::sycl::buffer<int, 1> matidx_sycl(sphMatIndexes.data(), cl::sycl::range<1>{sphMatIndexes.size()});
    // cl::sycl::buffer<double, 1> sph_centers_sycl(sphCentersFlat.data(), cl::sycl::range<1>{sphCentersFlat.size()});
    // cl::sycl::buffer<double, 1> sph_;radii_sycl(sphRadii.data(), cl::sycl::range<1>{sphRadii.size()});
    cl::sycl::buffer<Sphere, 1> sph_sycl(spheres.data(), cl::sycl::range<1>{spheres.size()});

    std::vector<double> wavelengths {nmToVisiRange(630), nmToVisiRange(532), nmToVisiRange(467)};
    std::vector<cl::sycl::buffer<double, 1>> ibuffers {rimg_sycl, gimg_sycl, bimg_sycl};

    for (int i = 0; i < wavelengths.size(); i++) {
      auto ibuffer = ibuffers[i];
      queue.submit([&] (cl::sycl::handler& cgh) {
        auto mats = mats_sycl.get_access<cl::sycl::access::mode::read>(cgh);
        auto spheres = sph_sycl.get_access<cl::sycl::access::mode::read>(cgh);

        // TODO: Deduplicate
        // R=630nm, G=532nm, and B=467nm
        auto img = ibuffer.get_access<cl::sycl::access::mode::discard_write>(cgh);
        cgh.parallel_for(cl::sycl::range<1>(width * height), [=](cl::sycl::id<1> pos){
          int x = pos.get(0) % width;
          int y = floor(pos.get(0) / width);

          // call the damn thing
          trace(width, height, bounces, subRays, spheres.size(), spheres, mats, img, x, y, wavelengths[i]);
        });
      });
    }
  }

  std::cout << "Finished executing\n";

  WriteImage(parser.get<std::string>("--output"), r, g, b, width, height);
  return 0;
}
