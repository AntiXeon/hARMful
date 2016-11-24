cmake_minimum_required(VERSION 2.8.12)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR}../../../../Libraries)

# Remove prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

get_filename_component(DOOMFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/DOOMful ABSOLUTE)

# Set DOOMful library sources
add_subdirectory(${DOOMFUL_ABSOLUTE}/build ./build)

# Set tests executable sources
add_subdirectory(${CMAKE_SOURCE_DIR}/LogSystem/build)
