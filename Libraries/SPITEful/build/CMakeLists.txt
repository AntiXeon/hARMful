cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(SPITE)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib/${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
)

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

# Linux dependencies
include("./LinuxDependencies.cmake")

target_link_libraries(${PROJECT_NAME} DOOM)

# Windows dependencies
include("./WindowsDependencies.cmake")

# Versioning
if (UNIX)
    target_link_libraries(${PROJECT_NAME} -lstdc++fs)

    if(DEBUG)
        list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++1z -g ${CMAKE_CXX_FLAGS}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++1z ${CMAKE_CXX_FLAGS}")
    endif()

    set(SPITE_VERSION_MAJOR 0)
    set(SPITE_VERSION_MINOR 1)
    set(SPITE_VERSION_PATCH 0)
    set(SPITE_VERSION_STRING ${SPITE_VERSION_MAJOR}.${SPITE_VERSION_MINOR}.${SPITE_VERSION_PATCH})

    set_target_properties (
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${SPITE_VERSION_STRING}
        SOVERSION ${SPITE_VERSION_MAJOR}
    )
elseif (MSVC)
   ADD_DEFINITIONS(/arch:SSE2)
endif()

set (
    ${PROJECT_NAME}_DEFINITIONS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
)

set (
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
