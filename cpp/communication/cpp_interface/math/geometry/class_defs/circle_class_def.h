#ifndef CIRCLE_CLASS_H_
#define CIRCLE_CLASS_H_

#include <utility>

namespace plot_tool
{
template <typename T> struct Circle2D
{
    T radius;           // Radius
    Point2D<T> center;  // Center point

    Circle2D(const T radius_, const T center_x_, const T center_y_);
    Circle2D(const T radius_, const Vec2D<T>& center_);
    Circle2D();

    HomogeneousLine2D<T> tangentLine(const T angle) const;
    bool doesLineIntersect(const HomogeneousLine2D<T>& line) const;
    Point2D<T> closestPointOnPerimeterFromPoint(const Point2D<T>& p) const;
    std::pair<Point2D<T>, Point2D<T>> lineIntersectionPoints(
        const HomogeneousLine2D<T>& line) const;
    bool isPointInCircle(const Point2D<T>& p) const;
    bool doesCircleIntersect(const Circle2D<T>& circle) const;
    std::pair<Point2D<T>, Point2D<T>> circleIntersection(const Circle2D<T>& circle) const;
};

template <typename T> class Circle3D
{
private:
    Vec3D<T> v_vec;
    Vec3D<T> a_vec;
    Vec3D<T> b_vec;
    Point3D<T> center;
    void calculateOrthogonalVectors();

public:
    Circle3D(const Vec3D<T>& v_, const Vec3D<T>& c_);
    Circle3D();
};

}  // namespace plot_tool

#endif
