#ifndef __PIXEL_COLOR__
#define __PIXEL_COLOR__

#include <DOOMful/utils/Mutex.h>

/**
 * @brief	A PixelColor is a color for pixel with three components :
 *          red, green, blue
 *
 * @author  Denis CARLUS
 * @version 1.0     12/13/2015
 */
class PixelColor {
    private:
        /**
         * @brief   Mutex to prevent concurrent accesses.
         */
        Doom::Mutex m_mutex ;

        /** @brief  Red component of the color. */
        int m_red ;

        /** @brief  Green component of the color. */
        int m_green ;

        /** @brief  Blue component of the color. */
        int m_blue ;

        /** @brief  Hexadecimal representation of the color. */
        int m_hexadecimal ;

    public:
        /**
         * @brief   Creation of a color with its components values.
         */
        PixelColor(int red = 0, int green = 0, int blue = 0) ;

        /** @brief  Destruction of a PixelColor. */
        virtual ~PixelColor() ;


        /** @brief  Get the red value. */
        int getRed() const ;

        /** @brief  Get the green value. */
        int getGreen() const ;

        /** @brief  Get the blue value. */
        int getBlue() const ;


        /** @brief  Convert the pixel color to an integer value. */
        operator int() const ;

    private:
        /** @brief  Set the Hexadecimal representation of the PixelColor. */
        void setHexadecimalRepresentation() ;
} ;

#endif
