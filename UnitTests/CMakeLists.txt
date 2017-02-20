cmake_minimum_required(VERSION 2.8.12)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR}../../Libraries)
set(COMMON_UNIT_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/Common/src)
set(COMMON_UNIT_TESTS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Common/include)

# Remove prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Put suffix to executable on UNIX (it will be easier to filter in .gitignore)
if (UNIX)
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
endif()

get_filename_component(DOOMFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/DOOMful ABSOLUTE)
get_filename_component(MINDFUL_ABSOLUTE ${HARMFUL_LIBS_DIR}/MINDful ABSOLUTE)

# Set hARMful libraries sources
add_subdirectory(${DOOMFUL_ABSOLUTE}/build ./build/DOOMful)
add_subdirectory(${MINDFUL_ABSOLUTE}/build ./build/MINDful)

# Set tests executable sources
add_subdirectory(${CMAKE_SOURCE_DIR}/DOOMful/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/MINDful/build)
