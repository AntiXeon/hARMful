
# - Try to find libjpeg-turbo
# Once done, this will define
#
#  JPEG_FOUND - system has libjpeg-turbo
#  JPEG_INCLUDE_DIRS - the libjpeg-turbo include directories
#  JPEG_LIBRARIES - link these to use libjpeg-turbo
#

include (FindPackageHandleStandardArgs)

find_path(JPEGTURBO_INCLUDE_DIR turbojpeg.h
          PATHS ${JPEGTURBO_PATH}/include
                /usr/include
                /usr/local/opt/libjpeg-turbo/include)
set(JPEGTURBO_NAMES ${JPEGTURBO_NAMES} libturbojpeg turbojpeg)

find_library(JPEGTURBO_LIBRARY NAMES ${JPEGTURBO_NAMES}
             PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                   ${JPEGTURBO_PATH}/lib64
                   ${JPEGTURBO_PATH}/lib
                   /usr/local/opt/jpeg-turbo/lib
                   /usr/local/opt/jpeg-turbo/lib64
                   /usr/lib/x86_64-linux-gnu/
                   NO_DEFAULT_PATH)

if (NOT JPEGTURBO_LIBRARY)
find_library(JPEGTURBO_LIBRARY NAMES ${JPEGTURBO_NAMES}
             PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                   ${JPEGTURBO_PATH}/lib
                   /usr/lib)
endif ()

# handle the QUIETLY and REQUIRED arguments and set JPEG_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JPEGTURBO DEFAULT_MSG JPEGTURBO_LIBRARY JPEGTURBO_INCLUDE_DIR)

if(JPEGTURBO_FOUND)
  set(JPEGTURBO_LIBRARIES ${JPEGTURBO_LIBRARY})
endif()

mark_as_advanced(JPEGTURBO_LIBRARY JPEGTURBO_INCLUDE_DIR )
