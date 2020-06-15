#ifndef PLOT_TOOL_ANGLE_AXIS_CLASS_H_
#define PLOT_TOOL_ANGLE_AXIS_CLASS_H_

namespace plot_tool
{
template <typename T> struct AxisAngle
{
    T phi;
    T x;
    T y;
    T z;

    AxisAngle(const T phi_, const T x_, const T y_, const T z_);
    AxisAngle(const T x_, const T y_, const T z_);
    AxisAngle(const Vec3D<T>& v);
    AxisAngle();

    AxisAngle<T> normalized() const;

    Matrix<T> toRotationMatrix() const;
    Quaternion<T> toQuaternion() const;
    RollPitchYaw<T> toRollPitchYaw() const;
};

}  // namespace plot_tool

#endif
