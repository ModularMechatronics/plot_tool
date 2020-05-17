#include "axes/structures/axes_settings.h"

#include <arl/math/math.h>

using namespace arl;

AxesSettings::AxesSettings()
{
    plot_box_wall_color_ = RGBTripletf(1.0f, 1.0f, 1.0f);
    plot_box_size_factor_ = 0.5;

    grid_on_ = false;
    grid_color_ = RGBTripletf(127.0f / 255.0f, 127.0f / 255.0f, 127.0f / 255.0f);

    coordinate_axes_on_ = true;
    coord_axes_extension_factor_ = 1.5;

    x_label_ = "x";
    y_label_ = "y";
    z_label_ = "z";

    num_axes_ticks_ = 4;

    axes_state_ = AxesState::DEFAULT;

    min_vec_ = Vec3Dd(-1.0, -1.0, -1.0);
    max_vec_ = Vec3Dd(1.0, 1.0, 1.0);
}

AxesSettings::AxesSettings(const Vec3Dd& min_vec, const Vec3Dd& max_vec)
{
    plot_box_wall_color_ = RGBTripletf(1.0f, 1.0f, 1.0f);
    plot_box_size_factor_ = 0.5;

    grid_on_ = false;
    grid_color_ = RGBTripletf(127.0f / 255.0f, 127.0f / 255.0f, 127.0f / 255.0f);

    coordinate_axes_on_ = true;
    coord_axes_extension_factor_ = 1.5;

    x_label_ = "x";
    y_label_ = "y";
    z_label_ = "z";

    num_axes_ticks_ = 4;

    axes_state_ = AxesState::DEFAULT;

    min_vec_ = min_vec;
    max_vec_ = max_vec;
}

double AxesSettings::getPlotBoxSizeFactor() const
{
    return plot_box_size_factor_;
}

arl::Vec3Dd AxesSettings::getMinVec() const
{
    return min_vec_;
}

arl::Vec3Dd AxesSettings::getMaxVec() const
{
    return max_vec_;
}

AxesState AxesSettings::getAxesState() const
{
    return axes_state_;
}

std::string AxesSettings::getXLabel() const
{
    return x_label_;
}

std::string AxesSettings::getYLabel() const
{
    return y_label_;
}

std::string AxesSettings::getZLabel() const
{
    return z_label_;
}

size_t AxesSettings::getNumAxesTicks() const
{
    return num_axes_ticks_;
}

RGBTripletf AxesSettings::getGridColor() const
{
    return grid_color_;
}

bool AxesSettings::getGridOn() const
{
    return grid_on_;
}

bool AxesSettings::getCoordinateAxesOn() const
{
    return coordinate_axes_on_;
}

RGBTripletf AxesSettings::getPlotBoxWallColor() const
{
    return plot_box_wall_color_;
}

double AxesSettings::getCoordAxExtFac() const
{
    return coord_axes_extension_factor_;
}
