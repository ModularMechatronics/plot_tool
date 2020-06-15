
#ifndef PLOT_TOOL_CIRCLE_H_
#define PLOT_TOOL_CIRCLE_H_

#include <cmath>
#include <vector>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
/* **************************************************************** */
/* ************************** Section 2D ************************** */
/* **************************************************************** */
template <typename T> Circle2D<T>::Circle2D(const T radius_, const T center_x_, const T center_y_)
{
    radius = radius_;
    center.x = center_x_;
    center.y = center_y_;
}

template <typename T> Circle2D<T>::Circle2D(const T radius_, const Vec2D<T>& center_)
{
    radius = radius_;
    center.x = center_.x;
    center.y = center_.y;
}

template <typename T> Circle2D<T>::Circle2D() {}

template <typename T> HomogeneousLine2D<T> Circle2D<T>::tangentLine(const T angle) const
{
    // Computes the tangent line that touches the point P = [r*cos(angle); r*sin(angle)]
    const Point2D<T> perimiter_point = radius * Point2D<T>(std::cos(angle), std::sin(angle));
    const Vec2D<T> center_to_perimiter_vector = center.vectorBetweenPoints(perimiter_point);

    HomogeneousLine2D<T> line =
        HomogeneousLine2D<T>(center_to_perimiter_vector.x, center_to_perimiter_vector.y, 0);
    line.c = -(line.a * perimiter_point.x + line.b * perimiter_point.y);

    return line;
}

