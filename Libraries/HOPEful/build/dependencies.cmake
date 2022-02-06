# Minimal versions of the dependencies.
SET(LIBGLEW_REQUIRED_VERSION "2.2.0")
SET(LIBGLFW_REQUIRED_VERSION "3.3.5")
SET(LIBASSIMP_REQUIRED_VERSION "5.0.1")

set(USE_CONAN_LIBS OFF)
set(CONAN_LIBS "")
set(CONAN_LINK "")

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW ${LIBGLEW_REQUIRED_VERSION} QUIET)
if (GLEW_FOUND AND NOT ${USE_CONAN_LIBS})
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
else()
    set(USE_CONAN_LIBS ON)
    list(APPEND CONAN_LIBS "glew/${LIBGLEW_REQUIRED_VERSION}")
    list(APPEND CONAN_LINK CONAN_PKG::glew)
endif()

# GLFW (Window/inputs)
find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
    pkg_search_module(GLFW QUIET glfw3)
endif()

if (GLFW_FOUND AND NOT ${USE_CONAN_LIBS})
    include_directories(${GLFW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
else()
    set(USE_CONAN_LIBS ON)
    list(APPEND CONAN_LIBS "glfw/${LIBGLFW_REQUIRED_VERSION}")
    list(APPEND CONAN_LINK CONAN_PKG::glfw)
endif()

# Assimp (3D models)
cmake_policy(SET CMP0012 OLD)
find_package(assimp ${LIBASSIMP_REQUIRED_VERSION} QUIET)
if (assimp_FOUND AND NOT ${USE_CONAN_LIBS})
    # Because ASSIMP find_package seems to be broken...
    set(ASSIMP_LIBRARY "assimp")
    target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARY})
else()
    set(USE_CONAN_LIBS ON)
    list(APPEND CONAN_LIBS "assimp/${LIBASSIMP_REQUIRED_VERSION}")
    list(APPEND CONAN_LINK CONAN_PKG::assimp)
endif()

if (${USE_CONAN_LIBS})
    conan_cmake_run(
        REQUIRES ${CONAN_LIBS}
        BASIC_SETUP CMAKE_TARGETS
        OPTIONS *:shared=True
        GENERATORS cmake virtualrunenv
    )
    target_link_libraries(${PROJECT_NAME} ${CONAN_LINK})
endif()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32)
endif()
