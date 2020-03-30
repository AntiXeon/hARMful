#ifndef __SPITE__RAW_IMAGE_DATA__
#define __SPITE__RAW_IMAGE_DATA__

#include <utils/Platform.hpp>
#include <files/images/data/ColorFormat.hpp>
#include <interfaces/IFileData.hpp>

namespace Spite {

    /**
     * Image containing raw uncompressed data.
     */
    class RawImage final : public IFileData {
        private:
            /**
             * Width of the picture.
             */
            unsigned int m_width = 0 ;

            /**
             * Height of the picture
             */
            unsigned int m_height = 0 ;

            /**
             * Picture pixel data.
             */
            std::vector<unsigned char> m_pixelData ;

            /**
             * Format of the picture.
             */
            ColorFormat::ID m_format = ColorFormat::Unknown ;


        public:
            /**
             * Create a new RawImage.
             * @param   format  Format of the RawImage.
             */
            exported RawImage(ColorFormat::ID format = ColorFormat::Unknown) ;

            /**
             * Set the dimensions of the picture.
             * @param   width   Width of the picture.
             * @param   height  Height of the picture
             */
            exported void setDimensions(
                const unsigned int& width,
                const unsigned int& height
            ) ;

            /**
             * Set the color format of the picture.
             * @param   format  The format of the picture.
             */
            exported void setFormat(ColorFormat::ID format) ;

            /**
             * Get the ColorFormat used by the RawImage.
             * @return  ColorFormat used by the RawImage.
             */
            exported ColorFormat::ID format() ;

            /**
             * Get the image raw data.
             * return   Output the raw data of the image. Data is
             *          expected to be an array of bytes.
             * @warning @a data should not be initialized, an array is
             *          allocated on getting data.
             */
            exported std::vector<unsigned char>& data() ;

            /**
             * Width of the image.
             * @return  The width of the image.
             */
            exported unsigned int width() const ;

            /**
             * Height of the image.
             * @return  The height of the image.
             */
            exported unsigned int height() const ;
    } ;
}

 #endif