template <typename T> bool Circle2D<T>::doesLineIntersect(const HomogeneousLine2D<T>& line) const
{
    const T centerpoint_line_distance = line.pointDistanceFromLine(center);
    if (centerpoint_line_distance < radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
Point2D<T> Circle2D<T>::closestPointOnPerimeterFromPoint(const Point2D<T>& p) const
{
    const Vec2D<T> center_to_point_vector = center.normalizedVectorBetweenPoints(p);
    return center + radius * center_to_point_vector;
}

template <typename T>
std::pair<Point2D<T>, Point2D<T>> Circle2D<T>::lineIntersectionPoints(
    const HomogeneousLine2D<T>& line) const
{
    // Derived using
    // E1 = cy - sqrt(r^2 - (x - cx)^2) == -(a*x + c)/b
    // E2 = cy + sqrt(r^2 - (x - cx)^2) == -(a*x + c)/b

    std::pair<Point2D<T>, Point2D<T>> return_points;

    if (this->doesLineIntersect(line))
    {
        const T a = line.a;
        const T b = line.b;
        const T c = line.c;
        const T cx = center.x;
        const T cy = center.y;
        const T a2 = a * a;
        const T b2 = b * b;
        const T c2 = c * c;
        const T r2 = radius * radius;
        const T a2b2 = a2 + b2;
        const T cx2 = cx * cx;
        const T cy2 = cy * cy;

        // x0 = -(a*c + b*(- a^2*cx^2 + a^2*r^2 - 2*a*b*cx*cy - 2*a*c*cx - b^2*cy^2 + b^2*r^2 -
        // 2*b*c*cy - c^2)^(1/2) - b^2*cx + a*b*cy)/(a^2 + b^2);
        // x1 = -(a*c - b*(- a^2*cx^2 + a^2*r^2 - 2*a*b*cx*cy - 2*a*c*cx - b^2*cy^2 + b^2*r^2 -
        // 2*b*c*cy
        // - c^2)^(1/2) - b^2*cx + a*b*cy)/(a^2 + b^2);
        // TODO: Check content of sqrt() to make sure it isn't negative
        const T x0 =
            -(a * c +
              b * std::sqrt(-a2 * cx2 + a2 * r2 - 2.0f * a * b * cx * cy - 2.0f * a * c * cx -
                            b2 * cy2 + b2 * r2 - 2.0f * b * c * cy - c2) -
              b2 * cx + a * b * cy) /
            a2b2;
        const T x1 =
            -(a * c -
              b * std::sqrt(-a2 * cx2 + a2 * r2 - 2.0f * a * b * cx * cy - 2.0f * a * c * cx -
                            b2 * cy2 + b2 * r2 - 2.0f * b * c * cy - c2) -
              b2 * cx + a * b * cy) /
            a2b2;
        return_points.first = Point2D<T>(x0, line.evalX(x0));
        return_points.second = Point2D<T>(x1, line.evalX(x1));
    }
    else
    {
        return_points.first = Point2D<T>(NAN, NAN);
        return_points.second = Point2D<T>(NAN, NAN);
    }

    return return_points;
}

template <typename T> bool Circle2D<T>::isPointInCircle(const Point2D<T>& p) const
{
    if ((p - center).norm() < radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T> bool Circle2D<T>::doesCircleIntersect(const Circle2D<T>& circle) const
{
    // TODO: Changed to squared distance (i.e. squared norm)
    const T distance_between_centers = (circle.center - center).norm();
    if (distance_between_centers < (radius + circle.radius))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
std::pair<Point2D<T>, Point2D<T>> Circle2D<T>::circleIntersection(const Circle2D<T>& circle) const
{
    if (!doesCircleIntersect(circle))
    {
        return std::pair<Point2D<T>, Point2D<T>>(Point2D<T>(NAN, NAN), Point2D<T>(NAN, NAN));
    }
    else
    {
        const Point2D<T> c0 = center;
        const Point2D<T> c1 = circle.center;
        const T r0 = radius;
        const T r1 = circle.radius;

        const Point2D<T> s0, s1;

        s0.x =
            (c0.x * c0.y * c0.y - c0.x * c0.x * c1.x - c0.x * c1.x * c1.x + c0.x * c1.y * c1.y +
                 c1.x * c0.y * c0.y + c1.x * c1.y * c1.y - c0.x * r0 * r0 + c0.x * r1 * r1 +
                 c1.x * r0 * r0 - c1.x * r1 * r1 + c0.x * c0.x * c0.x + c1.x * c1.x * c1.x -
                 c0.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 + c1.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c0.y * c1.y - 2.0 * c1.x * c0.y * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        s1.x =
            (c0.x * c0.y * c0.y - c0.x * c0.x * c1.x - c0.x * c1.x * c1.x + c0.x * c1.y * c1.y +
                 c1.x * c0.y * c0.y + c1.x * c1.y * c1.y - c0.x * r0 * r0 + c0.x * r1 * r1 +
                 c1.x * r0 * r0 - c1.x * r1 * r1 + c0.x * c0.x * c0.x + c1.x * c1.x * c1.x +
                 c0.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - c1.y * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c0.y * c1.y - 2.0 * c1.x * c0.y * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));

        s0.y =
            (c0.x * c0.x * c0.y + c0.x * c0.x * c1.y + c1.x * c1.x * c0.y + c1.x * c1.x * c1.y -
                 c0.y * c1.y * c1.y - c0.y * c0.y * c1.y - c0.y * r0 * r0 + c0.y * r1 * r1 +
                 c1.y * r0 * r0 - c1.y * r1 * r1 + c0.y * c0.y * c0.y + c1.y * c1.y * c1.y +
                 c0.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - c1.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c1.x * c0.y - 2.0 * c0.x * c1.x * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        s1.y =
            (c0.x * c0.x * c0.y + c0.x * c0.x * c1.y + c1.x * c1.x * c0.y + c1.x * c1.x * c1.y -
                 c0.y * c1.y * c1.y - c0.y * c0.y * c1.y - c0.y * r0 * r0 + c0.y * r1 * r1 +
                 c1.y * r0 * r0 - c1.y * r1 * r1 + c0.y * c0.y * c0.y + c1.y * c1.y * c1.y -
                 c0.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                          2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                         (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                          2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 + c1.x * ((-c0.x * c0.x + 2.0 * c0.x * c1.x - c1.x * c1.x - c0.y * c0.y +
                            2.0 * c0.y * c1.y - c1.y * c1.y + r0 * r0 + 2.0 * r0 * r1 + r1 * r1) *
                           (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                            2.0 * c0.y * c1.y + c1.y * c1.y - r0 * r0 + 2.0 * r0 * r1 - r1 * r1)) ^
             0.5 - 2.0 * c0.x * c1.x * c0.y - 2.0 * c0.x * c1.x * c1.y) /
            (2.0 * (c0.x * c0.x - 2.0 * c0.x * c1.x + c1.x * c1.x + c0.y * c0.y -
                    2.0 * c0.y * c1.y + c1.y * c1.y));
        return std::pair<Point2D<T>, Point2D<T>>(s0, s1);
    }
}

/* **************************************************************** */
/* ************************** Section 3D ************************** */
/* **************************************************************** */

template <typename T>
Circle3D<T>::Circle3D(const Vec3D<T>& v_vec_, const Vec3D<T>& center_)
    : v_vec(v_vec_), center(center_)
{
    calculateOrthogonalVectors();
}

template <typename T> Circle3D<T>::Circle3D() {}

template <typename T> void Circle3D<T>::calculateOrthogonalVectors()
{
    assert(v_vec.x != 0.0 || v_vec.y != 0.0 || v_vec.z != 0.0);

    if ((v_vec.x > v_vec.y) && (v_vec.x > v_vec.z))
    {
        const T x = -(v_vec.y + v_vec.z) / v_vec.x;
        a_vec = Vec3D<T>(x, 1.0, 1.0).normalized();
    }
    else if ((v_vec.y > v_vec.x) && (v_vec.y > v_vec.z))
    {
        const T y = -(v_vec.x + v_vec.z) / v_vec.y;
        a_vec = Vec3D<T>(1.0, y, 1.0).normalized();
    }
    else
    {
        const T z = -(v_vec.x + v_vec.y) / v_vec.z;
        a_vec = Vec3D<T>(1.0, 1.0, z).normalized();
    }
    b_vec = a_vec.crossProduct(v_vec);
}

}  // namespace plot_tool

#endif
