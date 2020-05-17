#ifndef OPENGL_2D_SHAPE_PRIMITIVES_H_
#define OPENGL_2D_SHAPE_PRIMITIVES_H_

#include <cstddef>

void drawArrow2D(const float x0, const float y0, const float x1, const float y1);
void drawArrow2D(const float x0, const float y0, const float x1, const float y1, const float s);
void drawCross2D(const float xc, const float yc, const float r);
void drawPlus2D(const float xc, const float yc, const float r);
void drawRectangle2D(const float x_top_left,
                     const float y_top_left,
                     const float width,
                     const float height);
void drawDiamond2D(const float xc, const float yc, const float r);
void drawSquare2D(const float xc, const float yc, const float r);
void drawUpTriangle2D(const float xc, const float yc, const float r);
void drawDownTriangle2D(const float xc, const float yc, const float r);
void drawLeftTriangle2D(const float xc, const float yc, const float r);
void drawRightTriangle2D(const float xc, const float yc, const float r);
void drawCircle2D(const float xc, const float yc, const float r, const size_t num_vertices = 20);

void drawFilledCircle2D(const float xc,
                        const float yc,
                        const float r,
                        const size_t num_vertices = 20);
void drawFilledRectangle2D(const float x_top_left,
                           const float y_top_left,
                           const float width,
                           const float height);
void drawFilledTriangle2D(const float xc, const float yc, const float r);

/*void drawRotatedRectangle2D();
void drawEllipse2D();
*/

#endif
