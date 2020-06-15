#ifndef PLOT_TOOL_AXIS_ANGLE_H_
#define PLOT_TOOL_AXIS_ANGLE_H_

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
// TODO: Axis needs to be normalized
template <typename T> AxisAngle<T>::AxisAngle(const T phi_, const T x_, const T y_, const T z_)
{
    phi = phi_;
    x = x_;
    y = y_;
    z = z_;
}

template <typename T> AxisAngle<T>::AxisAngle(const T x_, const T y_, const T z_)
{
    phi = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    if (phi == 0.0)
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    else
    {
        x = x_ / phi;
        y = y_ / phi;
        z = z_ / phi;
    }
}

template <typename T> AxisAngle<T>::AxisAngle(const Vec3D<T>& v)
{
    phi = v.norm();
    if (phi == 0.0)
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    else
    {
        x = v.x / phi;
        y = v.y / phi;
        z = v.z / phi;
    }
}

template <typename T> AxisAngle<T>::AxisAngle() {}

template <typename T> AxisAngle<T> AxisAngle<T>::normalized() const
{
    AxisAngle<T> normalized_axis_angle;
    T d = std::sqrt(x * x + y * y + z * z);
    if (d == 0)
    {
        normalized_axis_angle.x = 0.0;
        normalized_axis_angle.y = 0.0;
        normalized_axis_angle.z = 0.0;
    }
    else
    {
        normalized_axis_angle.x = x / d;
        normalized_axis_angle.y = y / d;
        normalized_axis_angle.z = z / d;
    }
    normalized_axis_angle.phi = phi;
    return normalized_axis_angle;
}

template <typename T> Matrix<T> AxisAngle<T>::toRotationMatrix() const
{
    AxisAngle<T> normalized_axis_angle = normalized();

    const Matrix<T> k_matrix =
        Vec3D<T>(normalized_axis_angle.x, normalized_axis_angle.y, normalized_axis_angle.z)
            .toCrossProductMatrix();

    const Matrix<T> unit_matrix = unitMatrix<T>(3, 3);

    const Matrix<T> rotation_matrix =
        unit_matrix + std::sin(normalized_axis_angle.phi) * k_matrix +
        (1.0 - std::cos(normalized_axis_angle.phi)) * k_matrix * k_matrix;

    return rotation_matrix;
}

template <typename T> Quaternion<T> AxisAngle<T>::toQuaternion() const
{
    Vec3D<T> v = Vec3D<T>(x, y, z).normalized();
    Quaternion<T> q;
    q.x = v.x * std::sin(phi / 2.0);
    q.y = v.y * std::sin(phi / 2.0);
    q.z = v.z * std::sin(phi / 2.0);
    q.w = std::cos(phi / 2.0);
    return q;
}

template <typename T> RollPitchYaw<T> AxisAngle<T>::toRollPitchYaw() const
{
    const Quaternion<T> q = toQuaternion();
    return q.toRollPitchYaw();
}

// Non class methods

template <typename T> AxisAngle<T> rotationMatrixToAxisAngle(const Matrix<T>& m)
{
    // Reference: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/
    AxisAngle<T> axis_angle;
    T a0 = m(2, 1) - m(1, 2);
    T a1 = m(0, 2) - m(2, 0);
    T a2 = m(1, 0) - m(0, 1);
    T inv_den = 1.0 / std::sqrt(a0 * a0 + a1 * a1 + a2 * a2);

    axis_angle.phi = std::acos((m(0, 0) + m(1, 1) + m(2, 2) - 1.0) / 2.0);
    if (std::abs(axis_angle.phi) < 1e-8)
    {
        axis_angle.x = 1.0;
        axis_angle.y = 0.0;
        axis_angle.z = 0.0;
    }
    else
    {
        axis_angle.x = a0 * inv_den;
        axis_angle.y = a1 * inv_den;
        axis_angle.z = a2 * inv_den;
    }

    return axis_angle;
}

}  // namespace plot_tool

#endif
