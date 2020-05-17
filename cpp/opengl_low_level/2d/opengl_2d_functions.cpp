#include "opengl_low_level/2d/opengl_2d_functions.h"

#include <arl/math/math.h>
#include <assert.h>

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

#include "opengl_low_level/opengl_header.h"

using namespace arl;

void setColor(const float r, const float g, const float b)
{
    glColor3f(r, g, b);
}

void setColor(const RGBTripletf& pc)
{
    glColor3f(pc.red, pc.green, pc.blue);
}

void setLinewidth(const float line_width)
{
    glLineWidth(line_width);
}

void setPointSize(const float point_size)
{
    glPointSize(point_size);
}

void drawLine2D(const float x0, const float y0, const float x1, const float y1)
{
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

void drawLines2D(const arl::Vectord& x_values, const arl::Vectord& y_values)
{
    assert(x_values.size() > 1);
    assert(x_values.size() == y_values.size());

    glBegin(GL_LINES);
    for (size_t k = 0; k < x_values.size() - 1; k++)
    {
        glVertex2f(x_values(k), y_values(k));
        glVertex2f(x_values(k + 1), y_values(k + 1));
    }

    glEnd();
}
