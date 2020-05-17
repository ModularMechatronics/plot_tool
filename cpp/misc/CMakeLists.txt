cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(plot-tool-misc CXX)

# plot-tool-misc library
add_library(plot-tool-misc STATIC number_formatting.cpp)

set_target_properties(plot-tool-misc
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
