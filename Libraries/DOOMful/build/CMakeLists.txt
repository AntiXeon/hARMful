cmake_minimum_required(VERSION 3.15)

# Project declaration
project(DOOM)
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
    ${CMAKE_HOME_DIRECTORY}/include
)

# Generate the output library
add_library (
    ${PROJECT_NAME}
    SHARED
    ${SOURCES}
)

set_target_properties (
    ${PROJECT_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

target_link_libraries(${PROJECT_NAME})

# Versioning
if (UNIX)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        if(DEBUG)
            list(APPEND CMAKE_CXX_FLAGS "-W -Wall -Werror -std=c++1z -g ${CMAKE_CXX_FLAGS}")
        else()
            list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++1z ${CMAKE_CXX_FLAGS}")
        endif()
    endif()

    set(DOOM_VERSION_MAJOR 0)
    set(DOOM_VERSION_MINOR 1)
    set(DOOM_VERSION_PATCH 0)
    set(DOOM_VERSION_STRING ${DOOM_VERSION_MAJOR}.${DOOM_VERSION_MINOR}.${DOOM_VERSION_PATCH})

    set_target_properties (
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${DOOM_VERSION_STRING}
        SOVERSION ${DOOM_VERSION_MAJOR}
    )
endif()

# Expose DOOM includes to other library projects.
set(
    ${PROJECT_NAME}_INCLUDE_DIRS ${CMAKE_HOME_DIRECTORY}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)
