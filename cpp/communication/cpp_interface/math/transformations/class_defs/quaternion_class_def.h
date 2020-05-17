#ifndef QUATERNION_CLASS_H_
#define QUATERNION_CLASS_H_

namespace plot_tool
{
template <typename T> struct Quaternion
{
    // w is real component, (x, y, z) are imaginary components
    T w;
    T x;
    T y;
    T z;

    Quaternion(const T w_, const T x_, const T y_, const T z_);
    Quaternion();

    Matrix<T> toRotationMatrix() const;
    AxisAngle<T> toAxisAngle() const;
    RollPitchYaw<T> toRollPitchYaw() const;

    T norm() const;
    T squaredNorm() const;
    Quaternion<T> normalized() const;
};
}  // namespace plot_tool

#endif
