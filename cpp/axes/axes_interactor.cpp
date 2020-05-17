#include "axes/axes_interactor.h"

#include <arl/math/math.h>
#include <arl/utilities/logging.h>

#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>

#include "io_devices/io_devices.h"
#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

AxesInteractor::AxesInteractor(const AxesSettings& axes_settings)
{
    ASSERT(axes_settings.getMinVec().x < axes_settings.getMaxVec().x) << "x min larger than x max!";
    ASSERT(axes_settings.getMinVec().y < axes_settings.getMaxVec().y) << "y min larger than y max!";
    ASSERT(axes_settings.getMinVec().z < axes_settings.getMaxVec().z) << "z min larger than z max!";

    axes_limits_ = AxesLimits(axes_settings.getMinVec(), axes_settings.getMaxVec());
    default_axes_limits_ = axes_limits_;

    view_angles_ = ViewAngles(-30.0 * M_PI / 180.0, 20.0 * M_PI / 180.0, 5.0 * M_PI / 180.0);
    default_view_angles_ = view_angles_;

    axes_settings_ = axes_settings;
    current_mouse_activity = MouseActivity::ROTATE;

    const size_t num_lines = axes_settings_.getNumAxesTicks();
    inc0 = 0.9999999999 * (default_axes_limits_.getMax() - default_axes_limits_.getMin()) /
           static_cast<double>(num_lines - 1);
}

void AxesInteractor::updateMouseActivity(const InteractionType interaction_type)
{
    if (interaction_type == InteractionType::PAN)
    {
        current_mouse_activity = MouseActivity::PAN;
    }
    else if (interaction_type == InteractionType::ZOOM)
    {
        current_mouse_activity = MouseActivity::ZOOM;
    }
    else if (interaction_type == InteractionType::ROTATE)
    {
        current_mouse_activity = MouseActivity::ROTATE;
    }
}

ViewAngles AxesInteractor::getViewAngles() const
{
    return view_angles_;
}

AxesLimits AxesInteractor::getAxesLimits() const
{
    return axes_limits_;
}

void AxesInteractor::update(const InteractionType interaction_type,
                            const int window_width,
                            const int window_height)
{
    if (interaction_type == InteractionType::RESET)
    {
        resetView();
    }
    else
    {
        updateMouseActivity(interaction_type);
    }

    coord_converter_.updateInternalState(
        Vec2Dd(window_width, window_height), view_angles_, axes_limits_);
}

void AxesInteractor::resetView()
{
    view_angles_ = default_view_angles_;
    axes_limits_ = default_axes_limits_;
}

void AxesInteractor::registerMouseDragInput(const int dx, const int dy)
{
    switch (current_mouse_activity)
    {
        case MouseActivity::ROTATE:
            changeRotation(dx * rotation_mouse_gain, dy * rotation_mouse_gain);
            break;
        case MouseActivity::ZOOM:
            changeZoom(dy * zoom_mouse_gain);
            break;
        case MouseActivity::PAN:
            changePan(dx * pan_mouse_gain, dy * pan_mouse_gain);
            break;
        default:
            break;
    }
}

void AxesInteractor::changeRotation(const double dx, const double dy)
{
    view_angles_.changeAnglesWithDelta(dx, dy);
}

double changeIncrement(const double scale, const double inc, const size_t num_lines)
{
    double new_inc = inc;
    if ((scale / inc) < static_cast<double>(num_lines) / 2.0)
    {
        new_inc = inc / 2.0;
    }
    else if ((scale / inc) > static_cast<double>(num_lines) * 1.0)
    {
        new_inc = inc * 2.0;
    }
    return new_inc;
}

void AxesInteractor::changeZoom(const double dy)
{
    const Vec3Dd s = axes_limits_.getAxesScale();
    const Vec3Dd inc_vec = Vec3Dd(dy * s.x, dy * s.y, dy * s.z);

    axes_limits_.setMin(axes_limits_.getMin() - inc_vec);
    axes_limits_.setMax(axes_limits_.getMax() + inc_vec);

    const size_t num_lines = axes_settings_.getNumAxesTicks();
    inc0.x = changeIncrement(s.x, inc0.x, num_lines);
    inc0.y = changeIncrement(s.y, inc0.y, num_lines);
    inc0.z = changeIncrement(s.z, inc0.z, num_lines);
}

