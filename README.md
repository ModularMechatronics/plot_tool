# plot_tool
A data visualization tool to speed up the development process.

### Vision
An application runnable on different platforms, to which you can send visualization commands through IPC, from different programming languages. The only required integration to the 'Application Under Test' shall be including a header only library, thus eliminating the need for integrating and running a 'heavy' GUI/data visualization library into your application. 

### Demonstration
![](media/demo.gif)

### Example
With just a few lines of code you can bring data visualization to your application, without heavy integration of big and slow graphical frameworks.
```cpp
#include <plot_tool.h>

using namespace plot_tool;

// Establish a socket with plot_tool
initialize();  

// --- Create some arbitrary data ---

Matrix<double> x_mat;
Matrix<double> z_mat;
std::tie(x_mat, z_mat) = meshGrid(-4.0, 4.0, -4.0, 4.0, 50, 50);

Matrix<double> r = sqrt((x_mat ^ x_mat) + (z_mat ^ z_mat));
Matrix<double> y_mat = sin(2.0 * r) / r + 0.1412;

Vector<double> x = linspaceFromPointsAndCount<double>(-1.0, 1.0, 100);
Vector<double> y = sin(x * 4.0);
Vector<double> z = cos(x * 3.0 + 2.0);

// --- Visualize ---

figure(1);
holdOn();

plot3(x, y, z, Color(1.0f, 0.0f, 0.0f), Linewidth(4.0f));
scatter3(x, y, z, PointSize(13.0f), Color(0.0f, 0.5f, 1.0f));

axis({-1.0, -1.0, -1.0}, {1.0, 1.0, 1.0});


figure(2);
holdOn();

surf(x_mat, y_mat, z_mat, ColorMap(ColorMap::MAGMA));
surf(x_mat + 8.0, y_mat, z_mat + 8.0, EdgeColor(1.0f, 1.0f, 1.0f));
surf(x_mat, y_mat, z_mat + 8.0, ColorMap(ColorMap::VIRIDIS));
surf(x_mat + 8.0, y_mat, z_mat, FaceColor(0.1f, 0.5f, 0.7f));

axis({-4.0, -1.0, -12.0}, {12.0, 7.0, 4.0});

// Close the socket
deinitialize();
```

This produces the following output:
![Plot0](/media/plot01.png)

### State of the code
The code is currently a bit of a mess. C++11 is the only supported interface language for now. Looking for people who can help make it better, add functionality and clean up the code.

### License
The software is licensed with the MIT license.

### Dependencies
plot_tool uses wxWidgets for the GUI backend. This is only required for building, and not for running. The tested version is currently 3.1.3, which can be downloaded [here](https://github.com/wxWidgets/wxWidgets/releases/download/v3.1.3/wxWidgets-3.1.3.zip). It's important that wxWidgets is built with OpenGL.
Configure wxWidgets with the following command:
#### Ubuntu
```./configure --with-opengl --with-gtk=2 --disable-shared --disable-dynamicloader --without-libpng --without-libjpeg --without-libtiff --without-libjbig --enable-svg=off```

#### Mac:
```./configure --with-opengl --with-osx_cocoa --disable-shared --disable-dynamicloader --without-libpng --without-libjpeg --without-libtiff --without-libjbig --enable-svg=off```


### Platforms
The only tested platforms for now are Ubuntu 16.04 and newer version of MacOS. Pretty sure other version of Ubuntu work though.


### TODO
- Write TODO list
