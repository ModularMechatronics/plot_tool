cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(main-app)

set(CPP_SOURCE_FILES main.cpp
                     main_window.cpp
                     main_window_plot_handler.cpp
                     plot_window.cpp
                     plot_window_gl_pane.cpp
                     plot_data.cpp)

add_executable(plot-tool ${CPP_SOURCE_FILES})
target_link_libraries(plot-tool ${wxWidgets_LIBRARIES}
                                axes
                                plot-tool-misc
                                plot-functions
                                communication
                                io-devices)

set_target_properties(plot-tool
                      PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
