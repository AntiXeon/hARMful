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

get_filename_component(DOOMFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/DOOMful ABSOLUTE)

# Set DOOMful library sources
add_subdirectory(${DOOMFUL_ABSOLUTE}/build ./build)

# Set tests executable sources
add_subdirectory(${CMAKE_SOURCE_DIR}/LogSystem/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/Chrono/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/Profiler/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/Random/build)
