#ifndef GRID_VECTORS_H_
#define GRID_VECTORS_H_

#include <arl/math/math.h>

enum class InteractionType
{
    UNCHANGED,
    PAN,
    ROTATE,
    RESET,
    ZOOM,
};

struct GridVectors
{
    arl::Vectord x;
    arl::Vectord y;
    arl::Vectord z;
    GridVectors(const size_t num_lines)
    {
        x.resize(num_lines);
        y.resize(num_lines);
        z.resize(num_lines);
    }
    GridVectors() = default;
    void resizeX(const size_t num_lines)
    {
        x.resize(num_lines);
    }
    void resizeY(const size_t num_lines)
    {
        y.resize(num_lines);
    }
    void resizeZ(const size_t num_lines)
    {
        z.resize(num_lines);
    }
};

#endif
