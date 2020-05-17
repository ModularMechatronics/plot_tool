FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install build-essential vim wget -y

RUN mkdir -p /home/deps
WORKDIR /home/deps/

RUN wget https://github.com/Kitware/CMake/archive/v3.15.4.tar.gz && tar -xvzf v3.15.4.tar.gz 

WORKDIR /home/deps/CMake-3.15.4
RUN ./bootstrap
RUN make -j5 && make install

RUN apt-get install libeigen3-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev -y

WORKDIR /home/deps
RUN wget https://github.com/wxWidgets/wxWidgets/archive/v3.1.3.tar.gz && tar -xvzf v3.1.3.tar.gz
WORKDIR /home/deps/wxWidgets-3.1.3
RUN mkdir build_tmp
WORKDIR /home/deps/wxWidgets-3.1.3/build_tmp


RUN apt-get update && apt-get install libgtk2.0-dev -y

RUN ../configure --with-opengl --with-gtk=2 --without-libjpeg --without-libpng --without-libtiff --disable-svg
RUN make -j5
RUN make install
