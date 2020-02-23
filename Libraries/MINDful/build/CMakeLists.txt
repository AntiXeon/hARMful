cmake_minimum_required(VERSION 3.15)

# Project declaration
project(MIND)
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

target_link_libraries(${PROJECT_NAME} DOOM)

# Versioning
if (UNIX)
    if(DEBUG)
        list(APPEND CMAKE_CXX_FLAGS "-msse4 -W -Wall -Werror -std=c++1z -g ${CMAKE_CXX_FLAGS}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-msse4 -O3 -W -Wall -Werror -std=c++1z ${CMAKE_CXX_FLAGS}")
    endif()

    set(MIND_VERSION_MAJOR 0)
    set(MIND_VERSION_MINOR 1)
    set(MIND_VERSION_PATCH 0)
    set(MIND_VERSION_STRING ${MIND_VERSION_MAJOR}.${MIND_VERSION_MINOR}.${MIND_VERSION_PATCH})

    set_target_properties (
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${MIND_VERSION_STRING}
        SOVERSION ${MIND_VERSION_MAJOR}
    )
elseif (MSVC)
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
        ADD_DEFINITIONS(/arch:SSE2)
    endif()
endif()

set (
    ${PROJECT_NAME}_DEFINITIONS
    CACHE INTERNAL "${PROJECT_NAME}: Definitions" FORCE
)

set (
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
