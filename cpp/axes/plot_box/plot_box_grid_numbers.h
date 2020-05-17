#ifndef PLOT_BOX_GRID_NUMBERS_H_
#define PLOT_BOX_GRID_NUMBERS_H_

#include <arl/math/math.h>

#include "axes/structures/axes_limits.h"
#include "axes/structures/coordinate_converter.h"
#include "axes/structures/grid_vectors.h"
#include "axes/structures/view_angles.h"

void drawAxisNumbers(const GridVectors& gv,
                     const AxesLimits& axes_limits,
                     const ViewAngles& view_angles,
                     const CoordinateConverter& coord_converter);

#endif
