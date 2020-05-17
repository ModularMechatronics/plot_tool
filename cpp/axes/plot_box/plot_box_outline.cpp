#include "axes/plot_box/plot_box_outline.h"

#include <arl/math/math.h>

#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

void drawOutline(const AxesSettings& axes_settings, const ViewAngles& view_angles)
{
    setLinewidth(1.5f);
    setColor(0.0f, 0.0f, 0.0f);
    const double width = axes_settings.getPlotBoxSizeFactor();
    const double height = axes_settings.getPlotBoxSizeFactor();
    const double depth = axes_settings.getPlotBoxSizeFactor();

    double width_to_use, height_to_use, depth_to_use;

    if ((view_angles.getSnappedAzimuth() > -M_PI_2) && (view_angles.getSnappedAzimuth() < M_PI_2))
    {
        depth_to_use = depth;
    }
    else
    {
        depth_to_use = -depth;
    }

    if ((view_angles.getSnappedAzimuth() > 0.0) && (view_angles.getSnappedAzimuth() < M_PI))
    {
        width_to_use = -width;
    }
    else
    {
        width_to_use = width;
    }

    if (view_angles.getSnappedElevation() < 0.0f)
    {
        height_to_use = height;
    }
    else
    {
        height_to_use = -height;
    }

    drawLine3D({-width, height_to_use, depth_to_use}, {width, height_to_use, depth_to_use});
    drawLine3D({width_to_use, height_to_use, -depth}, {width_to_use, height_to_use, depth});

    drawLine3D({-width, -height_to_use, -depth_to_use}, {width, -height_to_use, -depth_to_use});
    drawLine3D({-width_to_use, -height_to_use, -depth}, {-width_to_use, -height_to_use, depth});

    drawLine3D({width_to_use, height, -depth_to_use}, {width_to_use, -height, -depth_to_use});
    drawLine3D({-width_to_use, height, depth_to_use}, {-width_to_use, -height, depth_to_use});
}

void drawDottedBox(const AxesSettings& axes_settings)
{
    setLinewidth(1.0f);
    glPushAttrib(GL_ENABLE_BIT);
    setColor(0.0f, 0.0f, 0.0f);
    glLineStipple(1, 4450);
    glEnable(GL_LINE_STIPPLE);
    const double f = axes_settings.getPlotBoxSizeFactor();

    drawLine3D({-f, -f, -f}, {-f, -f, f});
    drawLine3D({-f, -f, -f}, {-f, f, -f});
    drawLine3D({-f, -f, -f}, {f, -f, -f});
    drawLine3D({f, f, f}, {f, f, -f});
    drawLine3D({f, f, f}, {f, -f, f});
    drawLine3D({f, f, f}, {-f, f, f});
    drawLine3D({-f, -f, f}, {f, -f, f});
    drawLine3D({f, -f, -f}, {f, -f, f});
    drawLine3D({f, -f, -f}, {f, f, -f});
    drawLine3D({-f, -f, f}, {-f, f, f});
    drawLine3D({-f, f, -f}, {-f, f, f});
    drawLine3D({-f, f, -f}, {f, f, -f});

    glPopAttrib();
}