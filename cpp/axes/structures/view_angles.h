#ifndef VIEW_ANGLES_H_
#define VIEW_ANGLES_H_

#include <arl/math/math.h>

class ViewAngles
{
private:
    double azimuth_;
    double snapped_azimuth_;
    double elevation_;
    double snapped_elevation_;
    double angle_limit_;

    void setSnapAngles();
    double calcElevationSnapAngle() const;
    double calcAzimuthSnapAngle() const;

public:
    ViewAngles();
    ViewAngles(const double azimuth, const double elevation);
    ViewAngles(const double azimuth, const double elevation, const double angle_limit);
    void setAngles(const double azimuth, const double elevation);
    void changeAnglesWithDelta(const double azimuth, const double elevation);
    double getAzimuth() const;
    double getElevation() const;
    double getSnappedAzimuth() const;
    double getSnappedElevation() const;
    arl::AxisAngled getAngleAxis() const;
    arl::Matrixd getRotationMatrix() const;
    arl::AxisAngled getSnappedAngleAxis() const;
    arl::Matrixd getSnappedRotationMatrix() const;
    bool isCloseToSnap() const;
    bool bothSnappedBelowAngleLimitAroundZero() const;
    double getAngleLimit() const;
};

#endif
