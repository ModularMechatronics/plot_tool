cmake_minimum_required (VERSION 2.6)

project(axes)

set(OPENGL_CPP_SOURCE_FILES axes_interactor.cpp
                            axes_painter.cpp
                            structures/view_angles.cpp
                            structures/axes_settings.cpp
                            structures/axes_limits.cpp
                            structures/coordinate_converter.cpp
                            plot_box/plot_box_walls.cpp
                            plot_box/plot_box_outline.cpp
                            plot_box/plot_box_coordinate_arrows.cpp
                            plot_box/plot_box_grid.cpp
                            plot_box/plot_box_grid_numbers.cpp)

# axes library
add_library(axes STATIC ${OPENGL_CPP_SOURCE_FILES})
target_link_libraries(axes opengl-low-level
                           io-devices
                           plot-tool-misc)

set_target_properties(axes
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
