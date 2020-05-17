#ifndef OPENGL_TEXT_H_
#define OPENGL_TEXT_H_

#include <arl/math/math.h>

#include <string>

/*void drawTextFromBottomRight(const std::string s, float x, float y);
void drawTextFromBottomLeft(const std::string s, float x, float y);
void drawTextFromTopRight(const std::string s, float x, float y);
void drawTextFromTopLeft(const std::string s, float x, float y);

double calculateStringWidth(const std::string& s);
double calculateStringHeight();*/

void putTextAt(const std::string& s, const arl::Vec2Dd& v);
void putTextAt3D(const std::string& s, const arl::Vec3Dd& v);
void putTextAt(const std::string& s, const double x, const double y);
void putTextAt3D(const std::string& s, const double x, const double y, const double z);

#endif
