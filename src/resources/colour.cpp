#include <resources/colour.hpp>

namespace tracer::colour {
double Colour::Sample(const double point_) const {
    double point = point_;
    // std::cout << '\n' << segments << '\n';
    // for (auto point: points)
    // std::cout << point << ' ';
    if (point >= 1.0) point = 0.999;
    point *= segments;
    int index = std::floor(point);
    double rem = point - index;
    // std::cout << '\n' << point << ' ' << index << ' ' << rem << '\n';
    double k1 = points[index];
    double m = (points[index+1] - k1);
    return m*rem + k1;
    // double lerped = (rem * k1) + ((1-rem) * points[index + 1]);
    // std::cout << lerped << "\n\n";
    // return lerped;
}

Colour::Colour(std::vector<double> points_) : points {points_}, segments(points_.size() - 1) {}
Colour::Colour(double brightness) : segments(1.0), points({brightness, brightness}) {}
Colour::Colour() : Colour(0.0) {}

}
