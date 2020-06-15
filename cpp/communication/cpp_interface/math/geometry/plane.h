
#ifndef PLOT_TOOL_PLANE_H_
#define PLOT_TOOL_PLANE_H_

#include <cmath>
#include <utility>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T> Plane<T>::Plane(const T a_, const T b_, const T c_, const T d_)
{
    a = a_;
    b = b_;
    c = c_;
    d = d_;
}

template <typename T> Plane<T>::Plane(const Point3D<T>& point, const Vec3D<T>& normal_vector)
{
    a = normal_vector.x;
    b = normal_vector.y;
    c = normal_vector.z;
    d = -(a * point.x + b * point.y + c * point.z);
}

template <typename T> Plane<T>::Plane() {}

template <typename T> template <typename Y> Plane<T>::Plane(const Plane<Y>& p)
{
    a = p.a;
    b = p.b;
    c = p.c;
    d = p.d;
}

template <typename T> Plane<T> Plane<T>::normalized() const
{
    Vec3D<T> normal_vec = this->normal();
    T nvl = normal_vec.norm();
    return Plane<T>(a / nvl, b / nvl, c / nvl, d / nvl);
}

template <typename T> T Plane<T>::eval(const Point3D<T>& p)
{
    return a * p.x + b * p.y + c * p.z + d;
}

template <typename T> T Plane<T>::evalXY(const T x, const T y)
{
    return -(a * x + b * y + d) / c;
}

template <typename T> T Plane<T>::evalXZ(const T x, const T z)
{
    return -(a * x + c * z + d) / b;
}

template <typename T> T Plane<T>::evalYZ(const T y, const T z)
{
    return -(b * y + c * z + d) / a;
}

template <typename T> Vec3D<T> Plane<T>::normal() const
{
    return Vec3D<T>(a, b, c);
}

template <typename T> Vec3D<T> Plane<T>::normalizedNormal() const
{
    return Vec3D<T>(a, b, c).normalized();
}

template <typename T> Point3D<T> Plane<T>::lineIntersection(const Line3D<T>& line) const
{
    const T t =
        -(d + a * line.px + b * line.py + c * line.pz) / (a * line.vx + b * line.vy + c * line.vz);
    return line.eval(t);
}

template <typename T> Line3D<T> Plane<T>::projectLineOntoPlane(const Line3D<T>& line) const
{
    const Vec3D<T> line_vector = line.v;
    const Vec3D<T> plane_normal_vector(a, b, c);
    const T angle_between_vectors = line_vector.angleBetweenVectors();
    if (std::fabs(angle_between_vectors) < 1e-8)
    {
        LOG_WARNING() << "Line and plane normal vector almost parallel, degenerate case!";
    }
    const Point3D<T> p0 = line.p;
    const Point3D<T> p1 = line.p + line.v.normalized();
    const Point3D<T> pp0 = closestPointOnPlaneFromPoint(p0);
    const Point3D<T> pp1 = closestPointOnPlaneFromPoint(p1);
    return lineFromTwoPoints(pp0, pp1);
}

template <typename T> Point3D<T> Plane<T>::closestPointOnPlaneFromPoint(const Point3D<T>& p) const
{
    T distance_from_plane = pointDistanceFromPlane(p);

    // a*x + b*y + c*z + d = 0
    // z = -(a*x + b*y + d)/c
    // E = (x - p.x)^2 + (y - p.y)^2 + (-a*x/c - b*y/c - d/c - p.z)^2

    // [2 + 2*a0*a/c, 2*a0*b/c] [ x ] = [2*p.x - 2*a0*d/c - 2*a0*p.z]
    // [2*a1*a/c, 2 + 2*a1*b/c] [ y ] = [2*p.y - 2*a1*d/c - 2*a1*p.z]
    // TODO: Implement cases where plane is in xz or yz plane (-> xy degenerate)
    T a0 = a / c;
    T a1 = b / c;

    Matrix<T> m(2, 2);
    m(0, 0) = 2.0 + 2.0 * a0 * a / c;
    m(0, 1) = 2.0 * 2.0 * a0 * b / c;

    m(1, 0) = 2.0 * a1 * a / c;
    m(1, 1) = 2.0 + 2.0 * a1 * b / c;

    Vec2D<T> b_vec(2.0 * p.x - 2.0 * a0 * d / c - 2.0 * a0 * p.z,
                   2.0 * p.y - 2.0 * a1 * d / c - 2.0 * a1 * p.z);

    Point2D<T> sol = m.solve(b_vec);
    return Point2D<T>(sol.x, sol.y, this->evalXY(sol.x, sol.y));
}

template <typename T> T Plane<T>::pointDistanceFromPlane(const Point3D<T>& p) const
{
    Plane<T> normalized_plane = this->normalized();
    return normalized_plane.eval(p);
}

// template <typename T> Plane<T> Plane<T>::rotatePlaneAroundLine(const Line3D<T>& line) const {}
// template <typename T> Point3D<T> Plane<T>::mirroredPoint(const Point3D<T>& point) const {}
// template <typename T> Line3D<T> Plane<T>::mirroredLine(const Line3D<T>& line) const {}
// template <typename T> Plane<T> Plane<T>::mirroredPlane(const Plane<T>& plane) const {}
// template <typename T> std::pair<Point3D<T>, Point3D<T>> Plane<T>::circleIntersection(const
// Circle3D<T> circle) const {} template <typename T> Circle3D<T> Plane<T>::sphereIntersection(const
// Sphere<T>& sphere) const {} template <typename T> std::pair<Point3D<T>, Vec3D<T>>
// Plane<T>::projectPointAndVectorOntoPlane(const Point3D<T>& point, const Vec3D<T>& vec) const {}
// template <typename T> Plane<T> Plane<T>::planeIntersection(const Plane<T>& plane) const {}
template <typename T> Plane<T> Plane<T>::translatePlane(const Vec3D<T>& vec) const
{
    Plane<T> plane;

    Point3D<T> p0 = this->evalXY(1.0, 1.0) + vec;
    Point3D<T> p1 = this->evalXY(1.0, 2.0) + vec;
    Point3D<T> p2 = this->evalXY(3.0, 1.0) + vec;

    return planeFromThreePoints(p0, p1, p2);
}

template <typename T>
Plane<T> planeFromThreePoints(const Point3D<T>& p0, const Point3D<T>& p1, const Point3D<T>& p2)
{
    Vec3D<T> v10 = p1.normalizedVectorBetweenPoints(p0);
    Vec3D<T> v12 = p1.normalizedVectorBetweenPoints(p2);
    Vec3D<T> normal_vector = v10.crossProduct(v12);

    return Plane<T>(p0, normal_vector);
}

}  // namespace plot_tool

#endif
