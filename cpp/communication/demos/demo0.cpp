#include <logging.h>
#include <math/math.h>
#include <plot_tool.h>
#include <unistd.h>

#include <iostream>

int main()
{
    plot_tool::initialize();

    const size_t xn = 50, yn = 50;
    std::pair<plot_tool::Matrixd, plot_tool::Matrixd> mp =
        plot_tool::meshGrid(-0.7, 0.7, -0.7, 0.7, xn, yn);
    const plot_tool::Matrixd x_mat = std::move(mp.first);
    const plot_tool::Matrixd z_mat = std::move(mp.second);

    const double elevation = 20.0 * M_PI / 180.0;
    double azimuth = -30.0 * M_PI / 180.0;

    const plot_tool::Matrixd r = sqrt((x_mat ^ x_mat) + (z_mat ^ z_mat));

    double phi = 0.0;

    plot_tool::figure(1);

    double x1 = 1.0;
    for (size_t k = 0; k < 500; k++)
    {
        const plot_tool::Vector<double> x =
            plot_tool::linspaceFromPointsAndCount<double>(-1.0, x1, 100);
        const plot_tool::Vector<double> y = plot_tool::sin(x * 4.0 + phi);
        const plot_tool::Vector<double> z = plot_tool::cos(x * 3.0 + 2.0 * phi);

        const plot_tool::Matrixd y_mat = sin(20.0 * r + phi);

        plot_tool::figure(1);
        plot_tool::plot3(x, y, z);
        plot_tool::axis({-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});

        plot_tool::figure(2);
        plot_tool::surf(x_mat, y_mat, z_mat);
        plot_tool::axis({-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});

        phi = phi + 0.05;
        x1 = x1 + 0.01;

        if (k > 200)
        {
            azimuth = azimuth + 0.01;
            plot_tool::view(azimuth, elevation);
        }
        if (azimuth > M_PI)
        {
            azimuth = -2.0 * M_PI + azimuth;
        }

        usleep(1000);
    }

    plot_tool::deinitialize();
    return 0;
}
