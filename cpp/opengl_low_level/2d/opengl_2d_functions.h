#ifndef OPENGL_FUNCTIONS_H_
#define OPENGL_FUNCTIONS_H_

#include <arl/math/math.h>

#include <cstddef>
#include <vector>

#include "opengl_low_level/data_structures.h"

void setColor(const RGBTripletf& pc);
void setColor(const float r, const float g, const float b);

void setLinewidth(const float line_width);
void setPointSize(const float point_size);

void drawLine2D(const float x0, const float y0, const float x1, const float y1);
void drawLines2D(const arl::Vectord& x_values, const arl::Vectord& y_values);

#endif
