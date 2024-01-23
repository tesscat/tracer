#include <algorithm>
#include <resources/image.hpp>


#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace tracer::image {

const double imageColourDepth = 255.0;

void WriteImage(std::string filename, std::vector<double> r, std::vector<double> g, std::vector<double> b, size_t width, size_t height) {
    size_t len = width*height;
    std::vector<uint8_t> data = std::vector<uint8_t>(len*3);
    for (size_t i = 0; i < len; i++) {
        data[3*i] = std::clamp(r[i], 0.0, 1.0) * imageColourDepth;
        data[3*i + 1] = std::clamp(g[i], 0.0, 1.0) * imageColourDepth;
        data[3*i + 2] = std::clamp(b[i], 0.0, 1.0) * imageColourDepth;
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_png(filename.c_str(), width, height, 3, data.data(), width * sizeof(uint8_t) * 3);
}

}
