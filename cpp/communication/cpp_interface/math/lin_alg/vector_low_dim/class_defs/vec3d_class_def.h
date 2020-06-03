#ifndef VEC3D_CLASS_H_
#define VEC3D_CLASS_H_

namespace plot_tool
{
template <typename T> struct Vec3D
{
    T x;
    T y;
    T z;

    Vec3D(const T x_, const T y_, const T z_);
    template <typename Y> Vec3D(const Vec3D<Y>& v);
    Vec3D();
    Vec3D(const T v_array[3]);
    Vector<T> toVector() const;

    CylindricalCoord<T> toCylindricalVec() const;
    SphericalCoord<T> toSphericalCoord() const;

    Vec3D<T> normalized() const;
    Vec3D<T> vectorBetweenPoints(const Point3D<T>& end_point) const;
    Vec3D<T> normalizedVectorBetweenPoints(const Point3D<T>& end_point) const;
    T squaredNorm() const;
    T norm() const;
    Vec3D<T> elementWiseMultiply(const Vec3D<T>& factor_vector) const;
    Vec3D<T> elementWiseDivide(const Vec3D<T>& numerator_vector) const;
    Vec3D<T> crossProduct(const Vec3D<T>& right_vector) const;
    Matrix<T> toCrossProductMatrix() const;
    Matrix<T> outerProduct(const Vec3D<T>& v) const;
    Point3D<T> mirrorPointInThis(const Point3D<T>& point_to_mirror) const;
    T angleBetweenVectors(const Vec3D<T>& v) const;
    Vec3D<T> perpendicularVector() const;

    bool areAllNan() const;
    bool isAnyNan() const;
};

}  // namespace plot_tool

#endif
