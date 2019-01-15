if (WIN32)
    set(DEPENDENCIES_DIR ${CMAKE_HOME_DIRECTORY}/dependencies)

    # ===== LIBPNG =====
    set(LIBPNG_VERSION 1.6.35)
    set(LIBPNG_HOME_DIRECTORY ${DEPENDENCIES_DIR}/libpng)

    include(ExternalProject)
    ExternalProject_Add(
         libpngBuild
         #-- Directories
         SOURCE_DIR ${LIBPNG_HOME_DIRECTORY}
         BINARY_DIR ${LIBPNG_HOME_DIRECTORY}
         #-- Configure
         CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} ${LIBPNG_HOME_DIRECTORY}
         #-- Install
         UPDATE_DISCONNECTED
    )

    set(LIBPNG_LIB_PATH ${LIBPNG_HOME_DIRECTORY}/$(Configuration)/libpng.lib)
    add_library(libpng SHARED IMPORTED)
    set_target_properties(libpng PROPERTIES IMPORTED_LOCATION ${LIBPNG_LIB_PATH})

    include_directories(${LIBPNG_HOME_DIRECTORY})
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIB_PATH})
    add_dependencies(${PROJECT_NAME} libpngBuild)


    # ===== LIBJPEG_TURBO =====
    set(LIBJPEG_TURBO_HOME_DIRECTORY ${DEPENDENCIES_DIR}/libjpeg-turbo)

    include(ExternalProject)
    ExternalProject_Add(
         jpegturboBuild
         #-- Directories
         SOURCE_DIR ${LIBJPEG_TURBO_HOME_DIRECTORY}
         BINARY_DIR ${LIBJPEG_TURBO_HOME_DIRECTORY}
         #-- Configure
         CONFIGURE_COMMAND ${CMAKE_COMMAND} -DCMAKE_GENERATOR_PLATFORM=${CMAKE_GENERATOR_PLATFORM} ${LIBJPEG_TURBO_HOME_DIRECTORY}
         #-- Install
         UPDATE_DISCONNECTED
    )

    set(LIBJPEG_TURBO_LIB_PATH ${LIBJPEG_TURBO_HOME_DIRECTORY}/$(Configuration)/libturbojpeg.lib)
    add_library(libturbojpeg SHARED IMPORTED)
    set_target_properties(libturbojpeg PROPERTIES IMPORTED_LOCATION ${LIBJPEG_TURBO_LIB_PATH})

    include_directories(${LIBJPEG_TURBO_HOME_DIRECTORY})
    target_link_libraries(${PROJECT_NAME} ${LIBJPEG_TURBO_LIB_PATH})
    add_dependencies(${PROJECT_NAME} jpegturboBuild)
endif()
