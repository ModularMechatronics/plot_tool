#ifndef TRIANGLE_CLASS_H_
#define TRIANGLE_CLASS_H_

namespace plot_tool
{
template <typename T> struct Triangle2D
{
    Point2D<T> p0;
    Point2D<T> p1;
    Point2D<T> p2;
    Triangle2D();
    Triangle2D(const Point2D<T>& p0_, const Point2D<T>& p1_, const Point2D<T>& p2_);
};

template <typename T> struct Triangle3D
{
    Point3D<T> p0;
    Point3D<T> p1;
    Point3D<T> p2;
    Triangle3D();
    Triangle3D(const Point3D<T>& p0_, const Point3D<T>& p1_, const Point3D<T>& p2_);
};

}  // namespace plot_tool

#endif
