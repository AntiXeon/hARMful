#ifndef __SPITE_RAW_IMAGE_DATA__
#define __SPITE_RAW_IMAGE_DATA__

#include <files/images/data/ColorFormat.h>
#include <interfaces/IFileData.h>


namespace Spite {

    /**
     * @brief   Image containing raw uncompressed data.
     *
     * @author  Denis CARLUS
     * @version 1.0     03/09/2016
     */
    class RawImage : public IFileData {
        private:
            /**
             * @brief   Width of the picture.
             */
            unsigned int m_width ;

            /**
             * @brief   Height of the picture
             */
            unsigned int m_height ;

            /**
             * @brief   Picture pixel data.
             */
            int* m_pixelData ;

            /**
             * @brief   Format of the picture.
             */
            ColorFormat* m_format ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new RawImage.
             * @param   format  Format of the RawImage.
             */
            RawImage(ColorFormat* format = NULL) ;

            /**
             * @brief   Destruction of the RawImage
             */
            virtual ~RawImage() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Free data from the RawImage instance.
             * @warning Data are not usable anymore after this call.
             */
            void freeData() ;


                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Set the dimensions of the picture.
             * @param   width   Width of the picture.
             * @param   height  Height of the picture
             */
            void setDimensions(
                               const unsigned int& width,
                               const unsigned int& height
                              ) ;

            /**
             * @brief   Set the color format of the picture.
             * @param   format  The format of the picture.
             * @return  TRUE if the format has been set, FALSE else.
             * @warning Format can only be set if it has not been defined yet.
             *          Once it is done, calling this method has no effect.
             */
            bool setFormat(ColorFormat* format) ;

            /**
             * @brief   Get the ColorFormat used by the RawImage.
             * @return  ColorFormat used by the RawImage.
             */
            const ColorFormat* getFormat() const ;

            /**
             * @brief   Get the image raw data.
             * @param   data    Output the raw data of the image. Data is
             *                  expected to be an array of integers.
             * @param   size    Output the size of the image @a data.
             * @warning @a data should not be initialized, an array is
             *          allocated on getting data.
             */
            void getData(void*& data, unsigned int& size) ;

            /**
             * @brief   Width of the image.
             * @return  The width of the image.
             */
            unsigned int getWidth() const ;

            /**
             * @brief   Height of the image.
             * @return  The height of the image.
             */
            unsigned int getHeight() const ;
    } ;

} ;

 #endif
