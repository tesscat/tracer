#include <cmath>
#include <resources/material.hpp>

SellmeierCoeffs::SellmeierCoeffs(double b1_, double b2_, double b3_, double c1_, double c2_, double c3_) :
    b1{b1_}, b2{b2_}, b3{b3_},
    c1{c1_}, c2{c2_}, c3{c3_} {}

double SellmeierCoeffs::Calculate(double wavelength_visirange) {
    double wl = visiRangeToUm(wavelength_visirange);
    double wl2 = wl*wl;
    double t1 = (b1*wl2)/(wl2 - c1);
    double t2 = (b2*wl2)/(wl2 - c2);
    double t3 = (b3*wl2)/(wl2 - c3);
    double sum = t1 + t2 + t3 + 1;

    return std::sqrt(sum);
}
