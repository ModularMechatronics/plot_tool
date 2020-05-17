#ifndef PLOT_BOX_GRID_H_
#define PLOT_BOX_GRID_H_

#include <arl/math/math.h>

#include "axes/structures/axes_limits.h"
#include "axes/structures/axes_settings.h"
#include "axes/structures/grid_vectors.h"
#include "axes/structures/view_angles.h"

void drawGrid(const GridVectors& gv,
              const AxesSettings& axes_settings,
              const AxesLimits& axes_limits,
              const ViewAngles& view_angles);

#endif
