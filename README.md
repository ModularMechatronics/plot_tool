# plot_tool
A data visualization tool to speed up the development process.

### Ambition
An application runnable on different platforms, to which you can send plot commands through IPC, from different programming languages. The only required integration to the 'Application Under Test' shall be including a header only library, thus eliminating the need for integrating and running a 'heavy' GUI/data visualization library into your application. 

### Demonstration
https://youtu.be/Or2qAsF1gD8

### State of the code
The code is currently a bit of a mess. Looking for people who can help make it better, add functionality and clean up the code.

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
