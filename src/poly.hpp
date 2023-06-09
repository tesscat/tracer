
#include <vector>
#include <cmath>

// x^0 then x^1 etc etc
// TODO: maybe, maybe fractional/non-int coeffs?
class Polynomial {
public:
  std::vector<double> coefficients;
  double at(double x) {
    double res = 0;
    uint i = 0;
    for (auto coeff : coefficients) {
      res += std::pow(x, i) * coeff;
      i++;
    }

    return res;
  }

  Polynomial(std::vector<double> coeffs_) : coefficients {coeffs_} {}
  Polynomial() = default;

  Polynomial(const Polynomial& p) : coefficients {p.coefficients} {};

  Polynomial derivative() {
    Polynomial res = Polynomial();
    // power rule go brr
    for (int i = 1; i < coefficients.size(); i++) {
      res.coefficients.push_back(coefficients[i] * i);
    }
    return res;
  }
  Polynomial indefiniteIntegral() {
    return indefiniteIntegral(0);
  }
  Polynomial indefiniteIntegral(double c) {
    Polynomial res = Polynomial();
    res.coefficients.push_back(c);
    // power rule go brr
    for (int i = 0; i < coefficients.size(); i++) {
      res.coefficients.push_back(coefficients[i] / i);
    }
    return res;
  }
  // Apply limits like this was the indefinite integral
  double limits(double a, double b) {
    return at(a) - at(b);
  }

  void operator += (Polynomial other) {
    int i = 0;
    for (auto coeff : other.coefficients) {
      if (i > coefficients.size()) {
        coefficients.push_back(0.0);
      }
      coefficients[i] += coeff;
      i++;
    }
  };

  Polynomial operator + (Polynomial b) {
    Polynomial a (*this);
    a += b;
    return a;
  };
};

// 380-750 visible, therefore 370 nm space
// https://computergraphics.stackexchange.com/questions/10547/what-wavelengthsdominant-the-primary-rgb-colors-are-supposed-to-be-in-srgb-col
// R=630nm, G=532nm, and B=467nm
class Colour {
public:
  Polynomial poly;
  double flatR() {
    return poly.at((630.0-380.0)/370.0);
  }
  double flatG() {
    return poly.at((532.0-380.0)/370.0);
  }
  double flatB() {
    return poly.at((467.0-380.0)/370.0);
  }
};
