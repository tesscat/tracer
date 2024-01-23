#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <string>
#include <vector>


namespace tracer::image {

void WriteImage(std::string filename, std::vector<double> r, std::vector<double> g, std::vector<double> b, size_t width, size_t height);

}

#endif
