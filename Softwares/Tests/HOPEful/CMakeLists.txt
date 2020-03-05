cmake_minimum_required(VERSION 2.8.12)
project(HOPEfulDemo)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR}../../../../Libraries)

# The compilation may require the Conan package manager.
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_SOURCE_DIR}/conan.cmake")
endif()

include(${CMAKE_SOURCE_DIR}/conan.cmake)
option(USE_CONAN_LIBS "To know if dependencies from Conan are required" OFF)

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
get_filename_component(SPITEFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/SPITEful ABSOLUTE)
get_filename_component(HOPEFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/HOPEful ABSOLUTE)

# Set DOOMful library sources
add_definitions(-DCOMPILE_SHARED_LIBS)
add_subdirectory(${DOOMFUL_ABSOLUTE}/build ./build)
add_subdirectory(${MINDFUL_ABSOLUTE}/build ./build/MINDful)
add_subdirectory(${SPITEFUL_ABSOLUTE}/build ./build/SPITEful)
add_subdirectory(${HOPEFUL_ABSOLUTE}/build ./build/HOPEful)

# Set tests executable sources
remove_definitions(-DCOMPILE_SHARED_LIBS)
add_subdirectory(${CMAKE_SOURCE_DIR}/Rendering/build)
