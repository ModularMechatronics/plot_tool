#ifndef PLOT_TOOL_LINE_2D_CLASS_H_
#define PLOT_TOOL_LINE_2D_CLASS_H_

namespace plot_tool
{
template <typename T> struct HomogeneousLine2D
{
    T a;
    T b;
    T c;

    HomogeneousLine2D(const T a_, const T b_, const T c_);
    HomogeneousLine2D(const ParametricLine2D<T>& pl);
    HomogeneousLine2D();

    T evalX(const T x) const;
    T evalY(const T y) const;
    T eval(const Point2D<T>& p) const;
    Vec2D<T> normal() const;
    Vec2D<T> normalizedNormal() const;
    Vec2D<T> vectorAlongLine() const;

    HomogeneousLine2D<T> normalized() const;
    HomogeneousLine2D<T> negated() const;
    T pointDistanceFromLine(const Point2D<T>& p) const;
    Point2D<T> closestPointOnLineFromPoint(const Point2D<T>& p) const;
    Point2D<T> pointReflection(const Point2D<T>& p) const;
    Point2D<T> lineIntersection(const HomogeneousLine2D<T>& line) const;
    Point2D<T> lineReflection(const HomogeneousLine2D<T>& line_for_reflection) const;
    bool isOnNormalVectorSide(const Point2D<T>& p) const;
    HomogeneousLine2D<T> calculateLineRotatedAroundPoint(const Point2D<T>& p, const T angle) const;
    HomogeneousLine2D<T> translatedLine(const Vec2D<T>& v) const;
    std::pair<Point2D<T>, Vec2D<T>> projectPointAndVectorOntoLine(const Point2D<T>& p,
                                                                  const Vec2D<T>& v) const;
    T angleBetweenLines(const HomogeneousLine2D<T>& line) const;
};

template <typename T> struct ParametricLine2D
{
    // Point on line
    Point2D<T> p;

    // Vector in line direction
    Vec2D<T> v;

    ParametricLine2D(const T px_, const T py_, const T vx_, const T vy_);
    ParametricLine2D(const Point2D<T>& p_, const Vec2D<T>& v_);
    ParametricLine2D(const HomogeneousLine2D<T>& hl);
    ParametricLine2D();
    T tFromX(const T x) const;
    T tFromY(const T y) const;
    Vec2D<T> eval(const T t) const;
    ParametricLine2D<T> calculateLineRotatedAroundPoint(const Point2D<T>& q, const T angle) const;
};

}  // namespace plot_tool

#endif
