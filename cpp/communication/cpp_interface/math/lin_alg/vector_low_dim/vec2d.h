
#ifndef VEC2D_H_
#define VEC2D_H_

#include <cmath>

#include "logging.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> Vec2D<T>::Vec2D(const T x_, const T y_)
{
    x = x_;
    y = y_;
}

template <typename T> Vec2D<T>::Vec2D() {}

template <typename T> Vec2D<T>::Vec2D(const T v_array[2])
{
    x = v_array[0];
    y = v_array[1];
}

template <typename T> ComplexCoord<T> Vec2D<T>::toComplex() const
{
    return ComplexCoord<T>(x, y);
}

template <typename T> PolarCoord<T> Vec2D<T>::toPolar() const
{
    return PolarCoord<T>(std::sqrt(x * x + y * y), std::atan2(y, x));
}

template <typename T> T Vec2D<T>::angle() const
{
    return std::atan2(y, x);
}

template <typename T> Vec2D<T> Vec2D<T>::normalized() const
{
    return Vec2D<T>(x, y) / std::sqrt(x * x + y * y);
}

template <typename T> Vec2D<T> Vec2D<T>::vectorBetweenPoints(const Point2D<T>& end_point) const
{
    // "This" is start point
    return end_point - *this;
}

template <typename T>
Vec2D<T> Vec2D<T>::normalizedVectorBetweenPoints(const Point2D<T>& end_point) const
{
    // "This" is start point
    return (end_point - *this).normalized();
}

template <typename T> T Vec2D<T>::squaredNorm() const
{
    return x * x + y * y;
}

template <typename T> T Vec2D<T>::norm() const
{
    return std::sqrt(x * x + y * y);
}

template <typename T> Vec2D<T> Vec2D<T>::elementWiseMultiply(const Vec2D<T>& factor_vector) const
{
    return Vec2D<T>(x * factor_vector.x, y * factor_vector.y);
}

template <typename T> Vec2D<T> Vec2D<T>::elementWiseDivide(const Vec2D<T>& denominator_vector) const
{
    return Vec2D<T>(x / denominator_vector.x, y / denominator_vector.y);
}

template <typename T>
Point2D<T> Vec2D<T>::rotatePointAroundThis(const Point2D<T>& point_to_rotate, const T angle) const
{
    // Rotates "point_to_rotate" "angle" radians around "this"
    Point2D<T> no_offset_point = point_to_rotate - *this;
    Point2D<T> rotated_point = rotationMatrix2D(angle) * no_offset_point;

    return rotated_point + *this;
}

template <typename T>
Point2D<T> Vec2D<T>::mirrorPointInThis(const Point2D<T>& point_to_mirror) const
{
    // Mirrors "point_to_mirror" in "this"
    return *this - this->vectorBetweenPoints(point_to_mirror);
}

template <typename T> T Vec2D<T>::angleBetweenVectors(const Vec2D<T>& v) const
{
    T dot_product = (*this) * v;
    return std::acos(dot_product / ((this->norm()) * (v.norm())));
}

// Non class functions

template <typename T> bool operator==(const Vec2D<T>& v0, const Vec2D<T>& v1)
{
    return (v0.x == v1.x) && (v0.y == v1.y);
}

template <typename T> bool operator!=(const Vec2D<T>& v0, const Vec2D<T>& v1)
{
    return !(v0 == v1);
}

template <typename T> Vec2D<T> operator*(const T f, const Vec2D<T>& v)
{
    return Vec2D<T>(f * v.x, f * v.y);
}

template <typename T> Vec2D<T> operator*(const Vec2D<T>& v, const T f)
{
    return Vec2D<T>(f * v.x, f * v.y);
}

template <typename T> T operator*(const Vec2D<T>& v0, const Vec2D<T>& v1)
{
    return v0.x * v1.x + v0.y * v1.y;
}

template <typename T> Vec2D<T> operator/(const Vec2D<T>& v, const T f)
{
    return Vec2D<T>(v.x / f, v.y / f);
}

template <typename T> Vec2D<T> operator+(const Vec2D<T>& v0, const Vec2D<T>& v1)
{
    return Vec2D<T>(v0.x + v1.x, v0.y + v1.y);
}

template <typename T> Vec2D<T> operator-(const Vec2D<T>& v0, const Vec2D<T>& v1)
{
    return Vec2D<T>(v0.x - v1.x, v0.y - v1.y);
}

template <typename T> Vec2D<T> operator*(const Matrix<T>& m, const Vec2D<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 2) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 2) << "Matrix dimension mismatch!";
    Vec2D<T> res;
    res.x = m(0, 0) * v.x + m(0, 1) * v.y;
    res.y = m(1, 0) * v.x + m(1, 1) * v.y;
    return res;
}

template <typename T> Vec2D<T> operator*(const Vec2D<T>& v, const Matrix<T>& m)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 2) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 2) << "Matrix dimension mismatch!";
    Vec2D<T> res;
    res.x = v.x * m(0, 0) + v.y * m(1, 0);
    res.y = v.x * m(0, 1) + v.y * m(1, 1);
    return res;
}

template <typename T> Vec2D<T> operator+(const Vec2D<T>& v, const T f)
{
    return Vec2D<T>(v.x + f, v.y + f);
}

template <typename T> Vec2D<T> operator+(const T f, const Vec2D<T>& v)
{
    return Vec2D<T>(v.x + f, v.y + f);
}

template <typename T> Vec2D<T> operator-(const Vec2D<T>& v, const T f)
{
    return Vec2D<T>(v.x - f, v.y - f);
}

template <typename T> Vec2D<T> operator-(const T f, const Vec2D<T>& v)
{
    return Vec2D<T>(f - v.x, f - v.y);
}

template <typename T> Vec2D<T> operator/(const T f, const Vec2D<T>& v)
{
    return Vec2D<T>(f / v.x, f / v.y);
}

template <typename T> Vec2D<T> operator-(const Vec2D<T>& v)
{
    return Vec2D<T>(-v.x, -v.y);
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Vec2D<T>& v)
{
    std::string s = "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
    os << s;
    return os;
}

template <typename T> bool Vec2D<T>::areAllNan() const
{
    return (x == NAN) && (y == NAN);
}

template <typename T> bool Vec2D<T>::isAnyNan() const
{
    return (x == NAN) || (y == NAN);
}

}  // namespace plot_tool

#endif
