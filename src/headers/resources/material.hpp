#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <resources/common_mats.hpp>
#include <resources/colour.hpp>

using namespace tracer::colour;

class SellmeierCoeffs {
public:
    double b1, b2, b3;
    double c1, c2, c3;
    SellmeierCoeffs(double b1, double b2, double b3, double c1, double c2, double c3);

    double Calculate(const double wavelength_visirange) const;
};

class Material {
public:
    Colour albedo;
    Colour emission;
    double reflection = 0.0;
    double translucency = 0.0;
    SellmeierCoeffs refract = AIR;
};


#endif // !MATERIAL_HPP
