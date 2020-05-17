cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(plot_tool CXX)


# *****************************
# ********* Set flags *********
# *****************************

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings -Wno-deprecated \
    -Wall -Wextra -pedantic -fdiagnostics-color")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -std=c++11 -fPIC")

set(TOP_LEVEL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# **********************************
# ********* Set build type *********
# **********************************

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG")
endif()

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    message("")
    message("BUILD TYPE IS DEBUG")
    message("")
    set(OUTPUT_BUILD_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/debug")
    execute_process (COMMAND bash -c "rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/release")
    
else()
    message("")
    message("BUILD TYPE IS RELEASE")
    message("")
    set(OUTPUT_BUILD_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/release")
    execute_process (COMMAND bash -c "rm -rf ${CMAKE_CURRENT_SOURCE_DIR}/debug")
endif()

execute_process (COMMAND bash -c "mkdir -p ${OUTPUT_BUILD_DIRECTORY}")

# *********************************************
# ********* Platform macro definition *********
# *********************************************

if(UNIX AND NOT APPLE)
    set(PLATFORM_LINUX TRUE)
    add_compile_definitions(PLATFORM_LINUX_M)
elseif(APPLE)
    set(PLATFORM_APPLE TRUE)
    add_compile_definitions(PLATFORM_APPLE_M)
elseif(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    add_compile_definitions(PLATFORM_WINDOWS_M)
else()
    message(FATAL_ERROR "Unknown platform!" )
endif()


# *********************************
# ********* Find packages *********
# *********************************

# ****** OpenGL ******
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

# ****** Eigen ******
find_package(Eigen3 REQUIRED)

# ****** wxWidgets ******
find_package(wxWidgets COMPONENTS core base gl)

# ***************************************
# ********* Include directories *********
# ***************************************

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${EIGEN3_INCLUDE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/gtest/googletest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/arl/include)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${wxWidgets_INCLUDE_DIRS})
include_directories(${TOP_LEVEL_SOURCE_DIR}/communication)

# ************************************
# ********* Link directories *********
# ************************************
link_directories(${OUTPUT_BUILD_DIRECTORY})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/gtest/build/lib)
link_directories(${wxWidgets_LIBRARY_DIRS})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/arl/build/source/utilities/color_map/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/arl/build/source/utilities/misc/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/arl/build/source/utilities/string/)

# ***************************************
# ********* Include cmake files *********
# ***************************************
include(${wxWidgets_USE_FILE})

# *****************************************
# ********* Adding subdirectories *********
# *****************************************

# ****** Libraries ******
add_subdirectory(misc)
add_subdirectory(communication)
add_subdirectory(axes)
add_subdirectory(opengl_low_level)
add_subdirectory(plot_functions)
add_subdirectory(io_devices)

# ****** Main application ******
add_subdirectory(main_application)
