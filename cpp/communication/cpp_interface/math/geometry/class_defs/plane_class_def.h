#ifndef PLANE_CLASS_H_
#define PLANE_CLASS_H_

namespace plot_tool
{
template <typename T> struct Plane
{
    T a;
    T b;
    T c;
    T d;

    Plane(const T a_, const T b_, const T c_, const T d_);
    Plane(const Point3D<T>& point, const Vec3D<T>& normal_vector);
    template <typename Y> Plane(const Plane<Y>& p);
    Plane();

    Plane<T> normalized() const;
    Vec3D<T> normal() const;
    Vec3D<T> normalizedNormal() const;
    Point3D<T> lineIntersection(const Line3D<T>& line) const;
    Point3D<T> closestPointOnPlaneFromPoint(const Point3D<T>& p) const;
    T pointDistanceFromPlane(const Point3D<T>& p) const;
    T eval(const Point3D<T>& p);
    T evalXY(const T x, const T y);
    T evalXZ(const T x, const T z);
    T evalYZ(const T y, const T z);

    Plane<T> rotatePlaneAroundLine(const Line3D<T>& line) const;
    Point3D<T> mirroredPoint(const Point3D<T>& point) const;
    Line3D<T> mirroredLine(const Line3D<T>& line) const;
    Plane<T> mirroredPlane(const Plane<T>& plane) const;
    std::pair<Point3D<T>, Point3D<T>> circleIntersection(const Circle3D<T> circle) const;
    Circle3D<T> sphereIntersection(const Sphere<T>& sphere) const;
    std::pair<Point3D<T>, Vec3D<T>> projectPointAndVectorOntoPlane(const Point3D<T>& point,
                                                                   const Vec3D<T>& vec) const;
    Line3D<T> projectLineOntoPlane(const Line3D<T>& line) const;
    Plane<T> planeIntersection(const Plane<T>& plane) const;
    Plane<T> translatePlane(const Vec3D<T>& vec) const;
};
}  // namespace plot_tool

#endif
