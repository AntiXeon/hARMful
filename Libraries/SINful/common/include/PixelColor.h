#ifndef __SIN_PIXEL_COLOR__
#define __SIN_PIXEL_COLOR__


#include <utils/Mutex.h>


namespace Sin {

    /**
     * @brief	A PixelColor is a color for pixel with three components :
     *          red, green, blue
     *
     * @author  Denis CARLUS
     * @version 1.0     12/13/2015
     */
    class PixelColor {
        private:
            /** @brief  Red component of the color. */
            int m_red ;

            /** @brief  Green component of the color. */
            int m_green ;

            /** @brief  Blue component of the color. */
            int m_blue ;

            /** @brief  Hexadecimal representation of the color. */
            int m_hexadecimal ;

        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a color with its components values.
             */
            PixelColor(int red = 0, int green = 0, int blue = 0) ;

            /** @brief  Destruction of a PixelColor. */
            virtual ~PixelColor() ;

                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the red value.
             * @return  Red value of the PixelColor.
             */
            int getRed() const ;

            /**
             * @brief   Get the green value.
             * @return  Green value of the PixelColor.
             */
            int getGreen() const ;

            /**
             * @brief   Get the blue value.
             * @return  Blue value of the PixelColor.
             */
            int getBlue() const ;


            /** @brief  Convert the pixel color to an integer value. */
            operator int() const ;


            /**
             * @brief   Set the red value.
             * @param   red     Red value of the PixelColor.
             */
            void setRed(const int& red) ;

            /**
             * @brief   Set the green value.
             * @param   green   Green value of the PixelColor.
             */
            void setGreen(const int& green) ;

            /**
             * @brief   Set the blue value.
             * @param   blue    Blue value of the PixelColor.
             */
            void setBlue(const int& blue) ;

            /**
             * @brief   Set the color.
             * @param   red     Red value of the PixelColor.
             * @param   green   Green value of the PixelColor.
             * @param   blue    Blue value of the PixelColor.
             */
            void setColor(
                          const int& red,
                          const int& green,
                          const int& blue
                         ) ;

        private:
            /** @brief  Set the Hexadecimal representation of the PixelColor. */
            void setHexadecimalRepresentation() ;
    } ;

} ;

#endif
