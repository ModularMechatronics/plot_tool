#ifndef PLOT_TOOL_ROLL_PITCH_YAW_H_
#define PLOT_TOOL_ROLL_PITCH_YAW_H_

#include <cmath>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> RollPitchYaw<T>::RollPitchYaw(const T roll_, const T pitch_, const T yaw_)
{
    roll = roll_;
    pitch = pitch_;
    yaw = yaw_;
}

template <typename T> RollPitchYaw<T>::RollPitchYaw() {}

template <typename T> Quaternion<T> RollPitchYaw<T>::toQuaternion() const
{
    T cy = std::cos(yaw * 0.5);
    T sy = std::sin(yaw * 0.5);
    T cp = std::cos(pitch * 0.5);
    T sp = std::sin(pitch * 0.5);
    T cr = std::cos(roll * 0.5);
    T sr = std::sin(roll * 0.5);

    Quaternion<T> q;

    q.w = cy * cp * cr + sy * sp * sr;
    q.x = cy * cp * sr - sy * sp * cr;
    q.y = sy * cp * sr + cy * sp * cr;
    q.z = sy * cp * cr - cy * sp * sr;

    return q;
}

template <typename T> AxisAngle<T> RollPitchYaw<T>::toAxisAngle() const
{
    Quaternion<T> q = toQuaternion();
    return q.toAxisAngle();
}

template <typename T> Matrix<T> rotationMatrixFromYaw(const T yaw)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(yaw);
    const T sa = std::sin(yaw);

    m(0, 0) = ca;
    m(0, 1) = -sa;
    m(0, 2) = 0.0;

    m(1, 0) = sa;
    m(1, 1) = ca;
    m(1, 2) = 0.0;

    m(2, 0) = 0.0;
    m(2, 1) = 0.0;
    m(2, 2) = 1.0;

    return m;
}

template <typename T> Matrix<T> rotationMatrixFromRoll(const T roll)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(roll);
    const T sa = std::sin(roll);

    m(0, 0) = 1.0;
    m(0, 1) = 0.0;
    m(0, 2) = 0.0;

    m(1, 0) = 0.0;
    m(1, 1) = ca;
    m(1, 2) = -sa;

    m(2, 0) = 0.0;
    m(2, 1) = sa;
    m(2, 2) = ca;

    return m;
}

template <typename T> Matrix<T> rotationMatrixFromPitch(const T pitch)
{
    Matrix<T> m(3, 3);
    const T ca = std::cos(pitch);
    const T sa = std::sin(pitch);

    m(0, 0) = ca;
    m(0, 1) = 0.0;
    m(0, 2) = sa;

    m(1, 0) = 0.0;
    m(1, 1) = 1.0;
    m(1, 2) = 0.0;

    m(2, 0) = -sa;
    m(2, 1) = 0.0;
    m(2, 2) = ca;

    return m;
}

template <typename T> Matrix<T> RollPitchYaw<T>::toRotationMatrix() const
{
    return rotationMatrixFromYaw(yaw) * rotationMatrixFromPitch(pitch) *
           rotationMatrixFromRoll(roll);
}

template <typename T> RollPitchYaw<T> rotationMatrixToRollPitchYaw(const Matrix<T>& m)
{
    return RollPitchYaw<T>(
        std::atan2(m(2, 1), m(2, 2)), std::asin(-m(2, 0)), std::atan2(m(1, 0), m(0, 0)));
}

}  // namespace plot_tool

#endif
