#ifndef __SPITE__IMAGE_FILE_READER__
#define __SPITE__IMAGE_FILE_READER__

#include <utils/Platform.hpp>
#include <files/images/readers/ImageReader.hpp>
#include <string>

namespace Spite {
    /**
     * Dedicated class to red compressed images from files.
     */
    class ImageFileReader final : public ImageReader {
        private:
            /**
             * Path to the file to read.
             */
            std::string m_filepath ;

        public:
            /**
             * Create a new ImageReader to write compressed data in a file.
             * @param   path         Path of the file to read.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageFileReader(
                const std::string& filepath,
                const bool verticalFlip = false
            ) ;

            /**
             * Perform read of the file.
             */
            exported RawImage process() ;

        private:
            /**
             * Read images.
             * @return  true on success; false otherwise.
             */
            exported RawImage readImage() ;

            /**
             * Read images with 8-bits per channel.
             * @return  true on success; false otherwise.
             */
            exported RawImage read8BitsChannel() ;

            /**
             * Read images with 16-bits per channel.
             * @return  true on success; false otherwise.
             */
            exported RawImage read16BitsChannel() ;

            /**
             * Read HDR file.
             * @return  true on success; false otherwise.
             */
            exported RawImage readHDR() ;
    } ;
}

#endif
