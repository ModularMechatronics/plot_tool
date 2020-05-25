#ifndef VEC2D_CLASS_H_
#define VEC2D_CLASS_H_

namespace plot_tool
{
template <typename T> struct Vec2D
{
    T x;
    T y;

    Vec2D(const T x_, const T y_);
    Vec2D();
    Vec2D(const T v_array[2]);
    template <typename Y> Vec2D(const Vec2D<Y>& v);
    Vector<T> toVector() const;

    ComplexCoord<T> toComplex() const;
    PolarCoord<T> toPolar() const;

    Vec2D<T> normalized() const;
    Vec2D<T> vectorBetweenPoints(const Point2D<T>& end_point) const;
    Vec2D<T> normalizedVectorBetweenPoints(const Point2D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec2D<T> elementWiseMultiply(const Vec2D<T>& factor_vector) const;
    Vec2D<T> elementWiseDivide(const Vec2D<T>& numerator_vector) const;
    Matrix<T> outerProduct(const Vec2D<T>& v) const;
    Point2D<T> rotatePointAroundThis(const Point2D<T>& point_to_rotate, const T angle) const;
    Point2D<T> mirrorPointInThis(const Point2D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec2D<T>& v) const;
    T angle() const;

    bool areAllNan() const;
    bool isAnyNan() const;
};

template <typename T> struct VecXY
{
    T x;
    T y;
    VecXY() = default;
    VecXY(const T x_, const T y_) : x(x_), y(y_) {}
};

template <typename T> struct VecXZ
{
    T x;
    T z;
    VecXZ() = default;
    VecXZ(const T x_, const T z_) : x(x_), z(z_) {}
};

template <typename T> struct VecYZ
{
    T y;
    T z;
    VecYZ() = default;
    VecYZ(const T y_, const T z_) : y(y_), z(z_) {}
};

}  // namespace plot_tool

#endif
