#include "opengl_low_level/2d/opengl_2d_shape_primitives.h"

#include <arl/math/math.h>
#include <assert.h>

#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

#include "opengl_low_level/2d/opengl_2d_functions.h"
#include "opengl_low_level/opengl_header.h"

using namespace arl;

void drawSquare2D(const float xc, const float yc, const float r)
{
    const float r2 = r * M_SQRT2;
    glBegin(GL_LINES);
    glVertex2f(xc + r2, yc + r2);
    glVertex2f(xc - r2, yc + r2);

    glVertex2f(xc - r2, yc + r2);
    glVertex2f(xc - r2, yc - r2);

    glVertex2f(xc - r2, yc - r2);
    glVertex2f(xc + r2, yc - r2);

    glVertex2f(xc + r2, yc - r2);
    glVertex2f(xc + r2, yc + r2);
    glEnd();
}

void drawDiamond2D(const float xc, const float yc, const float r)
{
    glBegin(GL_LINES);
    glVertex2f(xc + r, yc);
    glVertex2f(xc, yc + r);

    glVertex2f(xc, yc + r);
    glVertex2f(xc - r, yc);

    glVertex2f(xc - r, yc);
    glVertex2f(xc, yc - r);

    glVertex2f(xc, yc - r);
    glVertex2f(xc + r, yc);
    glEnd();
}

void drawArrow2D(const float x0, const float y0, const float x1, const float y1)
{
    const float vx = x1 - x0;
    const float vy = y1 - y0;
    const float alpha = M_PI / 6.0f;  // 30 degrees

    const float vector_length = std::sqrt(vx * vx + vy * vy);
    const float length_percentage = 0.1;
    const float s = vector_length * length_percentage;

    const float beta = std::atan2(vy, vx);
    const float gamma = alpha - beta;
    const float theta = M_PI - gamma;
    const float phi = M_PI - (alpha + beta);
    const Vec2Dd vleft(s * std::cos(theta) + x1, s * std::sin(theta) + y1);
    const Vec2Dd vright(s * std::cos(-phi) + x1, s * std::sin(-phi) + y1);

    drawLine2D(x0, y0, x1, y1);
    drawLine2D(x1, y1, vleft.x, vleft.y);
    drawLine2D(x1, y1, vright.x, vright.y);
}

void drawArrow2D(const float x0, const float y0, const float x1, const float y1, const float s)
{
    const float vx = x1 - x0;
    const float vy = y1 - y0;
    const float alpha = M_PI / 6.0f;  // 30 degrees

    const float beta = std::atan2(vy, vx);
    const float gamma = alpha - beta;
    const float theta = M_PI - gamma;
    const float phi = M_PI - (alpha + beta);
    const Vec2Dd vleft(s * std::cos(theta) + x1, s * std::sin(theta) + y1);
    const Vec2Dd vright(s * std::cos(-phi) + x1, s * std::sin(-phi) + y1);

    drawLine2D(x0, y0, x1, y1);
    drawLine2D(x1, y1, vleft.x, vleft.y);
    drawLine2D(x1, y1, vright.x, vright.y);
}

void drawFilledCircle2D(const float xc, const float yc, const float r, const size_t num_vertices)
{
    std::vector<float> x_vals(num_vertices + 1), y_vals(num_vertices + 1);

    float phi = 0.0f;
    const float inc = M_PI * 2.0f / static_cast<float>(num_vertices);
    for (size_t k = 0; k < num_vertices; k++)
    {
        x_vals[k] = r * std::cos(phi) + xc;
        y_vals[k] = r * std::sin(phi) + yc;

        phi = phi + inc;
    }
    x_vals[num_vertices] = x_vals[0];
    y_vals[num_vertices] = y_vals[0];

    glBegin(GL_POLYGON);
    for (size_t k = 0; k < num_vertices; k++)
    {
        glVertex2f(x_vals[k], y_vals[k]);
    }

    glEnd();
}

void drawFilledRectangle2D(const float x_top_left,
                           const float y_top_left,
                           const float width,
                           const float height)
{
    glBegin(GL_QUADS);
    glVertex2f(x_top_left, y_top_left);
    glVertex2f(x_top_left + width, y_top_left);

    glVertex2f(x_top_left + width, y_top_left);
    glVertex2f(x_top_left + width, y_top_left - height);

    glVertex2f(x_top_left + width, y_top_left - height);
    glVertex2f(x_top_left, y_top_left - height);

    glVertex2f(x_top_left, y_top_left - height);
    glVertex2f(x_top_left, y_top_left);
    glEnd();
}

