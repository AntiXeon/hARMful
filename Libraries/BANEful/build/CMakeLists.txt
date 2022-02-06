cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(BANE)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
)

message(${CMAKE_HOME_DIRECTORY}/src/*.cpp)

# Set the include files for the library.
include_directories (
    ${DOOM_INCLUDE_DIRS}
    ${CMAKE_HOME_DIRECTORY}/include
)

# Generate the output library
add_library (
    ${PROJECT_NAME}
    SHARED
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} DOOM)

# Versioning
if (UNIX)
    if(DEBUG)
        list(APPEND CMAKE_CXX_FLAGS "-msse4 -W -Wall -Werror -std=c++20 -g ${CMAKE_CXX_FLAGS}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-msse4 -O3 -W -Wall -Werror -std=c++20 ${CMAKE_CXX_FLAGS}")
    endif()

    set(BANE_VERSION_MAJOR 0)
    set(BANE_VERSION_MINOR 1)
    set(BANE_VERSION_PATCH 0)
    set(BANE_VERSION_STRING ${BANE_VERSION_MAJOR}.${BANE_VERSION_MINOR}.${BANE_VERSION_PATCH})

    set_target_properties (
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${BANE_VERSION_STRING}
        SOVERSION ${BANE_VERSION_MAJOR}
    )
endif()

set (
    ${PROJECT_NAME}_DEFINITIONS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
)

set (
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
