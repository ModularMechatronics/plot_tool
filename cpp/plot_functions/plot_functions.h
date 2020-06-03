#ifndef PLOT_FUNCTIONS_H_
#define PLOT_FUNCTIONS_H_

#include <arl/math/math.h>
#include <arl/utilities/color_map.h>

#include <utility>

#include "opengl_low_level/data_structures.h"

void plot(const arl::Vectord& x, const arl::Vectord& y);
void plot3(const arl::Vectord& x, const arl::Vectord& y, const arl::Vectord& z);
void scatter3(const arl::Vectord& x, const arl::Vectord& y, const arl::Vectord& z);
void scatter(const arl::Vectord& x, const arl::Vectord& y);

void drawGrid3D(const arl::Matrixd& x, const arl::Matrixd& y, const arl::Matrixd& z);
void surf(const arl::Matrixd& x,
          const arl::Matrixd& y,
          const arl::Matrixd& z,
          const arl::Interval1D<double> min_max_interval,
          arl::RGBColorMap<float> c_map);
void surf(const arl::Matrixd& x, const arl::Matrixd& y, const arl::Matrixd& z);
void drawArrow3D(const arl::Point3Dd& p, const arl::Vec3Dd& v);
void setSettings(const std::vector<std::pair<std::string, std::string>>& settings_vector);

#endif
