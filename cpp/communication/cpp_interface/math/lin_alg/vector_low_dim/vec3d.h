
#ifndef VEC3D_H_
#define VEC3D_H_

#include <cmath>

#include "logging.h"
#include "math/math_core.h"

// TODO:
//  - Angle between 2d and 3d vectors
//  - Projection of vector to vector/plane/line
//  - Find angle axis rotation from two vectors

namespace plot_tool
{
template <typename T> Vec3D<T>::Vec3D(const T x_, const T y_, const T z_)
{
    x = x_;
    y = y_;
    z = z_;
}

template <typename T> Vec3D<T>::Vec3D() {}

template <typename T> Vec3D<T>::Vec3D(const T v_array[3])
{
    x = v_array[0];
    y = v_array[1];
    z = v_array[2];
}

template <typename T> CylindricalCoord<T> Vec3D<T>::toCylindricalVec() const
{
    T phi;
    if (x == 0.0 && y == 0.0)
    {
        phi = 0.0;
    }
    else
    {
        phi = std::atan2(y, x);
    }

    return CylindricalCoord<T>(std::sqrt(x * x + y * y), z, phi);
}

template <typename T> SphericalCoord<T> Vec3D<T>::toSphericalCoord() const
{
    SphericalCoord<T> sv;
    sv.r = std::sqrt(x * x + y * y + z * z);
    sv.phi = std::acos(z / sv.r);
    sv.theta = std::atan2(y, x);
    return sv;
}

///////////////////////////

template <typename T> Vec3D<T> Vec3D<T>::normalized() const
{
    return Vec3D<T>(x, y, z) / std::sqrt(x * x + y * y + z * z);
}

template <typename T> Vec3D<T> Vec3D<T>::vectorBetweenPoints(const Point3D<T>& end_point) const
{
    // "This" is start point
    return end_point - *this;
}

template <typename T>
Vec3D<T> Vec3D<T>::normalizedVectorBetweenPoints(const Point3D<T>& end_point) const
{
    // "This" is start point
    return (end_point - *this).normalized();
}

template <typename T> T Vec3D<T>::squaredNorm() const
{
    return x * x + y * y + z * z;
}

template <typename T> T Vec3D<T>::norm() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template <typename T> Vec3D<T> Vec3D<T>::elementWiseMultiply(const Vec3D<T>& factor_vector) const
{
    return Vec3D<T>(x * factor_vector.x, y * factor_vector.y, z * factor_vector.z);
}

template <typename T> Vec3D<T> Vec3D<T>::elementWiseDivide(const Vec3D<T>& denominator_vector) const
{
    return Vec3D<T>(x / denominator_vector.x, y / denominator_vector.y, z / denominator_vector.z);
}

template <typename T> Vec3D<T> Vec3D<T>::crossProduct(const Vec3D<T>& right_vector) const
{
    return Vec3D<T>(y * right_vector.z - z * right_vector.y,
                    z * right_vector.x - x * right_vector.z,
                    x * right_vector.y - y * right_vector.x);
}

template <typename T>
Point3D<T> Vec3D<T>::mirrorPointInThis(const Point3D<T>& point_to_mirror) const
{
    // Mirrors "point_to_mirror" in "this"
    return *this - this->vectorBetweenPoints(point_to_mirror);
}

template <typename T> T Vec3D<T>::angleBetweenVectors(const Vec3D<T>& v) const
{
    T dot_product = (*this) * v;
    return std::acos(dot_product / ((this->norm()) * (v.norm())));
}

// Non class functions

template <typename T> bool operator==(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return (v0.x == v1.x) && (v0.y == v1.y) && (v0.z == v1.z);
}

template <typename T> bool operator!=(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return !(v0 == v1);
}

template <typename T> Vec3D<T> operator*(const T f, const Vec3D<T>& v)
{
    return Vec3D<T>(f * v.x, f * v.y, f * v.z);
}

template <typename T> Vec3D<T> operator*(const Vec3D<T>& v, const T f)
{
    return Vec3D<T>(f * v.x, f * v.y, f * v.z);
}

template <typename T> T operator*(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

template <typename T> Vec3D<T> operator/(const Vec3D<T>& v, const T f)
{
    return Vec3D<T>(v.x / f, v.y / f, v.z / f);
}

template <typename T> Vec3D<T> operator/(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return Vec3D<T>(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

template <typename T> Vec3D<T> operator+(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return Vec3D<T>(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

template <typename T> Vec3D<T> operator-(const Vec3D<T>& v0, const Vec3D<T>& v1)
{
    return Vec3D<T>(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

template <typename T> Vec3D<T> operator*(const Matrix<T>& m, const Vec3D<T>& v)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 3) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 3) << "Matrix dimension mismatch!";
    Vec3D<T> res;
    res.x = m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z;
    res.y = m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z;
    res.z = m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z;
    return res;
}

template <typename T> Vec3D<T> operator*(const Vec3D<T>& v, const Matrix<T>& m)
{
    ASSERT(m.isAllocated()) << "Matrix not allocated!";
    ASSERT(m.rows() == 3) << "Matrix dimension mismatch!";
    ASSERT(m.cols() == 3) << "Matrix dimension mismatch!";
    Vec3D<T> res;
    res.x = v.x * m(0, 0) + v.y * m(1, 0) + v.z * m(2, 0);
    res.y = v.x * m(0, 1) + v.y * m(1, 1) + v.z * m(2, 1);
    res.z = v.x * m(0, 2) + v.y * m(1, 2) + v.z * m(2, 2);
    return res;
}

template <typename T> Vec3D<T> operator+(const Vec3D<T>& v, const T f)
{
    return Vec3D<T>(v.x + f, v.y + f, v.z + f);
}

template <typename T> Vec3D<T> operator+(const T f, const Vec3D<T>& v)
{
    return Vec3D<T>(v.x + f, v.y + f, v.z + f);
}

template <typename T> Vec3D<T> operator-(const Vec3D<T>& v, const T f)
{
    return Vec3D<T>(v.x - f, v.y - f, v.z - f);
}

template <typename T> Vec3D<T> operator-(const T f, const Vec3D<T>& v)
{
    return Vec3D<T>(f - v.x, f - v.y, f - v.z);
}

template <typename T> Vec3D<T> operator/(const T f, const Vec3D<T>& v)
{
    return Vec3D<T>(f / v.x, f / v.y, f / v.z);
}

template <typename T> Vec3D<T> operator-(const Vec3D<T>& v)
{
    return Vec3D<T>(-v.x, -v.y, -v.z);
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Vec3D<T>& v)
{
    std::string s =
        "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + " ]";
    os << s;
    return os;
}

template <typename T> bool Vec3D<T>::areAllNan() const
{
    return (x == NAN) && (y == NAN) && (z == NAN);
}
template <typename T> bool Vec3D<T>::isAnyNan() const
{
    return (x == NAN) || (y == NAN) || (z == NAN);
}

template <typename T> Vec3D<T> Vec3D<T>::perpendicularVector() const
{
    if ((x == 0) && (y == 0) && (z == 0))
    {
        return Vec3D<T>(NAN, NAN, NAN);
    }
    else
    {
        const T a = x;
        const T b = y;
        const T c = z;
        T xn, yn, zn;
        if (x >= y && x >= z)
        {
            yn = 1.0;
            zn = 1.0;
            xn = -(b * yn + c * zn) / a;
        }
        else if (y >= x && y >= z)
        {
            xn = 1.0;
            zn = 1.0;
            yn = -(a * xn + c * zn) / b;
        }
        else if (z >= x && z >= y)
        {
            xn = 1.0;
            yn = 1.0;
            zn = -(a * xn + b * yn) / c;
        }
        else
        {
            // This 'else' statement is mainly to surpress compiler warning
            xn = NAN;
            yn = NAN;
            zn = NAN;
            LOG_WARNING() << "Something's weird";
        }

        return Vec3D<T>(xn, yn, zn);
    }
}

template <typename T> T angleBetweenVectors(const Vec3D<T> v0, const Vec3D<T> v1)
{
    return std::acos((v0 * v1) / (v0.norm() * v1.norm()));
}

template <typename T> T cosOfAngleBetweenVectors(const Vec3D<T> v0, const Vec3D<T> v1)
{
    return v0 * v1 / (v0.norm() * v1.norm());
}

template <typename T> Vec3D<T> projectVectorOntoVector(const Vec3D<T> v0, const Vec3D<T> v1)
{
    // Projects v0 onto v1
    return v0.norm() * cosOfAngleBetweenVectors(v0, v1) * v1.normalized();
}

}  // namespace plot_tool

#endif
