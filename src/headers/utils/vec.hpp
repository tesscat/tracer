#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>
#include <initializer_list>
#include <array>
template<typename T, int len>
class Vec {
public:
    std::array<T, len> data;
    // T operator[](int idx) {return data[idx];}
    template<typename... T_>
    Vec(T_... d) : data{static_cast<T>(d)...} {}
    // for (int i = 0; i < len; i++) {
    // data[i] = d[i];
    // }
    // }
    T& operator[](int idx) {return data[idx];}
    Vec() {
        data = std::array<T, len>();
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

#endif // !VEC_HPP
