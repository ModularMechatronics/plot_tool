#include "axes/plot_box/plot_box_coordinate_arrows.h"

#include <arl/math/math.h>

#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

void drawCoordinateAxesLines(const AxesSettings& axes_settings)
{
    glLineWidth(1.0f);
    const double ext_fac = axes_settings.getCoordAxExtFac();
    const double f = axes_settings.getPlotBoxSizeFactor();

    setColor(1.0f, 0.0f, 0.0f);
    drawLine3D({f, -f, -f}, {ext_fac * f, -f, -f});

    setColor(0.0f, 1.0f, 0.0f);
    drawLine3D({-f, f, -f}, {-f, ext_fac * f, -f});

    setColor(0.0f, 0.0f, 1.0f);
    drawLine3D({-f, -f, f}, {-f, -f, ext_fac * f});
}

void drawArrowHead(const Vec3Dd& v0, const Vec3Dd& v1, const CoordinateConverter& coord_converter)
{
    const Vec2Dd v0_2d = coord_converter.modelToViewCoordinate(v0);
    const Vec2Dd v1_2d = coord_converter.modelToViewCoordinate(v1);

    const Vec2Dd v01 = v1_2d.normalizedVectorBetweenPoints(v0_2d);

    const double arrow_angle = M_PI / 10.0;

    const Vec2Dd a0 = rotationMatrix2D(arrow_angle) * v01;
    const Vec2Dd a1 = rotationMatrix2D(-arrow_angle) * v01;

    const double f = 0.04;

    drawLine2D(v1_2d.x, v1_2d.y, v1_2d.x + a0.x * f, v1_2d.y + a0.y * f);
    drawLine2D(v1_2d.x, v1_2d.y, v1_2d.x + a1.x * f, v1_2d.y + a1.y * f);
}

void drawCoordinateArrowHead(const AxesSettings& axes_settings,
                             const CoordinateConverter& coord_conv)
{
    const double ext_fac = axes_settings.getCoordAxExtFac();

    const double f = axes_settings.getPlotBoxSizeFactor();
    const Vec3Dd x1(ext_fac * f, -f, -f);
    const Vec3Dd y1(-f, ext_fac * f, -f);
    const Vec3Dd z1(-f, -f, ext_fac * f);

    const Vec3Dd x0 = x1 - Vec3Dd(1.0, 0.0, 0.0);
    const Vec3Dd y0 = y1 - Vec3Dd(0.0, 1.0, 0.0);
    const Vec3Dd z0 = z1 - Vec3Dd(0.0, 0.0, 1.0);

    setColor(1.0, 0.0, 0.0);
    drawArrowHead(x0, x1, coord_conv);
    setColor(0.0, 1.0, 0.0);
    drawArrowHead(y0, y1, coord_conv);
    setColor(0.0, 0.0, 1.0);
    drawArrowHead(z0, z1, coord_conv);
}

void drawCoordinateAxesLetters(const AxesSettings& axes_settings,
                               const CoordinateConverter& coord_conv)
{
    // Extend a little bit (1.1) so letters are not "on" the arrow head
    const double ext_fac = axes_settings.getCoordAxExtFac() * 1.1;

    const double f = axes_settings.getPlotBoxSizeFactor();
    Vec3Dd xpos(ext_fac * f, -f, -f);
    Vec3Dd ypos(-f, ext_fac * f, -f);
    Vec3Dd zpos(-f, -f, ext_fac * f);

    const Vec2Dd x_vec = coord_conv.modelToViewCoordinate(xpos);
    const Vec2Dd y_vec = coord_conv.modelToViewCoordinate(ypos);
    const Vec2Dd z_vec = coord_conv.modelToViewCoordinate(zpos);

    setColor(0.0, 0.0, 0.0);
    putTextAt("X", x_vec.x, x_vec.y);
    putTextAt("Y", y_vec.x, y_vec.y);
    putTextAt("Z", z_vec.x, z_vec.y);
}
