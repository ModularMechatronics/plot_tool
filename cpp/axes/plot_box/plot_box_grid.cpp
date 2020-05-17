#include "axes/plot_box/plot_box_grid.h"

#include <cassert>

#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

void drawXZGrid(const double y_coord,
                const Vectord& x_values,
                const Vectord& z_values,
                const double x0,
                const double x1,
                const double z0,
                const double z1)
{
    assert((x_values.size()) > 0 && (z_values.size() > 0));
    for (size_t k = 0; k < x_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x_values(k), y_coord, z0), Vec3Dd(x_values(k), y_coord, z1));
    }
    for (size_t k = 0; k < z_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x0, y_coord, z_values(k)), Vec3Dd(x1, y_coord, z_values(k)));
    }
}

void drawXYGrid(const double z_coord,
                const Vectord& x_values,
                const Vectord& y_values,
                const double x0,
                const double x1,
                const double y0,
                const double y1)
{
    assert((x_values.size()) > 0 && (y_values.size() > 0));
    for (size_t k = 0; k < x_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x_values(k), y0, z_coord), Vec3Dd(x_values(k), y1, z_coord));
    }
    for (size_t k = 0; k < y_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x0, y_values(k), z_coord), Vec3Dd(x1, y_values(k), z_coord));
    }
}

void drawYZGrid(const double x_coord,
                const Vectord& y_values,
                const Vectord& z_values,
                const double y0,
                const double y1,
                const double z0,
                const double z1)
{
    assert((z_values.size()) > 0 && (y_values.size() > 0));
    for (size_t k = 0; k < y_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x_coord, y_values(k), z0), Vec3Dd(x_coord, y_values(k), z1));
    }
    for (size_t k = 0; k < z_values.size(); k++)
    {
        drawLine3D(Vec3Dd(x_coord, y0, z_values(k)), Vec3Dd(x_coord, y1, z_values(k)));
    }
}

void drawGrid(const GridVectors& gv,
              const AxesSettings& axes_settings,
              const AxesLimits& axes_limits,
              const ViewAngles& view_angles)
{
    glLineWidth(1.0f);
    setColor(axes_settings.getGridColor());

    const Vec3Dd s = axes_limits.getAxesScale();

    const double box_x_2 = s.x / 2.0f;
    const double box_y_2 = s.y / 2.0f;
    const double box_z_2 = s.z / 2.0f;

    const double azimuth = view_angles.getSnappedAzimuth();
    const double elevation = view_angles.getSnappedElevation();

    if ((azimuth > -M_PI_2) && (azimuth < M_PI_2))
    {
        drawXYGrid(-box_z_2, gv.x, gv.y, -box_x_2, box_x_2, -box_y_2, box_y_2);
    }
    else
    {
        drawXYGrid(box_z_2, gv.x, gv.y, -box_x_2, box_x_2, -box_y_2, box_y_2);
    }

    if ((azimuth > 0.0) && (azimuth < M_PI))
    {
        drawYZGrid(box_x_2, gv.y, gv.z, -box_y_2, box_y_2, -box_z_2, box_z_2);
    }
    else
    {
        drawYZGrid(-box_x_2, gv.y, gv.z, -box_y_2, box_y_2, -box_z_2, box_z_2);
    }

    if (elevation < 0.0)
    {
        drawXZGrid(box_y_2, gv.x, gv.z, -box_x_2, box_x_2, -box_z_2, box_z_2);
    }
    else
    {
        drawXZGrid(-box_y_2, gv.x, gv.z, -box_x_2, box_x_2, -box_z_2, box_z_2);
    }
}
