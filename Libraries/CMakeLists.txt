cmake_minimum_required(VERSION 2.8.12)

project(hARMful)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR})

# Remove prefix for shared libraries on Windows
if (WIN32)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

add_subdirectory(${HARMFUL_LIBS_DIR}/DOOMful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/SPITEful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/MINDful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/HOPEful/build)
