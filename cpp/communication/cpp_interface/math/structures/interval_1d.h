#ifndef PLOT_TOOL_INTERVAL_1D_H_
#define PLOT_TOOL_INTERVAL_1D_H_

#include <cmath>

namespace plot_tool
{
template <typename T> struct Interval1D
{
    T from;
    T to;

    Interval1D() = default;
    Interval1D(const T from_, const T to_) : from(from_), to(to_) {}

    T length() const;

    bool isInOpen(const T val) const;
    bool isInClosed(const T val) const;
    bool isInLeftOpen(const T val) const;
    bool isInRightOpen(const T val) const;

    bool isIncreasing() const;
};

template <typename T> bool Interval1D<T>::isIncreasing() const
{
    return from < to;
}

template <typename T> bool Interval1D<T>::isInOpen(const T val) const
{
    return (from < val) && (val < to);
}

template <typename T> bool Interval1D<T>::isInClosed(const T val) const
{
    return (from <= val) && (val <= to);
}

template <typename T> bool Interval1D<T>::isInLeftOpen(const T val) const
{
    return (from < val) && (val <= to);
}

template <typename T> bool Interval1D<T>::isInRightOpen(const T val) const
{
    return (from <= val) && (val < to);
}

template <typename T> T Interval1D<T>::length() const
{
    return std::fabs(to - from);
}

template <typename T> std::ostream& operator<<(std::ostream& os, const Interval1D<T>& interval)
{
    os << "[ " << interval.from << ", " << interval.to << " ]";
    return os;
}

template <typename T> Interval1D<T> operator-(const Interval1D<T>& interval, const T right_operand)
{
    return Interval1D<T>(interval.from - right_operand, interval.to - right_operand);
}

template <typename T> Interval1D<T> operator-(const T left_operand, const Interval1D<T>& interval)
{
    return Interval1D<T>(left_operand - interval.from, left_operand - interval.to);
}

template <typename T> Interval1D<T> operator-(const Interval1D<T>& interval)
{
    return Interval1D<T>(-interval.from, -interval.to);
}

template <typename T> Interval1D<T> operator+(const Interval1D<T>& interval, const T right_operand)
{
    return Interval1D<T>(interval.from + right_operand, interval.to + right_operand);
}

template <typename T> Interval1D<T> operator+(const T left_operand, const Interval1D<T>& interval)
{
    return Interval1D<T>(left_operand + interval.from, left_operand + interval.to);
}

template <typename T> Interval1D<T> operator*(const Interval1D<T>& interval, const T right_operand)
{
    return Interval1D<T>(interval.from * right_operand, interval.to * right_operand);
}

template <typename T> Interval1D<T> operator*(const T left_operand, const Interval1D<T>& interval)
{
    return Interval1D<T>(left_operand * interval.from, left_operand * interval.to);
}

template <typename T> Interval1D<T> operator/(const Interval1D<T>& interval, const T right_operand)
{
    return Interval1D<T>(interval.from / right_operand, interval.to / right_operand);
}

template <typename T>
T mapValueToInterval(const T value,
                     const Interval1D<T>& value_interval,
                     const Interval1D<T>& target_interval)
{
    // 'value' is in [value_interval.from, value_interval.to]
    // map 'value' to [target_interval.from, target_interval.to]
    const T mapped_value = (value - value_interval.from) / value_interval.length();
    const T target_value = mapped_value * target_interval.length() + target_interval.from;
    return target_value;
}

template <typename T>
T mapAndClampValueToInterval(const T value,
                             const Interval1D<T>& value_interval,
                             const Interval1D<T>& target_interval)
{
    // 'value' is in [value_interval.from, value_interval.to]
    // map 'value' to [target_interval.from, target_interval.to]
    const T mapped_value = (value - value_interval.from) / value_interval.length();
    const T clamped_value =
        std::min(std::max(value_interval.from, mapped_value), value_interval.to);
    const T target_value = clamped_value * target_interval.length() + target_interval.from;
    return target_value;
}

}  // namespace plot_tool

#endif
