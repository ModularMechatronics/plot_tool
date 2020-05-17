#include "axes/structures/coordinate_converter.h"

using namespace arl;

#include <cassert>

CoordinateConverter::CoordinateConverter(const Vec2Dd& window_size,
                                         const ViewAngles& view_angles,
                                         const AxesLimits& axes_limits)
    : window_size_(window_size), view_angles_(view_angles), axes_limits_(axes_limits)
{
}

void CoordinateConverter::updateInternalState(const Vec2Dd& window_size,
                                              const ViewAngles& view_angles,
                                              const AxesLimits& axes_limits)
{
    window_size_ = window_size;
    view_angles_ = view_angles;
    axes_limits_ = axes_limits;
}

Vec2Dd CoordinateConverter::orthogonalViewToModelCoordinate(const Vec2Dd& view_coord) const
{
    // Only works when azimuth = elevation = 0
    assert((view_angles_.getSnappedElevation() == 0.0) &&
           (view_angles_.getSnappedAzimuth() == 0.0));

    const Vec3Dd scale = axes_limits_.getAxesScale();
    const Vec3Dd offset = axes_limits_.getAxesCenter();
    const Vec3Dd res = Vec3Dd(view_coord.x, view_coord.y, 0.0).elementWiseMultiply(scale) + offset;

    return Vec2Dd(res.x, res.y);
}

Vec2Dd CoordinateConverter::modelToViewCoordinate(const Vec3Dd& model_coord) const
{
    const Matrixd rotation_mat = view_angles_.getSnappedRotationMatrix();
    const Vec3Dd vr = rotation_mat * model_coord;

    return Vec2Dd(vr.x, vr.y);
}

Vec2Dd CoordinateConverter::screenToViewCoordinate(const Vec2Dd& screen_coord) const
{
    const double w_x = window_size_.x;
    const double w_y = window_size_.y;

    Vec2Dd vret;

    vret.x = 2.0 * (screen_coord.x / w_x - 0.5);
    vret.y = 2.0 * ((w_y - screen_coord.y + 1.0) / (w_y - 1.0) - 0.5);

    return vret;
}

Vec2Dd CoordinateConverter::viewToScreenCoordinate(const Vec2Dd& view_coord) const
{
    const double w_x = window_size_.x;
    const double w_y = window_size_.y;

    Vec2Dd vret;
    vret.x = (view_coord.x / 2.0 + 0.5) * w_x;
    vret.y = 2.0 * w_y - ((view_coord.y / 2.0 + 0.5) * (w_y - 1.0) - 1.0 + w_y);

    return vret;
}