void AxesInteractor::changePan(const double dx, const double dy)
{
    const Matrixd rotation_mat = view_angles_.getSnappedRotationMatrix();
    const Vec3Dd v = rotation_mat.getTranspose() * Vec3Dd(-dx, dy, 0.0);

    const Vec3Dd s = axes_limits_.getAxesScale();

    const Vec3Dd v_scaled = v.elementWiseMultiply(s);

    axes_limits_.incrementMinMax(v_scaled);
}

// TODO: Remove?
double findFirstPointBeforeMin(const double min_point, const double start_point, const double inc)
{
    assert(inc > 0.0);
    double t0 = start_point;
    if (start_point <= min_point)
    {
        while ((t0 + inc) < min_point)
        {
            t0 = t0 + inc;
        }
    }
    else
    {
        while (t0 > min_point)
        {
            t0 = t0 - inc;
        }
    }
    return t0;
}

// TODO: Remove?
double findFirstPointInInterval(const double min_point,
                                const double max_point,
                                const double start_point,
                                const double inc)
{
    assert(min_point < max_point);
    const double t0 = findFirstPointBeforeMin(min_point, start_point, inc);
    double new_inc = inc;
    double t1 = t0;

    while (t1 < min_point)
    {
        while (t1 < min_point)
        {
            t1 = t1 + new_inc;
        }
        if (t1 > max_point)
        {
            new_inc = new_inc * 0.5;
            t1 = t0;
        }
        else if ((t1 < max_point) && ((t1 - new_inc) > min_point))
        {
            new_inc = new_inc * 0.5;
            t1 = t0;
        }
    }

    return t1;
}

void AxesInteractor::setViewAngles(const double azimuth, const double elevation)
{
    view_angles_.setAngles(azimuth, elevation);
    default_view_angles_.setAngles(azimuth, elevation);
}

void AxesInteractor::setAxesLimits(const arl::Vec3Dd& min_vec, const arl::Vec3Dd& max_vec)
{
    axes_limits_ = AxesLimits(min_vec, max_vec);
    default_axes_limits_ = axes_limits_;

    // TODO: Remove below?
    const size_t num_lines = axes_settings_.getNumAxesTicks();
    inc0 = 0.9999999999 * (default_axes_limits_.getMax() - default_axes_limits_.getMin()) /
           static_cast<double>(num_lines - 1);
}

void AxesInteractor::setAxesLimits(const arl::Vec2Dd& min_vec, const arl::Vec2Dd& max_vec)
{
    axes_limits_ = AxesLimits({min_vec.x, min_vec.y, axes_limits_.getMin().z},
                              {max_vec.x, max_vec.y, axes_limits_.getMax().z});
    default_axes_limits_ = axes_limits_;

    const size_t num_lines = axes_settings_.getNumAxesTicks();
    inc0 = 0.9999999999 * (default_axes_limits_.getMax() - default_axes_limits_.getMin()) /
           static_cast<double>(num_lines - 1);
}

Vectord generateAxisVector(const double min_val,
                           const double max_val,
                           const double num_lines,
                           const double offset)
{
    const double d = max_val - min_val;

    const double d_inc = std::pow(2.0, std::floor(std::log2(d / num_lines)));
    double val = min_val - std::fmod(min_val, d_inc);

    std::vector<double> vec;
    vec.reserve(num_lines);

    int it = 0;

    while (val < max_val)
    {
        if (val > min_val)
        {
            vec.push_back(val - offset);
        }
        val = val + d_inc;
        it++;
        if (it > static_cast<int>(num_lines * 3))
        {
            EXIT() << "Number of lines grew a lot!";
        }
    }

    Vectord ret_vec(vec.size());
    for (size_t k = 0; k < vec.size(); k++)
    {
        ret_vec(k) = vec[k];
    }

    return ret_vec;
}

GridVectors AxesInteractor::generateGridVectors()
{
    GridVectors gv;

    const Vec3Dd v_min = axes_limits_.getMin();
    const Vec3Dd v_max = axes_limits_.getMax();

    const Vec3Dd axes_center = axes_limits_.getAxesCenter();

    gv.x = generateAxisVector(v_min.x, v_max.x, axes_settings_.getNumAxesTicks(), axes_center.x);
    gv.y = generateAxisVector(v_min.y, v_max.y, axes_settings_.getNumAxesTicks(), axes_center.y);
    gv.z = generateAxisVector(v_min.z, v_max.z, axes_settings_.getNumAxesTicks(), axes_center.z);

    return gv;
}

CoordinateConverter AxesInteractor::getCoordConverter() const
{
    return coord_converter_;
}
