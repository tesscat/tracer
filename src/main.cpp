#include "resources/colour.hpp"
#include "resources/common_mats.hpp"
#include <resources/image.hpp>
#include <resources/material.hpp>
#include <trace.hpp>
#include <argparse/argparse.hpp>

int workGroupSize = 1;

using namespace tracer::colour;

int main(int argc, char** argv) {
    argparse::ArgumentParser parser("tracer");
    parser.add_argument("-o", "--output")
        .default_value(std::string("out.png"))
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

    std::vector<Sphere> spheres = std::vector<Sphere>();
    // spheres.push_back(Sphere({0.0, 1.0, 10.0}, 1.5, 2));
    // spheres.push_back(Sphere({3.0, 0.0, 10.0}, 1, 2));
    // spheres.push_back(Sphere({0.0, -21.0, 0.0}, 20, 2));
    // spheres.push_back(Sphere({0.0, 0.0, 10.0}, 3.0, 2));
    // spheres.push_back(Sphere({0.0, 0.0, -15.0}, 1.0, 1));
    // spheres.push_back(Sphere({0.0, 0.0, 200.0}, 180.0, 3));
    spheres.push_back(Sphere({-5.0, 0.0, 20.0}, 3.0, 1));
    // spheres.push_back(Sphere({0.0, 2.1, 20.0}, 1.8, 4));
    // spheres.push_back(Sphere({0.0, -2.1, 20.0}, 1.8, 4));
    spheres.push_back(Sphere({200, 0.0, 20}, 194, 3));
    spheres.push_back(Sphere({3.0, 0.0, 20.0}, 2.0, 5));
    spheres.push_back(Sphere({3.0, 0.0, 20.0}, 1.0, 0));

    // sellmeier test
    // std::cout << "sell test " << BK7.Calculate(nmToVisiRange(630)) << "\n";

    Material air; // only care abt refInd but makes it easier
    air.refract = AIR; // TODO: update with actual value
    air.albedo = Colour({1.0, 1.0});
    air.emission = Colour({0.0, 0.0});
    air.translucency = 1.0;
    air.reflection = 0.0;
    Material m1;
    m1.reflection = 0.0;
    m1.albedo = Colour(std::vector<double>({1.0, 1.0}));
    m1.emission = Colour(std::vector<double>({2.0, 2.0, 2.0}));
    Material m2;
    m2.reflection = 0.0;
    m2.albedo = Colour(std::vector<double>({1.0, 1.0}));
    m2.emission = Colour(std::vector<double>({0.0, 0.0, 0.0}));
    m2.translucency = 1.0;
    m2.refract = BK7;
    Material m3;
    m3.reflection = 0.3;
    m3.albedo = Colour({0.8, 0.8});
    m3.emission = Colour({0.1, 0.1});
    m3.translucency = 0.0;
    Material m4;
    m4.reflection = 0.0;
    m4.albedo = Colour({0.0, 0.0});
    m4.emission = Colour({0.0, 0.0, 0.0});
    m4.translucency = 0.0;
    Material m5;
    m5.reflection = 0.0;
    m5.albedo = Colour({1.0, 1.0});
    m4.emission = Colour({0.0, 0.0, 0.0});
    m5.translucency = 1.0;
    m5.refract = BK7;

    std::vector<Material> materials = {air, m1, m2, m3, m4, m5}; // , m1, m2, m3, m4, m5};

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
                    int y = floor(pos.get(0) / (float)width);

                    // call the damn thing
                    trace(width, height, bounces, subRays, spheres.size(), spheres, mats, img, x, y, wavelengths[i]);
                });
            });
        }
    }

    std::cout << "Finished executing\n";

    tracer::image::WriteImage(parser.get<std::string>("--output"), r, g, b, width, height);
    return 0;
}
