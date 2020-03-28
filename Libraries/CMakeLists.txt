cmake_minimum_required(VERSION 2.8.12)
project(hARMful)

set(HARMFUL_LIBS_DIR ${CMAKE_SOURCE_DIR})
add_compile_definitions(COMPILE_SHARED_LIBS)

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

add_subdirectory(${HARMFUL_LIBS_DIR}/DOOMful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/SPITEful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/MINDful/build)
add_subdirectory(${HARMFUL_LIBS_DIR}/HOPEful/build)
