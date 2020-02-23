cmake_minimum_required(VERSION 3.15)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR}../../../../Libraries)

# Remove prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Put suffix to executable on UNIX (it will be easier to filter in .gitignore)
if (UNIX)
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
endif()

# Enable the compilation with emulated SIMD when the option is ON.
option(WITH_EMULATED_SIMD "Force the compilation with emulated SIMD" OFF)
if (WITH_EMULATED_SIMD)
    add_definitions(-DFORCE_EMULATED_SIMD)
endif()

get_filename_component(DOOMFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/DOOMful ABSOLUTE)
get_filename_component(MINDFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/MINDful ABSOLUTE)

# Set DOOMful library sources
add_subdirectory(${DOOMFUL_ABSOLUTE}/build ./build)
add_subdirectory(${MINDFUL_ABSOLUTE}/build ./build/MINDful)

# Set tests executable sources
add_subdirectory(${CMAKE_SOURCE_DIR}/Performances/build)
