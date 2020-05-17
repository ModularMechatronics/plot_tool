#include "axes/plot_box/plot_box_grid_numbers.h"

#include <cassert>

#include "misc/misc.h"
#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

void drawNumbersForYAxis(const Vectord& y_values,
                         const double x_offset,
                         const double z_offset,
                         const AxesLimits& axes_limits,
                         const CoordinateConverter& coord_converter)
{
    const Vec3Dd axes_center = axes_limits.getAxesCenter();
    const Vec3Dd s = axes_limits.getAxesScale();

    /*const double max_val = arl::maxAbs(y_values);
    const double min_val = arl::minAbs(y_values);

    if ((max_val > 1e4) || (min_val < 1e-4))
    {

    }*/

    for (size_t k = 0; k < y_values.size(); k++)
    {
        const Vec3Dd v(x_offset / s.x, y_values(k) / s.y, z_offset / s.z);
        const Vec2Dd vv = coord_converter.modelToViewCoordinate(v);
        putTextAt(formatNumber(y_values(k) + axes_center.y, 3), vv.x, vv.y);
    }
}

void drawNumbersForZAxis(const Vectord& z_values,
                         const double x_offset,
                         const double y_offset,
                         const AxesLimits& axes_limits,
                         const CoordinateConverter& coord_converter)
{
    const Vec3Dd axes_center = axes_limits.getAxesCenter();
    const Vec3Dd s = axes_limits.getAxesScale();

    for (size_t k = 0; k < z_values.size(); k++)
    {
        const Vec3Dd v(x_offset / s.x, y_offset / s.y, z_values(k) / s.z);
        const Vec2Dd vv = coord_converter.modelToViewCoordinate(v);
        putTextAt(formatNumber(z_values(k) + axes_center.z, 3), vv.x, vv.y);
    }
}

void drawNumbersForXAxis(const Vectord& x_values,
                         const double y_offset,
                         const double z_offset,
                         const AxesLimits& axes_limits,
                         const CoordinateConverter& coord_converter)
{
    const Vec3Dd axes_center = axes_limits.getAxesCenter();
    const Vec3Dd s = axes_limits.getAxesScale();

    for (size_t k = 0; k < x_values.size(); k++)
    {
        const Vec3Dd v(x_values(k) / s.x, y_offset / s.y, z_offset / s.z);
        const Vec2Dd vv = coord_converter.modelToViewCoordinate(v);
        putTextAt(formatNumber(x_values(k) + axes_center.x, 3), vv.x, vv.y);
    }
}

void drawAxisNumbers(const GridVectors& gv,
                     const AxesLimits& axes_limits,
                     const ViewAngles& view_angles,
                     const CoordinateConverter& coord_converter)
{
    const Vec3Dd s = axes_limits.getAxesScale();
    const double box_x = s.x;
    const double box_y = s.y;
    const double box_z = s.z;
    setColor(0.0, 0.0, 0.0);

    double x_value_to_use_vert, z_value_to_use_vert;
    double x_value_to_use, y_value_to_use, z_value_to_use;
    if (view_angles.getSnappedElevation() < 0.0)
    {
        y_value_to_use = box_y / 2.0;
    }
    else
    {
        y_value_to_use = -box_y / 2.0;
    }

    // Magic numbers are for moving text away from the plot box
    if ((view_angles.getSnappedAzimuth() > -M_PI_2) && (view_angles.getSnappedAzimuth() < M_PI_2))
    {
        z_value_to_use = -1.1 * box_z / 2.0;
    }
    else
    {
        z_value_to_use = box_z / 2.0;
    }

    if ((view_angles.getSnappedAzimuth() > 0.0) && (view_angles.getSnappedAzimuth() < M_PI))
    {
        x_value_to_use = -1.15 * box_x / 2.0;
    }
    else
    {
        x_value_to_use = 1.05 * box_x / 2.0;
    }

    // Magic numbers are for moving text away from the plot box
    if ((view_angles.getSnappedAzimuth() > 0) && (view_angles.getSnappedAzimuth() <= M_PI_2))
    {
        z_value_to_use_vert = -box_z / 2.0;
        x_value_to_use_vert = -box_x / 2.0;
    }
    else if ((view_angles.getSnappedAzimuth() > M_PI_2) &&
             (view_angles.getSnappedAzimuth() <= M_PI))
    {
        z_value_to_use_vert = -box_z / 2.0;
        x_value_to_use_vert = box_x / 2.0;
    }
    else if ((view_angles.getSnappedAzimuth() <= 0.0) &&
             (view_angles.getSnappedAzimuth() > -M_PI_2))
    {
        z_value_to_use_vert = box_z / 2.0;
        x_value_to_use_vert = -box_x / 2.0;
    }
    else
    {
        z_value_to_use_vert = box_z / 2.0;
        x_value_to_use_vert = box_x / 2.0;
    }

    drawNumbersForXAxis(gv.x, y_value_to_use, -z_value_to_use, axes_limits, coord_converter);
    drawNumbersForZAxis(gv.z, x_value_to_use, y_value_to_use, axes_limits, coord_converter);
    drawNumbersForYAxis(
        gv.y, x_value_to_use_vert, z_value_to_use_vert, axes_limits, coord_converter);
}
