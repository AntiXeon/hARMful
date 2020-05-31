#ifndef __SPITE__IMAGE_READER__
#define __SPITE__IMAGE_READER__

#include <utils/Platform.hpp>
#include <files/images/data/RawImage.hpp>
#include <string>

namespace Spite {
    /**
     * Dedicated class to red compressed images.
     */
    class ImageReader {
        protected:
            static const float GammaCorrection ;
            static const float HDRScale ;

        private:
            /**
             * true to flip vertically on load; false otherwise.
             */
            bool m_verticalFlip = false ;

        public:
            /**
             * Create a new ImageReader to write compressed data in a file.
             * @param   image        Structure to which insert image data.
             * @param   path         Path of the file to read.
             * @param   verticalFlip true to flip vertically; false otherwise.
             */
            exported ImageReader(const bool verticalFlip = false) ;

            /**
             * Perform read of the file.
             */
            exported virtual RawImage process() = 0 ;

        protected:
            /**
             * true to flip vertically on load; false otherwise.
             */
            bool flip() const ;

            /**
             * Common post-read action.
             */
            bool postRead(
                RawImage& image,
                int width,
                int height,
                unsigned char* imageData
            ) ;
    } ;
}

#endif
