
#ifndef PLOT_TOOL_MATH_CORE_H_
#define PLOT_TOOL_MATH_CORE_H_

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "logging.h"
#include "math/misc/math_macros.h"

namespace plot_tool
{
template <typename T> struct Vec2D;
template <typename T> struct Vec3D;
template <typename T> struct Vec4D;

template <typename T> struct VecXY;
template <typename T> struct VecXZ;
template <typename T> struct VecYZ;

template <typename T> class Vector;
template <typename T> class Matrix;

template <typename T> struct ComplexCoord;
template <typename T> struct PolarCoord;
template <typename T> struct CylindricalCoord;
template <typename T> struct SphericalCoord;

template <typename T> class Circle3D;
template <typename T> struct Circle2D;
template <typename T> struct Line3D;
template <typename T> struct ParametricLine2D;
template <typename T> struct HomogeneousLine2D;
template <typename T> struct Plane;
template <typename T> struct Sphere;

template <typename T> struct Quaternion;
template <typename T> struct RollPitchYaw;
template <typename T> struct AxisAngle;
template <typename T> class PoseSE3;

template <typename T> struct Rect2D;
template <typename T> class PolygonNVertices2D;
template <typename T> class PolygonNVertices3D;
template <typename T> class OrderedSet3D;
template <typename T> class OrderedSet2D;
template <typename T> struct Triangle2D;
template <typename T> struct Triangle3D;

template <typename T> struct Interval1D;
struct IndexSpan;
struct EndIndex;

template <typename T> using Point2D = Vec2D<T>;
template <typename T> using Point3D = Vec3D<T>;
template <typename T> using Point4D = Vec4D<T>;
template <typename T> using Point = Vector<T>;

template <typename T> using PointXY = VecXY<T>;
template <typename T> using PointXZ = VecXZ<T>;
template <typename T> using PointYZ = VecYZ<T>;

}  // namespace plot_tool

// clang-format off
#include "math/lin_alg/matrix_dynamic/class_defs/matrix_dynamic_class_def.h"
#include "math/lin_alg/vector_dynamic/class_defs/vector_dynamic_class_def.h"
#include "math/lin_alg/vector_low_dim/class_defs/vec2d_class_def.h"
#include "math/lin_alg/vector_low_dim/class_defs/vec3d_class_def.h"
#include "math/lin_alg/vector_low_dim/class_defs/vec4d_class_def.h"

#include "math/geometry/class_defs/line_2d_class_def.h"
#include "math/geometry/class_defs/line_3d_class_def.h"
#include "math/geometry/class_defs/plane_class_def.h"

#include "math/transformations/class_defs/axis_angle_class_def.h"
#include "math/transformations/class_defs/pose_class_def.h"
#include "math/transformations/class_defs/quaternion_class_def.h"
#include "math/transformations/class_defs/roll_pitch_yaw_class_def.h"

#include "math/structures/end_index.h"
#include "math/structures/index_span.h"
#include "math/structures/interval_1d.h"
// clang-format on

#endif
