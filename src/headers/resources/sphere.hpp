#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <utils/vec.hpp>

class Sphere {
public:
  Vec<double, 3> center;
  double radius;
  int matIdx;
  Sphere(Vec<double, 3> center_, double radius_, int matIdx_) : center{center_}, radius{radius_}, matIdx{matIdx_} {}
  Sphere() = default;
};

#endif // !SPHERE_HPP
