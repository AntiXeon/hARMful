cmake_minimum_required(VERSION 2.8.12)

# Project declaration
project(MINDUnitTest)
set(CMAKE_HOME_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE})
set(CURRENT_TEST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

if (UNIX)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        list(APPEND CMAKE_CXX_FLAGS "-W -Wall -Werror -std=c++1y ${CMAKE_CXX_FLAGS}")
    endif()
endif()

# Set the include files for the library.
include_directories (
    ${CURRENT_TEST_INCLUDE_DIR}
    ${COMMON_UNIT_TESTS_INCLUDE_DIR}
    ${DOOM_INCLUDE_DIRS}
)

# List source files
file (
    GLOB_RECURSE
    SOURCES
    ${CMAKE_HOME_DIRECTORY}/src/*.cpp
    ${COMMON_UNIT_TESTS_SRC_DIR}/*.cpp
)

add_executable (
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} DOOM)
