
#ifndef PLOT_TOOL_LINE_3D_H_
#define PLOT_TOOL_LINE_3D_H_

#include <cmath>
#include <vector>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> Line3D<T>::Line3D(const Point3D<T>& p_, const Vec3D<T>& v_) : p(p_), v(v_) {}

template <typename T> Line3D<T>::Line3D() {}

template <typename T> template <typename Y> Line3D<T>::Line3D(const Line3D<Y>& l)
{
    p = l.p;
    v = l.v;
}

template <typename T> Vec3D<T> Line3D<T>::vectorNormalToLine() const
{
    Vec3D<T> vn;
    Vec3D<T> vnorm = v.normalized();

    // Dot product equals zero: v.x * vn.x + v.y * vn.y + v.z * vn.z = 0

    const T xa = std::fabs(vnorm.x);
    const T ya = std::fabs(vnorm.y);
    const T za = std::fabs(vnorm.z);
    if ((za > xa) && (za > ya))
    {
        vn.x = 1.0;
        vn.y = 1.0;
        vn.z = (vnorm.x + vnorm.y) / vnorm.z;
    }
    else if ((xa > za) && (xa > ya))
    {
        vn.x = (vnorm.z + vnorm.y) / vnorm.x;
        vn.y = 1.0;
        vn.z = 1.0;
    }
    else
    {
        vn.x = 1.0;
        vn.y = (vnorm.x + vnorm.z) / vnorm.y;
        vn.z = 1.0;
    }

    return vn.normalized();
}

template <typename T> Point3D<T> Line3D<T>::eval(const T t) const
{
    return p + t * v;
}

template <typename T> Point3D<T> Line3D<T>::closestPointOnLineFromPoint(const Point3D<T>& q) const
{
    const T vx = v.x;
    const T vy = v.y;
    const T vz = v.z;

    const T px = p.x;
    const T py = p.y;
    const T pz = p.z;

    const T qx = q.x;
    const T qy = q.y;
    const T qz = q.z;

    const T t = (vx * (px - qx) + vy * (py - qy) + vz * (pz - qz)) / (vx * vx + vy * vy + vz * vz);

    return this->eval(t);
}

template <typename T>
Vec3D<T> Line3D<T>::vectorBetweenClosestPointOnLineAndPoint(const Point3D<T>& q) const
{
    const Point3D<T> closest_point = this->closestPointOnLineFromPoint(q);
    return q - closest_point;
}

template <typename T> Line3D<T> Line3D<T>::translatedLine(const Vec3D<T>& v) const
{
    Point3D<T> p0 = this->eval(0.0) + v;
    Point3D<T> p1 = this->eval(1.0) + v;

    return Line3D<T>(p0, p0.vectorBetweenPoints());
}

