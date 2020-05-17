cmake_minimum_required (VERSION 2.6)

project(plot-functions)

set(PLOT_FUNCTIONS_CPP_SOURCE_FILES plot_functions.cpp)

# plot-functions library
add_library(plot-functions STATIC ${PLOT_FUNCTIONS_CPP_SOURCE_FILES})
target_link_libraries(plot-functions opengl-low-level
                                     arl-color-map)

set_target_properties(plot-functions
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
               