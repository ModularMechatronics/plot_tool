#ifndef PLOT_TOOL_BASE_TYPES_H_
#define PLOT_TOOL_BASE_TYPES_H_

#include <stdlib.h>

#include "shared/enumerations.h"

namespace plot_tool
{
constexpr char max_num_bytes = SCHAR_MAX;

struct TxPair
{
    Command command;
    char data[max_num_bytes];
    char num_bytes;
};

struct Dimension2D
{
    size_t rows;
    size_t cols;

    Dimension2D()
    {
        rows = 0;
        cols = 0;
    }

    Dimension2D(const size_t r, const size_t c)
    {
        rows = r;
        cols = c;
    }
};

struct Pos2D
{
    int x;
    int y;

    Pos2D()
    {
        x = 0;
        y = 0;
    }

    Pos2D(const int x_, const int y_)
    {
        x = x_;
        y = y_;
    }
};

struct Bound3D
{
    double x;
    double y;
    double z;
    Bound3D() {}
    Bound3D(const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_) {}
};

struct Bound2D
{
    double x;
    double y;
    Bound2D() {}
    Bound2D(const double x_, const double y_) : x(x_), y(y_) {}
};

}  // namespace plot_tool

#endif
