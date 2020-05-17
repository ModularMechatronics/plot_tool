#ifndef SPHERICAL_CLASS_H_
#define SPHERICAL_CLASS_H_

namespace plot_tool
{
template <typename T> struct SphericalCoord
{
    // phi for azimuth, theta for inclination
    T r;
    T phi;
    T theta;

    SphericalCoord(const T r_, const T phi_, const T theta_);
    SphericalCoord();

    CylindricalCoord<T> toCylindricalVec() const;
    Vec3D<T> toVec3D() const;
};

}  // namespace plot_tool

#endif
