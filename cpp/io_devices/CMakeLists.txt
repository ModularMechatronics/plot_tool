cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(io-devices CXX)

# io-devices library
add_library(io-devices STATIC mouse_state.cpp
                              keyboard_state.cpp)

set_target_properties(io-devices
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
        