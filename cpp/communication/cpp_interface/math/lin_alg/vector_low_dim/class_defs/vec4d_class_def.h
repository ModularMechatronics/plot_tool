#ifndef PLOT_TOOL_VEC4D_CLASS_H_
#define PLOT_TOOL_VEC4D_CLASS_H_

namespace plot_tool
{
template <typename T> struct Vec4D
{
    T x;
    T y;
    T z;
    T w;

    Vec4D(const T x_, const T y_, const T z_, const T w_);
    Vec4D();
    Vec4D(const T v_array[4]);
    template <typename Y> Vec4D(const Vec4D<Y>& v);

    Vector<T> toVector() const;
    Vec4D<T> normalized() const;
    Vec4D<T> vectorBetweenPoints(const Point4D<T>& end_point) const;
    Vec4D<T> normalizedVectorBetweenPoints(const Point4D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec4D<T> elementWiseMultiply(const Vec4D<T>& factor_vector) const;
    Vec4D<T> elementWiseDivide(const Vec4D<T>& numerator_vector) const;
    Matrix<T> outerProduct(const Vec4D<T>& v) const;
    Point4D<T> mirrorPointInThis(const Point4D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec4D<T>& v) const;

    bool areAllNan() const;
    bool isAnyNan() const;
};
}  // namespace plot_tool

#endif
