# Minimal versions of the dependencies.
SET(LIBJPEGTURBO_REQUIRED_VERSION "2.0.2")
SET(LIBPNG_REQUIRED_VERSION "1.6.37")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

set(CONAN_LIBS "")
set(CONAN_LINK "")

# LibJpegTurbo (load JPEG files)
find_package(LibJpegTurbo ${LIBJPEGTURBO_REQUIRED_VERSION} QUIET)
if (JPEGTURBO_FOUND AND NOT ${USE_CONAN_LIBS})
    include_directories(${JPEGTURBO_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${JPEGTURBO_LIBRARIES})
    target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
elseif(NOT NO_CONAN)
    set(USE_CONAN_LIBS ON)
    list(APPEND CONAN_LIBS "libjpeg-turbo/${LIBJPEGTURBO_REQUIRED_VERSION}@bincrafters/stable")
    list(APPEND CONAN_LINK CONAN_PKG::libjpeg-turbo)
endif()

# libpng (load PNG files)
find_package(PNG ${LIBPNG_REQUIRED_VERSION} QUIET)
if (PNG_FOUND AND NOT ${USE_CONAN_LIBS})
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})
elseif(NOT NO_CONAN)
    set(USE_CONAN_LIBS ON)
    list(APPEND CONAN_LIBS "libpng/${LIBPNG_REQUIRED_VERSION}@bincrafters/stable")
    list(APPEND CONAN_LINK CONAN_PKG::libpng)
endif()

if (NOT NO_CONAN AND ${USE_CONAN_LIBS})
    conan_cmake_run(
        REQUIRES ${CONAN_LIBS}
        BASIC_SETUP CMAKE_TARGETS
        OPTIONS *:shared=True
        GENERATORS cmake virtualrunenv
    )
    target_link_libraries(${PROJECT_NAME} ${CONAN_LINK})
endif()
