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
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++latest")
        endif()
    endif()
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

if (UNIX)
    target_link_libraries(${PROJECT_NAME} -lstdc++fs)
endif()

if (WIN32)
    set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES LINK_FLAGS
        "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\" /SUBSYSTEM:CONSOLE")
    target_link_libraries(${PROJECT_NAME})
endif()
