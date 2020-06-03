#include "plot_functions/plot_functions.h"

#include <arl/math/math.h>
#include <arl/utilities/color_map.h>
#include <arl/utilities/logging.h>

#include "opengl_low_level/opengl_low_level.h"

using namespace arl;

void plot(const arl::Vectord& x, const arl::Vectord& y)
{
    assert(x.isAllocated() && (x.size() > 1));
    assert(y.isAllocated() && (y.size() > 1));
    drawLines2D(x, y);
}

void plot3(const arl::Vectord& x, const arl::Vectord& y, const arl::Vectord& z)
{
    assert(x.isAllocated() && (x.size() > 1));
    assert(y.isAllocated() && (y.size() > 1));
    assert(z.isAllocated() && (z.size() > 1));
    drawLines3D(x, y, z);
}

void scatter3(const arl::Vectord& x, const arl::Vectord& y, const arl::Vectord& z)
{
    assert(x.isAllocated() && (x.size() > 1));
    assert(y.isAllocated() && (y.size() > 1));
    assert(z.isAllocated() && (z.size() > 1));
    drawPoints3D(x, y, z);
}

void scatter(const arl::Vectord& x, const arl::Vectord& y)
{
    assert(x.isAllocated() && (x.size() > 1));
    assert(y.isAllocated() && (y.size() > 1));
    drawPoints2D(x, y);
}

void surf(const arl::Matrixd& x,
          const arl::Matrixd& y,
          const arl::Matrixd& z,
          const Interval1D<double> min_max_interval,
          arl::RGBColorMap<float> c_map)
{
    assert((x.rows() == y.rows()) && (x.rows() == z.rows()));
    assert((x.cols() == y.cols()) && (x.cols() == z.cols()));

    const Interval1D<double> target_interval(0.0, 1.0);

    for (size_t r = 0; r < x.rows() - 1; r++)
    {
        for (size_t c = 0; c < x.cols() - 1; c++)
        {
            const Vec3Dd c0(x(r, c), y(r, c), z(r, c));
            const Vec3Dd c1(x(r, c + 1), y(r, c + 1), z(r, c + 1));
            const Vec3Dd c2(x(r + 1, c + 1), y(r + 1, c + 1), z(r + 1, c + 1));
            const Vec3Dd c3(x(r + 1, c), y(r + 1, c), z(r + 1, c));

            const double mean_val = (y(r, c) + y(r, c + 1) + y(r + 1, c + 1) + y(r + 1, c)) * 0.25;

            const double color_val =
                arl::mapAndClampValueToInterval(mean_val, min_max_interval, target_interval);
            const RGBTripletf color = c_map(color_val);
            setColor(color);
            // setColor(input_color);
            drawPolygon3D(c0, c1, c2, c3);
        }
    }
}

void surf(const arl::Matrixd& x, const arl::Matrixd& y, const arl::Matrixd& z)
{
    assert((x.rows() == y.rows()) && (x.rows() == z.rows()));
    assert((x.cols() == y.cols()) && (x.cols() == z.cols()));

    for (size_t r = 0; r < x.rows() - 1; r++)
    {
        for (size_t c = 0; c < x.cols() - 1; c++)
        {
            const Vec3Dd c0(x(r, c), y(r, c), z(r, c));
            const Vec3Dd c1(x(r, c + 1), y(r, c + 1), z(r, c + 1));
            const Vec3Dd c2(x(r + 1, c + 1), y(r + 1, c + 1), z(r + 1, c + 1));
            const Vec3Dd c3(x(r + 1, c), y(r + 1, c), z(r + 1, c));

            drawPolygon3D(c0, c1, c2, c3);
        }
    }
}

void drawGrid3D(const arl::Matrixd& x, const arl::Matrixd& y, const arl::Matrixd& z)
{
    assert((x.rows() == y.rows()) && (x.rows() == z.rows()));
    assert((x.cols() == y.cols()) && (x.cols() == z.cols()));

    for (size_t r = 0; r < x.rows() - 1; r++)
    {
        for (size_t c = 0; c < x.cols() - 1; c++)
        {
            const Vec3Dd c0(x(r, c), y(r, c), z(r, c));
            const Vec3Dd c1(x(r, c + 1), y(r, c + 1), z(r, c + 1));
            const Vec3Dd c2(x(r + 1, c + 1), y(r + 1, c + 1), z(r + 1, c + 1));
            const Vec3Dd c3(x(r + 1, c), y(r + 1, c), z(r + 1, c));
            drawLine3D(c0, c1);
            drawLine3D(c1, c2);
            drawLine3D(c2, c3);
            drawLine3D(c3, c0);
        }
    }
}

void drawArrow3D(const arl::Point3Dd& p, const arl::Vec3Dd& v)
{
    drawLine3D(p, p + v);
}

void setColorOnChar(const char c)
{
    switch (c)
    {
        case 'r':
            setColor(1.0, 0.0, 0.0);
            break;
        case 'g':
            setColor(0.0, 1.0, 0.0);
            break;
        case 'b':
            setColor(0.0, 0.0, 1.0);
            break;
        case 'c':
            setColor(1.0, 1.0, 0.0);
            break;
        case 'm':
            setColor(1.0, 0.0, 1.0);
            break;
        case 'y':
            setColor(0.0, 1.0, 1.0);
            break;
        case 'k':
            setColor(0.0, 0.0, 0.0);
            break;
        case 'w':
            setColor(1.0, 1.0, 1.0);
            break;
        default:
            std::cout << "No color: " << c << std::endl;
            exit(-1);
            break;
    }
}