void drawCross2D(const float xc, const float yc, const float r)
{
    const float r2 = r * M_SQRT2;

    glBegin(GL_LINES);
    glVertex2f(xc - r2, yc - r2);
    glVertex2f(xc + r2, yc + r2);

    glVertex2f(xc - r2, yc + r2);
    glVertex2f(xc + r2, yc - r2);
    glEnd();
}

void drawPlus2D(const float xc, const float yc, const float r)
{
    glBegin(GL_LINES);
    glVertex2f(xc, yc - r);
    glVertex2f(xc, yc + r);

    glVertex2f(xc - r, yc);
    glVertex2f(xc + r, yc);
    glEnd();
}

void drawFilledTriangle2D(const float xc, const float yc, const float r)
{
    const float x0 = r * 0.8660254037844386f + xc;
    const float y0 = -r * 0.5 + yc;

    const float x1 = xc;
    const float y1 = r + yc;

    const float x2 = -r * 0.8660254037844386f + xc;
    const float y2 = -r * 0.5 + yc;

    glBegin(GL_TRIANGLES);
    glVertex2f(x0, y0);

    glVertex2f(x1, y1);

    glVertex2f(x2, y2);
    glEnd();
}

void drawDownTriangle2D(const float xc, const float yc, const float r)
{
    const float x0 = -0.86602540378443858553138321338528 * r + xc;
    const float y0 = 0.5 * r + yc;

    const float x1 = xc;
    const float y1 = -r + yc;

    const float x2 = 0.8660254037844387079960631281206 * r + xc;
    const float y2 = 0.5 * r + yc;

    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x0, y0);
    glEnd();
}

void drawLeftTriangle2D(const float xc, const float yc, const float r)
{
    const float x0 = 0.5 * r + xc;
    const float y0 = 0.86602540378443861614755319206911 * r + yc;

    const float x1 = -r + xc;
    const float y1 = +yc;

    const float x2 = 0.5 * r + xc;
    const float y2 = -0.86602540378443867737989314943677 * r + yc;

    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x0, y0);
    glEnd();
}

void drawRightTriangle2D(const float xc, const float yc, const float r)
{
    const float x0 = -0.5 * r + xc;
    const float y0 = -0.86602540378443867737989314943677 * r + yc;

    const float x1 = r + xc;
    const float y1 = yc;

    const float x2 = -0.5 * r + xc;
    const float y2 = 0.86602540378443861614755319206911 * r + yc;

    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x0, y0);
    glEnd();
}

void drawUpTriangle2D(const float xc, const float yc, const float r)
{
    const float x0 = r * 0.8660254037844386f + xc;
    const float y0 = -r * 0.5 + yc;

    const float x1 = xc;
    const float y1 = r + yc;

    const float x2 = -r * 0.8660254037844386f + xc;
    const float y2 = -r * 0.5 + yc;

    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glVertex2f(x2, y2);
    glVertex2f(x0, y0);
    glEnd();
}

void drawRectangle2D(const float x_top_left,
                     const float y_top_left,
                     const float width,
                     const float height)
{
    assert(width > 0 && "Width can't be negative!");
    assert(height > 0 && "Height can't be negative!");

    glBegin(GL_LINES);
    glVertex2f(x_top_left, y_top_left);
    glVertex2f(x_top_left + width, y_top_left);

    glVertex2f(x_top_left + width, y_top_left);
    glVertex2f(x_top_left + width, y_top_left - height);

    glVertex2f(x_top_left + width, y_top_left - height);
    glVertex2f(x_top_left, y_top_left - height);

    glVertex2f(x_top_left, y_top_left - height);
    glVertex2f(x_top_left, y_top_left);
    glEnd();
}

void drawCircle2D(const float xc, const float yc, const float r, const size_t num_vertices)
{
    Vectord x_vals(num_vertices + 1), y_vals(num_vertices + 1);

    float phi = 0.0f;
    const float inc = M_PI * 2.0f / static_cast<float>(num_vertices);
    for (size_t k = 0; k < num_vertices; k++)
    {
        x_vals(k) = r * std::cos(phi) + xc;
        y_vals(k) = r * std::sin(phi) + yc;

        phi = phi + inc;
    }
    x_vals(num_vertices) = x_vals(0);
    y_vals(num_vertices) = y_vals(0);

    drawLines2D(x_vals, y_vals);
}
