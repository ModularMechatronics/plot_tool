
#ifndef VEC4D_H_
#define VEC4D_H_

#include <cmath>

#include "logging.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> Vec4D<T>::Vec4D(const T x_, const T y_, const T z_, const T w_)
{
    x = x_;
    y = y_;
    z = z_;
    w = w_;
}

template <typename T> Vec4D<T>::Vec4D() {}

template <typename T> Vec4D<T>::Vec4D(const T v_array[4])
{
    x = v_array[0];
    y = v_array[1];
    z = v_array[2];
    w = v_array[3];
}

template <typename T> Vec4D<T> Vec4D<T>::normalized() const
{
    return Vec4D<T>(x, y, z, w) / std::sqrt(x * x + y * y + z * z + w * w);
}

template <typename T> T Vec4D<T>::squaredNorm() const
{
    return x * x + y * y + z * z + w * w;
}

template <typename T> T Vec4D<T>::norm() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

template <typename T> Vec4D<T> Vec4D<T>::elementWiseMultiply(const Vec4D<T>& factor_vector) const
{
    return Vec4D<T>(
        x * factor_vector.x, y * factor_vector.y, z * factor_vector.z, w * factor_vector.w);
}

template <typename T> Vec4D<T> Vec4D<T>::elementWiseDivide(const Vec4D<T>& denominator_vector) const
{
    return Vec4D<T>(x / denominator_vector.x,
                    y / denominator_vector.y,
                    z / denominator_vector.z,
                    w / denominator_vector.w);
}

template <typename T> Vec4D<T> Vec4D<T>::vectorBetweenPoints(const Point4D<T>& end_point) const
{
    // "This" is start point
    return end_point - *this;
}

template <typename T>
Vec4D<T> Vec4D<T>::normalizedVectorBetweenPoints(const Point4D<T>& end_point) const
{
    // "This" is start point
    return (end_point - *this).normalized();
}

template <typename T>
Point4D<T> Vec4D<T>::mirrorPointInThis(const Point4D<T>& point_to_mirror) const
{
    // Mirrors "point_to_mirror" in "this"
    return *this - this->vectorBetweenPoints(point_to_mirror);
}

template <typename T> T Vec4D<T>::angleBetweenVectors(const Vec4D<T>& v) const
{
    T dot_product = (*this) * v;
    return std::acos(dot_product / ((this->norm()) * (v.norm())));
}

// Non class functions

template <typename T> bool operator==(const Vec4D<T>& v0, const Vec4D<T>& v1)
{
    return (v0.x == v1.x) && (v0.y == v1.y) && (v0.z == v1.z) && (v0.w == v1.w);
}

template <typename T> bool operator!=(const Vec4D<T>& v0, const Vec4D<T>& v1)
{
    return !(v0 == v1);
}

template <typename T> Vec4D<T> operator*(const T f, const Vec4D<T>& v)
{
    return Vec4D<T>(f * v.x, f * v.y, f * v.z, f * v.w);
}

template <typename T> Vec4D<T> operator*(const Vec4D<T>& v, const T f)
{
    return Vec4D<T>(f * v.x, f * v.y, f * v.z, f * v.w);
}

template <typename T> T operator*(const Vec4D<T>& v0, const Vec4D<T>& v1)
{
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

template <typename T> Vec4D<T> operator/(const Vec4D<T>& v, const T f)
{
    return Vec4D<T>(v.x / f, v.y / f, v.z / f, v.w / f);
}

template <typename T> Vec4D<T> operator+(const Vec4D<T>& v0, const Vec4D<T>& v1)
{
    return Vec4D<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
}

template <typename T> Vec4D<T> operator-(const Vec4D<T>& v0, const Vec4D<T>& v1)
{
    return Vec4D<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

template <typename T> Vec4D<T> operator*(const Matrix<T>& m, const Vec4D<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 4) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 4) << "Matrix dimension mismatch!";
    Vec4D<T> res;
    res.x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w;
    res.y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w;
    res.z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w;
    res.w = m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w;
    return res;
}

template <typename T> Vec4D<T> operator*(const Vec4D<T>& v, const Matrix<T>& m)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 4) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 4) << "Matrix dimension mismatch!";
    Vec4D<T> res;
    res.x = m(0, 0) * v.x + m(1, 0) * v.y + m(2, 0) * v.z + m(3, 0) * v.w;
    res.y = m(0, 1) * v.x + m(1, 1) * v.y + m(2, 1) * v.z + m(3, 1) * v.w;
    res.z = m(0, 2) * v.x + m(1, 2) * v.y + m(2, 2) * v.z + m(3, 2) * v.w;
    res.w = m(0, 3) * v.x + m(1, 3) * v.y + m(2, 3) * v.z + m(3, 3) * v.w;
    return res;
}

template <typename T> Vec4D<T> operator+(const Vec4D<T>& v, const T f)
{
    return Vec4D<T>(v.x + f, v.y + f, v.z + f, v.w + f);
}

template <typename T> Vec4D<T> operator+(const T f, const Vec4D<T>& v)
{
    return Vec4D<T>(v.x + f, v.y + f, v.z + f, v.w + f);
}

template <typename T> Vec4D<T> operator-(const Vec4D<T>& v, const T f)
{
    return Vec4D<T>(v.x - f, v.y - f, v.z - f, v.w - f);
}

template <typename T> Vec4D<T> operator-(const T f, const Vec4D<T>& v)
{
    return Vec4D<T>(f - v.x, f - v.y, f - v.z, f - v.w);
}

template <typename T> Vec4D<T> operator/(const T f, const Vec4D<T>& v)
{
    return Vec4D<T>(f / v.x, f / v.y, f / v.z, f / v.w);
}

template <typename T> Vec4D<T> operator-(const Vec4D<T>& v)
{
    return Vec4D<T>(-v.x, -v.y, -v.z, -v.w);
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Vec4D<T>& v)
{
    std::string s = "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " +
                    std::to_string(v.z) + ", " + std::to_string(v.w) + " ]";
    os << s;
    return os;
}

template <typename T> bool Vec4D<T>::areAllNan() const
{
    return (x == NAN) && (y == NAN) && (z == NAN) && (w == NAN);
}
template <typename T> bool Vec4D<T>::isAnyNan() const
{
    return (x == NAN) || (y == NAN) || (z == NAN) || (w == NAN);
}

}  // namespace plot_tool

#endif
