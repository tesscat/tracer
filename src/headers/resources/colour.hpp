#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <cmath>
#include <vector>

namespace tracer::colour {
// 380-750 visible, therefore 370 nm space
// https://computergraphics.stackexchange.com/questions/10547/what-wavelengthsdominant-the-primary-rgb-colors-are-supposed-to-be-in-srgb-col
// R=630nm, G=532nm, and B=467nm
constexpr double nmToVisiRange(double nm) {
  return (nm - 380)/370;
}

constexpr double visiRangeToNm(double visi) {
    return (visi*370) + 380;
}

constexpr double visiRangeToUm(double visi) {
    return ((visi*370)+380)*1e-3;
}

class Colour {
public:
  double segments = 4;
  std::vector<double> points;
  double Sample(double point_);

  Colour(std::vector<double> points_);
  Colour(double brightness);
  Colour();
};
}
#endif
