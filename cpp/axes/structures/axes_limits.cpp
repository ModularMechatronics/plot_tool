#include "axes/structures/axes_limits.h"

#include <arl/math/math.h>

using namespace arl;

AxesLimits::AxesLimits(const arl::Vec3Dd& min_vec, const arl::Vec3Dd& max_vec)
{
    lim_min_ = min_vec;
    tick_begin_ = min_vec;
    lim_max_ = max_vec;
}

void AxesLimits::setTickBegin(const arl::Vec3Dd& tick_begin_vec)
{
    tick_begin_ = tick_begin_vec;
}

void AxesLimits::setMin(const Vec3Dd& min_vec)
{
    lim_min_ = min_vec;
}

void AxesLimits::setMax(const Vec3Dd& max_vec)
{
    lim_max_ = max_vec;
}

void AxesLimits::incrementMinMax(const arl::Vec3Dd& dv)
{
    lim_min_ = lim_min_ + dv;
    lim_max_ = lim_max_ + dv;
}

Vec3Dd AxesLimits::getMin() const
{
    return lim_min_;
}

Vec3Dd AxesLimits::getMax() const
{
    return lim_max_;
}

arl::Vec3Dd AxesLimits::getTickBegin() const
{
    return tick_begin_;
}

Vec3Dd AxesLimits::getAxesCenter() const
{
    return (getMin() + getMax()) / 2.0;
}

Vec3Dd AxesLimits::getAxesScale() const
{
    return getMax() - getMin();
}
