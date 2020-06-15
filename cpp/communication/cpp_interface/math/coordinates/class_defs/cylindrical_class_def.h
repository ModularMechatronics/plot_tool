#ifndef PLOT_TOOL_CYLINDRICAL_CLASS_H_
#define PLOT_TOOL_CYLINDRICAL_CLASS_H_

namespace plot_tool
{
template <typename T> struct CylindricalCoord
{
    T r;
    T z;
    T phi;

    CylindricalCoord(const T r_, const T z_, const T phi_);
    CylindricalCoord();

    SphericalCoord<T> toSphericalCoord() const;
    Vec3D<T> toVec3D() const;
};

}  // namespace plot_tool

#endif
