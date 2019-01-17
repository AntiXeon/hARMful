cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(Images)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})

if (UNIX)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++1z ${CMAKE_CXX_FLAGS}")
    endif()
endif()

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Set the include files for the library.
include_directories (
    ${DOOM_INCLUDE_DIRS}
    ${SPITE_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${JPEGTURBO_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
)

add_executable (
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} DOOM SPITE ${SDL2_LIBRARIES})

if (UNIX)
    target_link_libraries(${PROJECT_NAME} -lstdc++fs)
endif()
