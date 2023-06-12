#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <cmath>
#include <vector>

// 380-750 visible, therefore 370 nm space
// https://computergraphics.stackexchange.com/questions/10547/what-wavelengthsdominant-the-primary-rgb-colors-are-supposed-to-be-in-srgb-col
// R=630nm, G=532nm, and B=467nm
constexpr double nmToVisiRange(double nm) {
  return (nm - 380)/370;
}

class Colour {
public:
  double segments = 4;
  std::vector<double> points;
  double Sample(double point) {
    if (point == 1.0) point = 0.999;
    point *= segments;
    int index = std::floor(point);
    double rem = point - index;
    double k1 = points[index];
    double lerped = (rem * k1) + ((1-rem) * points[index + 1]);
    return lerped + k1;
  }

  Colour(std::vector<double> points_) : points {points_}, segments(points_.size() - 1) {}
  Colour(double brightness) : segments(1.0), points({brightness, brightness}) {}
  Colour() : Colour(0.0) {}
};

#endif
