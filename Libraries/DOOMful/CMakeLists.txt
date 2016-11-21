cmake_minimum_required(VERSION 2.6)

# Project declaration
project(DOOMful)
list(APPEND CMAKE_CXX_FLAGS "-std=c++1y ${CMAKE_CXX_FLAGS}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

# Set the include files for the library.
include_directories (
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Generate the output library
add_library (
    ${PROJECT_NAME}
    SHARED
    ${SOURCES}
)

add_library (
    ${PROJECT_NAME}_static
    STATIC
    ${SOURCES}
)