template <typename T>
std::vector<Point3D<T>> Line3D<T>::closestPointsBetweenLines(const Line3D<T>& line) const
{
    std::vector<Point3D<T>> points_vec;

    const T vx0 = v.x;
    const T vy0 = v.y;
    const T vz0 = v.z;
    const T px0 = p.x;
    const T py0 = p.y;
    const T pz0 = p.z;

    const T vx1 = line.v.x;
    const T vy1 = line.v.y;
    const T vz1 = line.v.z;
    const T px1 = line.p.x;
    const T py1 = line.p.y;
    const T pz1 = line.p.z;

    const T t0 = -(px0 * vx0 * vy1 * vy1 - px1 * vx0 * vy1 * vy1 + px0 * vx0 * vz1 * vz1 +
                   py0 * vx1 * vx1 * vy0 - px1 * vx0 * vz1 * vz1 - py1 * vx1 * vx1 * vy0 +
                   py0 * vy0 * vz1 * vz1 + pz0 * vx1 * vx1 * vz0 - py1 * vy0 * vz1 * vz1 -
                   pz1 * vx1 * vx1 * vz0 + pz0 * vy1 * vy1 * vz0 - pz1 * vy1 * vy1 * vz0 -
                   px0 * vx1 * vy0 * vy1 - py0 * vx0 * vx1 * vy1 + px1 * vx1 * vy0 * vy1 +
                   py1 * vx0 * vx1 * vy1 - px0 * vx1 * vz0 * vz1 - pz0 * vx0 * vx1 * vz1 +
                   px1 * vx1 * vz0 * vz1 + pz1 * vx0 * vx1 * vz1 - py0 * vy1 * vz0 * vz1 -
                   pz0 * vy0 * vy1 * vz1 + py1 * vy1 * vz0 * vz1 + pz1 * vy0 * vy1 * vz1) /
                 (vx0 * vx0 * vy1 * vy1 + vx0 * vx0 * vz1 * vz1 - 2.0 * vx0 * vx1 * vy0 * vy1 -
                  2.0 * vx0 * vx1 * vz0 * vz1 + vx1 * vx1 * vy0 * vy0 + vx1 * vx1 * vz0 * vz0 +
                  vy0 * vy0 * vz1 * vz1 - 2.0 * vy0 * vy1 * vz0 * vz1 + vy1 * vy1 * vz0 * vz0);
    const T t1 = (2.0 * vx0 * (px0 - px1 + t0 * vx0) + 2.0 * vy0 * (py0 - py1 + t0 * vy0) +
                  2.0 * vz0 * (pz0 - pz1 + t0 * vz0)) /
                 (2.0 * vx0 * vx1 + 2.0 * vy0 * vy1 + 2.0 * vz0 * vz1);

    Point3D<T> p0 = this->eval(t0);
    Point3D<T> p1 = line.eval(t1);
    points_vec.push_back(p0);
    points_vec.push_back(p1);
    return points_vec;
}

template <typename T>
std::pair<Point3D<T>, Vec3D<T>> Line3D<T>::projectPointAndVectorOntoLine(const Point3D<T>& q,
                                                                         const Vec3D<T>& v) const
{
    Point3D<T> p0 = this->closestPointOnLineFromPoint(q);
    Point3D<T> p1 = this->closestPointOnLineFromPoint(q + v);

    std::pair<Point3D<T>, Vec3D<T>> point_vector_pair(p0, p0.vectorBetweenPoints(p1));
    return point_vector_pair;
}

template <typename T>
Point3D<T> Line3D<T>::rotatePointAroundLine(const Point3D<T>& q, const T angle) const
{
    Vec3D<T> point_offset = this->closestPointOnLineFromPoint(q);
    Point3D<T> no_offset_point = q - point_offset;

    Matrix<T> rotation_matrix = AxisAngle<T>(v * angle).toRotationMatrix();
    Point3D<T> rotated_point = rotation_matrix * no_offset_point;

    return rotated_point + point_offset;
}

template <typename T> Line3D<T> Line3D<T>::negatedLine() const
{
    return Line3D<T>(p, -v);
}

template <typename T> T Line3D<T>::pointDistanceFromLine(const Point3D<T>& q) const
{
    Point3D<T> closest_point = this->closestPointOnLineFromPoint(q);
    return (closest_point - q).norm();
}

template <typename T> T Line3D<T>::angleBetweenLines(const Line3D<T>& line) const
{
    return v.angleBetweenVectors(line.v);
}

template <typename T> Line3D<T> lineFromTwoPoints(const Point3D<T>& p0, const Point3D<T>& p1)
{
    Line3D<T> line;
    line.p = p0;

    const Vec3D<T> line_vector = p1 - p0;
    line.v = line_vector;

    return line;
}

template <typename T>
Line3D<T> Line3D<T>::rotateLineAroundLine(const Line3D<T>& line_to_be_rotated, const T angle) const
{
    // Rotates "line_to_be_rotated" "angle" radians around "this"
    Point3D<T> p0 = line_to_be_rotated.eval(0.0);
    Point3D<T> p1 = line_to_be_rotated.eval(1.0);

    Point3D<T> p0r = this->rotatePointAroundLine(p0, angle);
    Point3D<T> p1r = this->rotatePointAroundLine(p1, angle);

    return lineFromTwoPoints(p0r, p1r);
}

}  // namespace plot_tool

#endif
