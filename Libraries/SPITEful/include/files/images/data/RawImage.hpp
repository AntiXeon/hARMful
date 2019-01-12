#ifndef __SPITE__RAW_IMAGE_DATA__
#define __SPITE__RAW_IMAGE_DATA__

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
            unsigned int m_width ;

            /**
             * Height of the picture
             */
            unsigned int m_height ;

            /**
             * Picture pixel data.
             */
            int* m_pixelData = nullptr ;

            /**
             * Format of the picture.
             */
            ColorFormat* m_format = nullptr ;


        public:
            /**
             * Create a new RawImage.
             * @param   format  Format of the RawImage.
             */
            RawImage(ColorFormat* format = nullptr) ;

            /**
             * Destruction of the RawImage
             */
            virtual ~RawImage() ;

            /**
             * Free data from the RawImage instance.
             * @warning Data are not usable anymore after this call.
             */
            void freeData() ;

            /**
             * Set the dimensions of the picture.
             * @param   width   Width of the picture.
             * @param   height  Height of the picture
             */
            void setDimensions(
                const unsigned int& width,
                const unsigned int& height
            ) ;

            /**
             * Set the color format of the picture.
             * @param   format  The format of the picture.
             * @return  TRUE if the format has been set, FALSE else.
             * @warning Format can only be set if it has not been defined yet.
             *          Once it is done, calling this method has no effect.
             */
            bool setFormat(ColorFormat* format) ;

            /**
             * Get the ColorFormat used by the RawImage.
             * @return  ColorFormat used by the RawImage.
             */
            const ColorFormat* format() const ;

            /**
             * Get the image raw data.
             * @param   data    Output the raw data of the image. Data is
             *                  expected to be an array of integers.
             * @param   size    Output the size of the image @a data.
             * @warning @a data should not be initialized, an array is
             *          allocated on getting data.
             */
            void data(void*& data, unsigned int& size) ;

            /**
             * Width of the image.
             * @return  The width of the image.
             */
            unsigned int width() const ;

            /**
             * Height of the image.
             * @return  The height of the image.
             */
            unsigned int height() const ;

            // Remove copy/move operations.
            RawImage(const RawImage& copied) = delete;
            RawImage(RawImage&& moved) = delete;
            RawImage& operator=(const RawImage& copied) = delete;
            RawImage& operator=(RawImage&& moved) = delete;
    } ;
}

 #endif
