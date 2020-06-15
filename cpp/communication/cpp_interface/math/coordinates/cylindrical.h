#ifndef PLOT_TOOL_CYLINDRICAL_H_
#define PLOT_TOOL_CYLINDRICAL_H_

#include <cmath>
#include <vector>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> CylindricalCoord<T>::CylindricalCoord(const T r_, const T z_, const T phi_)
{
    r = r_;
    z = z_;
    phi = phi_;
}

template <typename T> CylindricalCoord<T>::CylindricalCoord() {}

template <typename T> SphericalCoord<T> CylindricalCoord<T>::toSphericalCoord() const
{
    SphericalCoord<T> sv;

    sv.r = std::sqrt(r * r + z * z);
    sv.theta = std::atan2(r, z);
    sv.phi = phi;

    return sv;
}

template <typename T> Vec3D<T> CylindricalCoord<T>::toVec3D() const
{
    return Vec3D<T>(r * std::cos(phi), r * std::sin(phi), z);
}
}  // namespace plot_tool

#endif
