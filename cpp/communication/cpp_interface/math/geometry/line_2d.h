
#ifndef PLOT_TOOL_LINE_2D_H_
#define PLOT_TOOL_LINE_2D_H_

#include <cmath>
#include <utility>

#include "logging.h"
#include "math/lin_alg.h"
#include "math/math_core.h"

namespace plot_tool
{
template <typename T>
HomogeneousLine2D<T>::HomogeneousLine2D(const T a_, const T b_, const T c_) : a(a_), b(b_), c(c_)
{
}

template <typename T> HomogeneousLine2D<T>::HomogeneousLine2D(const ParametricLine2D<T>& pl)
{
    a = -pl.v.y;
    b = pl.v.x;
    c = -(a * pl.p.x + b * pl.p.y);
}

template <typename T> HomogeneousLine2D<T>::HomogeneousLine2D() {}

template <typename T> Vec2D<T> HomogeneousLine2D<T>::normal() const
{
    const Vec2D<T> v(a, b);
    if (v.y < 0.0)
    {
        return -v;
    }
    else
    {
        return v;
    }
}

template <typename T> Vec2D<T> HomogeneousLine2D<T>::normalizedNormal() const
{
    const Vec2D<T> v(a, b);
    if (v.y < 0.0)
    {
        return -v.normalized();
    }
    else
    {
        return v.normalized();
    }
}

template <typename T> Vec2D<T> HomogeneousLine2D<T>::vectorAlongLine() const
{
    const Vec2D<T> v(-b, a);
    if (v.x < 0.0)
    {
        return -v;
    }
    else
    {
        return v;
    }
}

template <typename T> T HomogeneousLine2D<T>::evalX(const T x) const
{
    return -(a * x + c) / b;
}

template <typename T> T HomogeneousLine2D<T>::evalY(const T y) const
{
    return -(b * y + c) / a;
}

template <typename T> T HomogeneousLine2D<T>::eval(const Point2D<T>& p) const
{
    return a * p.x + b * p.y + c;
}

template <typename T> HomogeneousLine2D<T> HomogeneousLine2D<T>::normalized() const
{
    const T d = std::sqrt(a * a + b * b);
    return HomogeneousLine2D<T>(a / d, b / d, c / d);
}

template <typename T> HomogeneousLine2D<T> HomogeneousLine2D<T>::negated() const
{
    return HomogeneousLine2D<T>(-a, -b, -c);
}

template <typename T> T HomogeneousLine2D<T>::pointDistanceFromLine(const Point2D<T>& p) const
{
    const HomogeneousLine2D<T> normalized_line = this->normalized();
    return std::fabs(normalized_line.eval(p));
}

template <typename T>
Point2D<T> HomogeneousLine2D<T>::closestPointOnLineFromPoint(const Point2D<T>& p) const
{
    const T x = -(-p.x * b * b + a * p.y * b + a * c) / (a * a + b * b);

    return Point2D<T>(x, evalX(x));
}

template <typename T> Point2D<T> HomogeneousLine2D<T>::pointReflection(const Point2D<T>& p) const
{
    const Point2D<T> closest_point = this->closestPointOnLineFromPoint(p);
    const Vec2D<T> line_normal = closest_point.vectorBetweenPoints(p);
    const Point2D<T> reflected_point = closest_point - line_normal;
    return reflected_point;
}

template <typename T>
Point2D<T> HomogeneousLine2D<T>::lineIntersection(const HomogeneousLine2D<T>& line) const
{
    return Point2D<T>((b * line.c - line.b * c) / (a * line.b - line.a * b),
                      -(a * line.c - line.a * c) / (a * line.b - line.a * b));
}

template <typename T>
Point2D<T> HomogeneousLine2D<T>::lineReflection(
    const HomogeneousLine2D<T>& line_for_reflection) const
{
    // Reflects the input line in this line
    const Point2D<T> intersection_point = this->lineIntersection(line_for_reflection);

    const Vec2D<T> vec_along_line = Vec2D<T>(-b, a).normalized();
    const Point2D<T> point_to_reflect = intersection_point + vec_along_line;
    const Point2D<T> reflected_point = this->pointReflection(point_to_reflect);
    const HomogeneousLine2D<T> reflected_line =
        homogeneousLineFromPoints(intersection_point, reflected_point);

    return reflected_line;
}

template <typename T> bool HomogeneousLine2D<T>::isOnNormalVectorSide(const Point2D<T>& p) const
{
    // Returns true if p is on the same side as the side that the normal
    // vector of the line extends into (i.e. points towards)
    return this->eval(p) > 0;
}

template <typename T>
HomogeneousLine2D<T> HomogeneousLine2D<T>::calculateLineRotatedAroundPoint(const Point2D<T>& p,
                                                                           const T angle) const
{
    const ParametricLine2D<T> p_line(*this);
    const Matrix<T> rot_mat = rotationMatrix2D(angle);

    const Point2D<T> p0 = p_line.eval(0.0) - p;
    const Point2D<T> p1 = p_line.eval(1.0) - p;

    const Point2D<T> p0r = rot_mat * p0 + p;
    const Point2D<T> p1r = rot_mat * p1 + p;

    return homogeneousLineFromPoints(p0r, p1r);
}

template <typename T>
HomogeneousLine2D<T> HomogeneousLine2D<T>::translatedLine(const Vec2D<T>& v) const
{
    const ParametricLine2D<T> p_line(*this);

    const Point2D<T> p0 = p_line.eval(0.0) + v;
    const Point2D<T> p1 = p_line.eval(1.0) + v;

    return homogeneousLineFromPoints(p0, p1);
}

template <typename T>
std::pair<Point2D<T>, Vec2D<T>> HomogeneousLine2D<T>::projectPointAndVectorOntoLine(
    const Point2D<T>& p, const Vec2D<T>& v) const
{
    const Point2D<T> p0 = this->closestPointOnLineFromPoint(p);
    const Point2D<T> p1 = this->closestPointOnLineFromPoint(p + v);

    const std::pair<Point2D<T>, Vec2D<T>> point_vector_pair(p0, p0.vectorBetweenPoints(p1));
    return point_vector_pair;
}

template <typename T>
T HomogeneousLine2D<T>::angleBetweenLines(const HomogeneousLine2D<T>& line) const
{
    return this->vectorAlongLine().angleBetweenVectors(line.vectorAlongLine());
}

// Non class functions

template <typename T> HomogeneousLine2D<T> lineFromPointAndAngle(const Point2D<T>& p, const T angle)
{
    const Vec2D<T> v(std::cos(angle), std::sin(angle));
    const ParametricLine2D<T> parametric_line(p, v);

    const HomogeneousLine2D<T> line = parametric_line;

    return line;
}

template <typename T>
HomogeneousLine2D<T> homogeneousLineFromPointAndVector(const Point2D<T>& p, const Vec2D<T>& v)
{
    HomogeneousLine2D<T> line;
    line.a = -v.y;
    line.b = v.x;
    line.c = -(line.a * p.x + line.b * p.y);

    return line;
}

template <typename T>
HomogeneousLine2D<T> homogeneousLineFromPoints(const Point2D<T>& p0, const Point2D<T>& p1)
{
    const Vec2D<T> v = p1 - p0;
    const ParametricLine2D<T> line_p(p0, v);

    return HomogeneousLine2D<T>(line_p);
}

// ParametricLine2D

template <typename T>
ParametricLine2D<T>::ParametricLine2D(const T px_, const T py_, const T vx_, const T vy_)
{
    p.x = px_;
    p.y = py_;
    v.x = vx_;
    v.y = vy_;
}

template <typename T>
ParametricLine2D<T>::ParametricLine2D(const Point2D<T>& p_, const Vec2D<T>& v_)
{
    p = p_;
    v = v_;
}

template <typename T> ParametricLine2D<T>::ParametricLine2D(const HomogeneousLine2D<T>& hl)
{
    v.x = -hl.b;
    v.y = hl.a;

    if (std::fabs(hl.b) > std::fabs(hl.a))
    {
        const T x = 1.0;
        const T y = -(hl.a * x + hl.c) / hl.b;
        p.x = x;
        p.y = y;
    }
    else
    {
        const T y = 1.0;
        const T x = -(hl.b * y + hl.c) / hl.a;
        p.x = x;
        p.y = y;
    }
}

template <typename T> ParametricLine2D<T>::ParametricLine2D() {}

template <typename T> T ParametricLine2D<T>::tFromX(const T x) const
{
    return (x - p.x) / v.x;
}

template <typename T> T ParametricLine2D<T>::tFromY(const T y) const
{
    return (y - p.y) / v.y;
}

template <typename T> Vec2D<T> ParametricLine2D<T>::eval(const T t) const
{
    return p + t * v;
}

template <typename T>
ParametricLine2D<T> ParametricLine2D<T>::calculateLineRotatedAroundPoint(const Point2D<T>& q,
                                                                         const T angle) const
{
    Matrix<T> rot_mat = rotationMatrix2D(angle);

    Point2D<T> p0 = eval(0.0) - q;
    Point2D<T> p1 = eval(1.0) - q;

    Point2D<T> p0r = rot_mat * p0 + q;
    Point2D<T> p1r = rot_mat * p1 + q;

    return parametricLineFromPoints(p0r, p1r);
}

template <typename T>
ParametricLine2D<T> parametricLineFromPoints(const Point2D<T>& p0, const Point2D<T>& p1)
{
    const Vec2D<T> v = p1 - p0;
    v = p1 - p0;
    return ParametricLine2D<T>(p0, v);
}

}  // namespace plot_tool

#endif
