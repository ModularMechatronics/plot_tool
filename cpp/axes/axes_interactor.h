#ifndef AXES_INTERACTOR_H_
#define AXES_INTERACTOR_H_

#include <arl/math/math.h>

#include <cmath>
#include <utility>
#include <vector>

#include "axes/axes_interactor.h"
#include "axes/structures/axes_limits.h"
#include "axes/structures/axes_settings.h"
#include "axes/structures/coordinate_converter.h"
#include "axes/structures/grid_vectors.h"
#include "axes/structures/view_angles.h"
#include "io_devices/io_devices.h"

double findFirstPointInInterval(const double min_point,
                                const double max_point,
                                const double start_point,
                                const double inc);
double findFirstPointBeforeMin(const double min_point, const double start_point, const double inc);

class AxesInteractor
{
private:
    // Variables
    const double rotation_mouse_gain = 0.01;
    const double pan_mouse_gain = 0.005;
    const double zoom_mouse_gain = 0.005;

    MouseActivity current_mouse_activity;

    ViewAngles view_angles_;
    ViewAngles default_view_angles_;

    AxesLimits axes_limits_;
    AxesLimits default_axes_limits_;

    AxesSettings axes_settings_;

    CoordinateConverter coord_converter_;

    arl::Vec3Dd inc0;

    // Functions
    void changePan(const double dx, const double dy);
    void changeZoom(const double dy);
    void changeRotation(const double dx, const double dy);

public:
    AxesInteractor(const AxesSettings& axes_settings);

    void update(const InteractionType interaction_type,
                const int window_width,
                const int window_height);
    void resetView();
    void setViewAngles(const double azimuth, const double elevation);
    void setAxesLimits(const arl::Vec3Dd& min_vec, const arl::Vec3Dd& max_vec);
    void setAxesLimits(const arl::Vec2Dd& min_vec, const arl::Vec2Dd& max_vec);

    void registerMouseDragInput(const int dx, const int dy);
    void updateMouseActivity(const InteractionType interaction_type);

    GridVectors generateGridVectors();
    ViewAngles getViewAngles() const;
    AxesLimits getAxesLimits() const;
    CoordinateConverter getCoordConverter() const;
};

#endif
