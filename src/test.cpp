#include <poly.hpp>
#include<iostream>

std::ostream &operator<<(std::ostream &os, Polynomial const &p) { 
    for(unsigned i = p.coefficients.size(); i-- > 0;) {
      double coeff = p.coefficients[i];
      if (coeff >= 0 && i != (p.coefficients.size() - 1)) {os << '+';}
      os << coeff;
      os << "x^";
      os << i;
      os << " ";
    }
    return os;
}

int main() {
  Polynomial poly {{-0.5, 1.0}};
  std::cout << poly << '\n';
  std::cout << (poly*poly);
}
