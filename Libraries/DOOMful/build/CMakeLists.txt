cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(DOOMful)
list(APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
set(CMAKE_HOME_DIRECTORY ..)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
)

# Set the include files for the library.
include_directories (
    ${CMAKE_HOME_DIRECTORY}/include
)

# Generate the output library
add_library (
    ${PROJECT_NAME}
    SHARED
    ${SOURCES}
)

# Expose DOOMful includes to other library projects.
set(
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
