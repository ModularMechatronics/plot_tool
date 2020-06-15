#ifndef PLOT_TOOL_COMPLEX_CLASS_H_
#define PLOT_TOOL_COMPLEX_CLASS_H_

namespace plot_tool
{
template <typename T> struct ComplexCoord
{
    T real;
    T imag;

    ComplexCoord(const T real_, const T imag_);
    ComplexCoord();

    PolarCoord<T> toPolar() const;
    ComplexCoord<T> conjugate() const;
    ComplexCoord<T> inv() const;
    Vec2D<T> toVec2D() const;
    T abs() const;
};
}  // namespace plot_tool

#endif
