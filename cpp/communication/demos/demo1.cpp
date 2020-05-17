#include <logging.h>
#include <math/math.h>
#include <plot_tool.h>
#include <unistd.h>

#include <iostream>

using namespace plot_tool;

int main()
{
    initialize();

    const double alim = 3.0;

    figure(1);
    drawPlaneXY(PointXY<double>(-2.1, -2.2),
                PointXY<double>(3.0, 3.4),
                Planed(0.1, 0.2, 0.5, 0.1),
                Color(0.1, 0.2, 0.6));
    plot_tool::axis({-alim, -alim, -alim}, {alim, alim, alim});

    figure(2);
    plot_tool::drawLine(plot_tool::Line3Dd({0.1, 0.2, 0.1}, {0.1, 0.7, 0.7}), 0.0, 1.0);
    plot_tool::axis({-alim, -alim, -alim}, {alim, alim, alim});

    figure(3);
    plot_tool::drawLineBetweenPoints(plot_tool::Point3Dd(1.0, 0.2, 0.1),
                                     plot_tool::Point3Dd(3.0, 2.1, 1.2),
                                     plot_tool::Color(0.1, 0.2, 0.5));
    plot_tool::axis({-alim, -alim, -alim}, {alim, alim, alim});

    plot_tool::deinitialize();
    return 0;
}
