#include "axes/axes_painter.h"

#include <arl/utilities/logging.h>

#include "axes/plot_box/plot_box_coordinate_arrows.h"
#include "axes/plot_box/plot_box_grid.h"
#include "axes/plot_box/plot_box_grid_numbers.h"
#include "axes/plot_box/plot_box_outline.h"
#include "axes/plot_box/plot_box_walls.h"
#include "misc/misc.h"

using namespace arl;

AxesPainter::AxesPainter(const AxesSettings& axes_settings) : axes_settings_(axes_settings) {}

void drawDebugSilhouette()
{
    setColor(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    const float f = 1.0f;
    const float ymin = -1.0f;
    drawLine2D(-f, ymin, -f, f);
    drawLine2D(-f, ymin, f, ymin);

    drawLine2D(-f, f, f, f);
    drawLine2D(f, ymin, f, f);
    glLineWidth(1.0f);
}

void AxesPainter::paint(const AxesLimits& axes_limits,
                        const ViewAngles& view_angles,
                        const GridVectors& gv,
                        const CoordinateConverter& coord_converter)
{
    // TODO: Set state variable that increments for every call, and assert in the beginning
    // of every call that it has the right value (thus asserting that the call order is correct)

    axes_limits_ = axes_limits;
    view_angles_ = view_angles;
    gv_ = gv;
    coord_converter_ = coord_converter;

    // ------------

    // Plot box
    setOpenGLStateForPlotBox();

    drawPlotBoxWalls(axes_settings_, view_angles_);
    drawDottedBox(axes_settings_);
    drawOutline(axes_settings_, view_angles_);

    glPopMatrix();

    drawAxesArrows();

    setOpenGLStateForAxesGrid();

    drawGrid(gv_, axes_settings_, axes_limits_, view_angles_);

    glPopMatrix();

    drawAxisNumbers(gv_, axes_limits_, view_angles_, coord_converter_);

    printViewAnglesInPlotWindow();
    drawDebugSilhouette();
}

// TODO: Wrap 'glPopMatrix' in functions to improve consistency

void setClipPlane(const GLenum gl_plane,
                  const Point3Dd& p0,
                  const Point3Dd& p1,
                  const Point3Dd& p2,
                  const Matrixd rot_mat,
                  const bool invert)
{
    // Points are 3 points in non rotated plane
    const Point3Dd tp0 = rot_mat * p0;
    const Point3Dd tp1 = rot_mat * p1;
    const Point3Dd tp2 = rot_mat * p2;

    // Fit plane
    const Planed fp = planeFromThreePoints(tp0, tp1, tp2);

    // Invert
    const Planed plane = invert ? Planed(-fp.a, -fp.b, -fp.c, fp.d) : fp;

    // Params in "Plane" stored in same way as "double ptr[4]" (which is what "glClipPlane" expects)
    glClipPlane(gl_plane, reinterpret_cast<const double*>(&plane));
    glEnable(gl_plane);
}

void AxesPainter::enableClipPlanes() const
{
    const double f = axes_settings_.getPlotBoxSizeFactor();

    const ViewAngles view_ang(
        -view_angles_.getAzimuth(), -view_angles_.getElevation(), view_angles_.getAngleLimit());

    const Matrixd rot_mat = view_ang.getSnappedRotationMatrix();

    setClipPlane(GL_CLIP_PLANE0, {-f, 0.0, 0.0}, {-f, 1.0, 1.0}, {-f, 1.0, 0.0}, rot_mat, false);
    setClipPlane(GL_CLIP_PLANE1, {-f, 0.0, 0.0}, {-f, 1.0, 1.0}, {-f, 1.0, 0.0}, rot_mat, true);

    setClipPlane(GL_CLIP_PLANE2, {0.0, f, 0.0}, {1.0, f, 1.0}, {1.0, f, 0.0}, rot_mat, false);
    setClipPlane(GL_CLIP_PLANE3, {0.0, f, 0.0}, {1.0, f, 1.0}, {1.0, f, 0.0}, rot_mat, true);

    setClipPlane(GL_CLIP_PLANE4, {0.0, 0.0, -f}, {1.0, 1.0, -f}, {1.0, 0.0, -f}, rot_mat, false);
    setClipPlane(GL_CLIP_PLANE5, {0.0, 0.0, -f}, {1.0, 1.0, -f}, {1.0, 0.0, -f}, rot_mat, true);
}

void AxesPainter::disableClipPlanes() const
{
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
    glDisable(GL_CLIP_PLANE4);
    glDisable(GL_CLIP_PLANE5);
}

void AxesPainter::plotBegin()
{
    // Must be closed with glPopMatrix()
    // const AxisAngled ax_ang = view_angles_.getSnappedAngleAxis();
    // TODO: Why do angles need to be negated? Because matrix is not popped from drawing plot box?
    const ViewAngles view_ang(
        -view_angles_.getAzimuth(), -view_angles_.getElevation(), view_angles_.getAngleLimit());
    const AxisAngled ax_ang = view_ang.getSnappedAngleAxis();

    const Vec3Dd s = axes_limits_.getAxesScale();
    const Vec3Dd axes_center = axes_limits_.getAxesCenter();

    enableClipPlanes();

    glPushMatrix();

    glRotatef(ax_ang.phi * 180.0f / M_PI, ax_ang.x, ax_ang.y, ax_ang.z);
    // Not sure why z axis should be negated... But it works like this.
    glScaled(1.0 / s.x, 1.0 / s.y, -1.0 / s.z);
    glTranslated(-axes_center.x, -axes_center.y, axes_center.z);
}

void AxesPainter::plotEnd()
{
    disableClipPlanes();
    glPopMatrix();
}

void AxesPainter::setOpenGLStateForPlotBox() const
{
    // Must be closed with glPopMatrix()
    const AxisAngled ax_ang = view_angles_.getSnappedAngleAxis();

    glPushMatrix();

    glRotatef(ax_ang.phi * 180.0f / M_PI, ax_ang.x, ax_ang.y, ax_ang.z);
}

void AxesPainter::setOpenGLStateForAxesGrid() const
{
    // Must be closed with glPopMatrix()
    const AxisAngled ax_ang = view_angles_.getSnappedAngleAxis();

    const Vec3Dd scale = axes_limits_.getAxesScale();

    glPushMatrix();

    glRotatef(ax_ang.phi * 180.0f / M_PI, ax_ang.x, ax_ang.y, ax_ang.z);
    glScaled(1.0 / scale.x, 1.0 / scale.y, 1.0 / scale.z);
}

void AxesPainter::drawAxesArrows() const
{
    setLinewidth(1.0f);
    setOpenGLStateForPlotBox();
    drawCoordinateAxesLines(axes_settings_);
    glPopMatrix();

    drawCoordinateAxesLetters(axes_settings_, coord_converter_);
    drawCoordinateArrowHead(axes_settings_, coord_converter_);
}

void AxesPainter::printViewAnglesInPlotWindow() const
{
    setColor(0.0f, 0.0f, 0.0f);
    putTextAt(
        "(" + toStringWithNumDecimalPlaces(view_angles_.getSnappedAzimuth() * 180.0 / M_PI, 1) +
            ", " +
            toStringWithNumDecimalPlaces(view_angles_.getSnappedElevation() * 180.0 / M_PI, 1) +
            ")",
        -0.9,
        -0.9);
}
