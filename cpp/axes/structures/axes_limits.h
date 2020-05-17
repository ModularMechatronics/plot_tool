#ifndef AXES_LIMITS_H_
#define AXES_LIMITS_H_

#include <arl/math/math.h>

class AxesLimits
{
private:
    arl::Vec3Dd lim_min_;
    arl::Vec3Dd lim_max_;
    arl::Vec3Dd tick_begin_;

public:
    AxesLimits() = default;
    AxesLimits(const arl::Vec3Dd& min_vec, const arl::Vec3Dd& max_vec);

    void setTickBegin(const arl::Vec3Dd& tick_begin_vec);

    void setMin(const arl::Vec3Dd& min_vec);
    void setMax(const arl::Vec3Dd& max_vec);

    void incrementMinMax(const arl::Vec3Dd& dv);

    arl::Vec3Dd getMin() const;
    arl::Vec3Dd getMax() const;

    arl::Vec3Dd getTickBegin() const;

    arl::Vec3Dd getAxesCenter() const;

    arl::Vec3Dd getAxesScale() const;
};

#endif
