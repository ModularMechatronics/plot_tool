#include <logging.h>
#include <math/math.h>
#include <plot_tool.h>
#include <unistd.h>
#include <iostream>
#include <tuple>
#include <utility>

using namespace plot_tool;

int main()
{
    initialize();

    figure(1);

    Matrix<double> x_mat;
    Matrix<double> z_mat;
    std::tie(x_mat, z_mat) = meshGrid(-4.0, 4.0, -4.0, 4.0, 50, 50);

    Matrix<double> r = sqrt((x_mat ^ x_mat) + (z_mat ^ z_mat));
    Matrix<double> y_mat = sin(2.0 * r) / r + 0.1412;

    Vector<double> x = linspaceFromPointsAndCount<double>(-1.0, 1.0, 100);
    Vector<double> y = sin(x * 4.0);
    Vector<double> z = cos(x * 3.0 + 2.0);

    figure(1);
    clearFigure();
    holdOn();
    plot3(x, y, z, Color(1.0f, 0.0f, 0.0f), Linewidth(4.0f));
    scatter3(x, y, z, PointSize(13.0f), Color(0.0f, 0.5f, 1.0f));
    axis({-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});

    figure(2);
    clearFigure();
    holdOn();
    surf(x_mat, y_mat, z_mat, ColorMap(ColorMap::MAGMA));
    surf(x_mat + 8.0, y_mat, z_mat + 8.0, EdgeColor(1.0f, 1.0f, 1.0f));
    surf(x_mat, y_mat, z_mat + 8.0, ColorMap(ColorMap::VIRIDIS));
    surf(x_mat + 8.0, y_mat, z_mat, FaceColor(0.1f, 0.5f, 0.7f));
    axis({-4.0, -1.0, -12.0}, {12.0, 7.0, 4.0});

    deinitialize();
    return 0;
}
