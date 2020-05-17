#ifndef AXES_PAINTER_H_
#define AXES_PAINTER_H_

#include <arl/math/math.h>

#include <cmath>
#include <utility>
#include <vector>

#include "axes/structures/axes_limits.h"
#include "axes/structures/axes_settings.h"
#include "axes/structures/coordinate_converter.h"
#include "axes/structures/grid_vectors.h"
#include "axes/structures/view_angles.h"
#include "opengl_low_level/opengl_low_level.h"

class AxesPainter
{
    // Variables
    ViewAngles view_angles_;
    AxesLimits axes_limits_;

    AxesSettings axes_settings_;
    CoordinateConverter coord_converter_;

    GridVectors gv_;

    // Functions
    void printViewAnglesInPlotWindow() const;

    void setOpenGLStateForPlotBox() const;
    void setOpenGLStateForAxesGrid() const;

    void drawAxesArrows() const;

    void enableClipPlanes() const;
    void disableClipPlanes() const;

public:
    void plotBegin();
    void plotEnd();

    AxesPainter() = default;
    AxesPainter(const AxesSettings& axes_settings);

    void paint(const AxesLimits& axes_limits,
               const ViewAngles& view_angles,
               const GridVectors& gv,
               const CoordinateConverter& coord_converter);
};

#endif
