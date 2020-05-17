#ifndef COMPLEX_H_
#define COMPLEX_H_

#include <cmath>
#include <vector>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

// Reference: https://github.com/N1ckK/MandelbrotZoom/blob/master/complex.h

namespace plot_tool
{
template <typename T> ComplexCoord<T>::ComplexCoord() {}
template <typename T> ComplexCoord<T>::ComplexCoord(const T real_, const T imag_)
{
    real = real_;
    imag = imag_;
}

template <typename T> PolarCoord<T> ComplexCoord<T>::toPolar() const
{
    return PolarCoord<T>(abs(), std::atan2(imag, real));
}

template <typename T> T ComplexCoord<T>::abs() const
{
    return std::sqrt(real * real + imag * imag);
}

template <typename T> ComplexCoord<T> ComplexCoord<T>::conjugate() const
{
    return ComplexCoord<T>(real, -imag);
}

template <typename T> Vec2D<T> ComplexCoord<T>::toVec2D() const
{
    return Vec2D<T>(real, imag);
}

template <typename T> ComplexCoord<T> ComplexCoord<T>::inv() const
{
    return ComplexCoord<T>(real / (real * real + imag * imag), -imag / (real * real + imag * imag));
}

// Non class methods

template <typename T> ComplexCoord<T> operator*(const ComplexCoord<T>& c, const T f)
{
    return ComplexCoord<T>(f * c.real, f * c.imag);
}

template <typename T> ComplexCoord<T> operator*(const T f, const ComplexCoord<T>& c)
{
    return ComplexCoord<T>(f * c.real, f * c.imag);
}

template <typename T>
ComplexCoord<T> operator*(const ComplexCoord<T>& c0, const ComplexCoord<T>& c1)
{
    return ComplexCoord<T>(c0.real * c1.real - c0.imag * c1.imag,
                           c0.real * c1.imag + c0.imag * c1.real);
}

template <typename T>
ComplexCoord<T> operator+(const ComplexCoord<T>& c0, const ComplexCoord<T>& c1)
{
    return ComplexCoord<T>(c0.real + c1.real, c0.imag + c1.imag);
}

template <typename T>
ComplexCoord<T> operator-(const ComplexCoord<T>& c0, const ComplexCoord<T>& c1)
{
    return ComplexCoord<T>(c0.real - c1.real, c0.imag - c1.imag);
}

template <typename T> T pow(const ComplexCoord<T>& c, int n)
{
    if (n == 0)
    {
        return ComplexCoord<T>(1.0, 0.0);
    }
    else if (n < 0)
    {
        return pow(c.inv(), -n);
    }
    else if (n == 1)
    {
        return c;
    }
    else
    {
        return pow(c, n - 1) * c;
    }
}

template <typename T>
ComplexCoord<T> operator/(const ComplexCoord<T>& c0, const ComplexCoord<T>& c1)
{
    return c0 * c1.inv();
}

template <typename T> ComplexCoord<T> operator/(const ComplexCoord<T>& c, const T f)
{
    return ComplexCoord<T>(c.real / f, c.imag / f);
}

template <typename T> ComplexCoord<T> operator/(const T f, const ComplexCoord<T>& c)
{
    return f * c.inv();
}

}  // namespace plot_tool

#endif
