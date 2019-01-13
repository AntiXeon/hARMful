#ifndef __SPITE__JPEG_TURBO_FILE__
#define __SPITE__JPEG_TURBO_FILE__

extern "C" {
    #include <stdio.h>
    #include <stddef.h>
    #include <turbojpeg.h>
}

#include <files/BinaryFile.hpp>
#include <files/images/data/ColorFormat.hpp>
#include <files/images/data/RawImage.hpp>

namespace Spite {

    /**
     * Load a JPEG file using libjpeg-turbo (using SIMD).
     */
    class JPEGTurboFile final : public BinaryFile {
        public:
            /**
             * Create a new JPEGTurboFile.
             * @param   path    Path of the file to open.
             */
            JPEGTurboFile(const std::string& path) ;

            /**
             * Destruction of the JPEGTurboFile.
             */
            virtual ~JPEGTurboFile() = default ;

            // Remove copy/move operations.
            JPEGTurboFile(const JPEGTurboFile& copied) = delete;
            JPEGTurboFile(JPEGTurboFile&& moved) = delete;
            JPEGTurboFile& operator=(const JPEGTurboFile& copied) = delete;
            JPEGTurboFile& operator=(JPEGTurboFile&& moved) = delete;

        public:
            /**
             * Load a data at a given place on disk.
             * @param   filedata    File data to store data in.
             */
            bool load(RawImage* filedata) ;

            /**
             * Save a data at a given place on disk.
             * @param   output      Raw data to write on disk. They can be
             *                      processed before saving.
             * @param   path        Path to the location on filesystem.
             */
            bool save(
                RawImage* output,
                const std::string& path
            ) ;

        private:
            /**
             * Convert the color space value from libjpeg-turbo to the color
             * space values of SPITE.
             */
            ColorFormat::ID convertColorFormat(const int jpegColorSpace) ;
    } ;
}

#endif
