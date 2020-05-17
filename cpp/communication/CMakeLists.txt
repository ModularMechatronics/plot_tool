cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(communication CXX)

set(CLIENT_SERVER_SOURCE_FILES server.cpp)

# client_server library
add_library(communication STATIC ${CLIENT_SERVER_SOURCE_FILES})
target_link_libraries(communication pthread)

set_target_properties(communication
                      PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_BUILD_DIRECTORY}")
