#include <cmath>
#include <initializer_list>
#include <vector>
template<typename T, int len>
class Vec {
public:
  std::vector<T> data;
  // T operator[](int idx) {return data[idx];}
  Vec(std::initializer_list<T> d) : data{d} {}
    // for (int i = 0; i < len; i++) {
      // data[i] = d[i];
    // }
  // }
  T& operator[](int idx) {return data[idx];}
  Vec() {
    data = std::vector<T>(len);
  };
  Vec(const Vec<T, len>& other) {
    data = other.data;
    // for (int i = 0; i < len; i++) {
      // data[i] = other[i];
    // }
  }
  Vec<T, len> operator * (T scalar) {
    Vec<T, len> result (*this);
    result *= scalar;
    return result;
  }
  void operator += (Vec<T, len> other) {
    for (int i = 0; i < len; i++) {
      data[i] += other[i];
    }
  }
  void operator *= (T scalar) {
    for (int i = 0; i < len; i++) {
      data[i] *= scalar;
    }
  }
  // TODO: general optim
  Vec<T, len> operator + (Vec<T, len> other) {
    Vec<T, len> result (*this);
    result += other;
    return result;
  }
  Vec<T, len> operator - (Vec<T, len> other) {
    Vec<T, len> result;
    for (int i = 0; i < len; i++) {
      result[i] = data[i] - other[i];
    }
    return result;
  }
  const T length() const {
    T sum = 0;
    for (auto i : data) {
      sum += i*i;
    }
    return std::sqrt(sum);
  };
  Vec<T, len> normalized() {
    return Vec<T, len>(*this) * (1/length());
  }
};
