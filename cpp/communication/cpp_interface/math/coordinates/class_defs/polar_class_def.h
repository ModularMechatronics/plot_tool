#ifndef PLOT_TOOL_POLAR_CLASS_H_
#define PLOT_TOOL_POLAR_CLASS_H_

namespace plot_tool
{
template <typename T> struct PolarCoord
{
    T r;
    T phi;

    PolarCoord(const T r_, const T phi_);
    PolarCoord();

    ComplexCoord<T> toComplex() const;
    Vec2D<T> toVec2D() const;
};

}  // namespace plot_tool

#endif
