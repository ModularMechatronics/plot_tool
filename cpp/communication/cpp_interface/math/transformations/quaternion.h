
#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <cmath>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> Quaternion<T>::Quaternion(const T w_, const T x_, const T y_, const T z_)
{
    w = w_;
    x = x_;
    y = y_;
    z = z_;
}

template <typename T> Quaternion<T>::Quaternion() {}

template <typename T> RollPitchYaw<T> Quaternion<T>::toRollPitchYaw() const
{
    RollPitchYaw<T> rpy;
    // Roll (x-axis rotation)
    T sinr_cosp = 2.0 * (w * x + y * z);
    T cosr_cosp = 1.0 - 2.0 * (x * x + y * y);
    rpy.roll = std::atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    T sinp = 2.0 * (w * y - z * x);
    if (std::fabs(sinp) >= 1)
    {
        rpy.pitch = std::copysign(M_PI / 2.0, sinp);  // Use 90 degrees if out of range
    }
    else
    {
        rpy.pitch = std::asin(sinp);
    }

    // Yaw (z-axis rotation)
    T siny_cosp = 2.0 * (w * z + x * y);
    T cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
    rpy.yaw = std::atan2(siny_cosp, cosy_cosp);
    return rpy;
}

template <typename T> AxisAngle<T> Quaternion<T>::toAxisAngle() const
{
    AxisAngle<T> axis_angle;
    axis_angle.phi = 2.0 * std::acos(w);
    axis_angle.x = x / std::sqrt(1 - w * w);
    axis_angle.y = y / std::sqrt(1 - w * w);
    axis_angle.z = z / std::sqrt(1 - w * w);

    return axis_angle;
}

template <typename T> Matrix<T> Quaternion<T>::toRotationMatrix() const
{
    Matrix<T> m(3, 3);

    const Quaternion<T> qn = this->normalized();
    const T qr = qn.w;
    const T qi = qn.x;
    const T qj = qn.y;
    const T qk = qn.z;

    m(0, 0) = 1.0 - 2.0 * (qj * qj + qk * qk);
    m(0, 1) = 2.0 * (qi * qj - qk * qr);
    m(0, 2) = 2.0 * (qi * qk + qj * qr);
    m(1, 0) = 2.0 * (qi * qj + qk * qr);
    m(1, 1) = 1.0 - 2.0 * (qi * qi + qk * qk);
    m(1, 2) = 2.0 * (qj * qk - qi * qr);
    m(2, 0) = 2.0 * (qi * qk - qj * qr);
    m(2, 1) = 2.0 * (qj * qk + qi * qr);
    m(2, 2) = 1.0 - 2.0 * (qi * qi + qj * qj);

    return m;
}

template <typename T> T Quaternion<T>::norm() const
{
    return std::sqrt(w * w + x * x + y * y + z * z);
}

template <typename T> T Quaternion<T>::squaredNorm() const
{
    return w * w + x * x + y * y + z * z;
}

template <typename T> Quaternion<T> Quaternion<T>::normalized() const
{
    const T d = this->norm();
    return Quaternion<T>(w / d, x / d, y / d, z / d);
}

// Non class methods

template <typename T> Quaternion<T> operator*(const Quaternion<T>& q, const Quaternion<T>& p)
{
    Vec3D<T> qv = Vec3D<T>(q.x, q.y, q.z);
    Vec3D<T> pv = Vec3D<T>(p.x, p.y, p.z);
    Vec3D<T> intermediate_vector = qv.crossProduct(pv) + q.w * pv + p.w * qv;
    return Quaternion<T>(
        q.w * p.w - pv * qv, intermediate_vector.x, intermediate_vector.y, intermediate_vector.z);
}

template <typename T> Quaternion<T> rotationMatrixToQuaternion(const Matrix<T>& m)
{
    // Reference:
    // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
    Quaternion<T> q;
    q.w = std::sqrt(1.0 + m(0, 0) + m(1, 1) + m(2, 2)) / 2.0;
    q.x = (m(2, 1) - m(1, 2)) / (4.0 * q.w);
    q.y = (m(0, 2) - m(2, 0)) / (4.0 * q.w);
    q.z = (m(1, 0) - m(0, 1)) / (4.0 * q.w);

    return q;
}

}  // namespace plot_tool

#endif
