#include "opengl_low_level/opengl_text.h"

#include <arl/math/math.h>

#include <string>

#include "opengl_low_level/2d/opengl_2d_functions.h"
#include "opengl_low_level/opengl_header.h"

using namespace arl;

/*Vec2Dd screenToViewCoordinates(const Vec2Dd& screen_coord)
{
    Vec2Dd vret;
    const Vec2Di win_size = getWindowSize();
    const double w_x = static_cast<double>(win_size.x);
    const double w_y = static_cast<double>(win_size.y);
    vret.x = 2.0 * (screen_coord.x / w_x - 0.5);
    vret.y = 2.0 * ((w_y - screen_coord.y + 1.0) / (w_y - 1.0) - 0.5);

    return vret;
}

double calculateStringWidth(const std::string& s)
{
    int len = 0;
    for (size_t k = 0; k < s.length(); k++)
    {
        len = len + glutBitmapWidth(GLUT_BITMAP_8_BY_13, s[k]);
    }

    const double width_in_view_coords =
        1.0 + screenToViewCoordinates({static_cast<double>(len), 0}).x;

    return width_in_view_coords;
}

double calculateStringHeight()
{
    // const int height = glutBitmapHeight(GLUT_BITMAP_8_BY_13);
    const int height = 8;

    const double height_in_view_coords =
        1.0 - screenToViewCoordinates({0, static_cast<double>(height)}).y;

    return height_in_view_coords;
}

void drawTextFromBottomRight(const std::string s, float x, float y)
{
    glRasterPos2f(x - calculateStringWidth(s), y);

    for (size_t i = 0; i < s.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    }
}

void drawTextFromBottomLeft(const std::string s, float x, float y)
{
    glRasterPos2f(x, y);

    for (size_t i = 0; i < s.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    }
}

void drawTextFromTopRight(const std::string s, float x, float y)
{
    glRasterPos2f(x - calculateStringWidth(s), y - calculateStringHeight());

    for (size_t i = 0; i < s.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    }
}

void drawTextFromTopLeft(const std::string s, float x, float y)
{
    glRasterPos2f(x, y - calculateStringHeight());

    for (size_t i = 0; i < s.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
    }
}*/

void putTextAt(const std::string& s, const arl::Vec2Dd& v)
{
    putTextAt(s, v.x, v.y);
}
void putTextAt3D(const std::string& s, const arl::Vec3Dd& v)
{
    putTextAt3D(s, v.x, v.y, v.z);
}

void putTextAt(const std::string& s, const double x, const double y)
{
    glRasterPos2f(x, y);

    for (size_t i = 0; i < s.length(); i++)
    {
#ifdef PLATFORM_LINUX_M
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
#else
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
#endif
    }
}

void putTextAt3D(const std::string& s, const double x, const double y, const double z)
{
    glRasterPos3f(x, y, z);

    for (size_t i = 0; i < s.length(); i++)
    {
#ifdef PLATFORM_LINUX_M
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
#else
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
#endif
    }
}
