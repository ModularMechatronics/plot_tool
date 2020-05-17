cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(opengl-low-level CXX)

set(OPENGL_CPP_SOURCE_FILES 2d/opengl_2d_functions.cpp
                            3d/opengl_3d_functions.cpp
                            2d/opengl_2d_shape_primitives.cpp
                            3d/opengl_3d_shape_primitives.cpp
                            opengl_text.cpp)

# opengl-low-level library
add_library(opengl-low-level STATIC ${OPENGL_CPP_SOURCE_FILES})
target_link_libraries(opengl-low-level ${OPENGL_LIBRARIES}
                                       ${GLUT_LIBRARY})
