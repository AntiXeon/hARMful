cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(glsl2cpp)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})

if (UNIX)
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")

    if(DEBUG)
        list(APPEND CMAKE_CXX_FLAGS "-W -Wall -Werror -std=c++1z -g ${CMAKE_CXX_FLAGS}")
    else()
        list(APPEND CMAKE_CXX_FLAGS "-O3 -W -Wall -Werror -std=c++1z ${CMAKE_CXX_FLAGS}")
    endif()
endif()

if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

# Set the include files for the library.
include_directories (
    ${CMAKE_HOME_DIRECTORY}/include
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

target_link_libraries(${PROJECT_NAME} -lstdc++fs)
