#ifndef __SDL_VIEWPORT_PART__
#define __SDL_VIEWPORT_PART__

#include <vector>
#include <SDL2/SDL.h>
#include <Fractals/graphics/PixelColor.h>
#include <MINDful/geometry/points/Point2Di.h>
#include <MINDful/geometry/dimensions/Dimension2Di.h>

/**
 * @brief	A ViewportPart stores pixel data for rendering on parts of the whole
 *          displayed viewport.
 *
 * @author  Denis CARLUS
 * @version 1.0     12/16/2015
 */
class ViewportPart {
    private:
        /**
         * @brief   List of pixel colors in the ViewportPart.
         */
        std::vector<int> m_pixels ;

        /**
         * @brief   Dimension of the ViewportPart.
         */
        Mind::Dimension2Di m_dimension ;

        /**
         * @brief   Position of the ViewportPart.
         */
        Mind::Point2Di m_position ;

        /**
         * @brief   Mutex to prevent concurrent accesses.
         */
        Doom::Mutex m_mutex ;


    public:
                                          	  /** CONSTRUCTION / DESTRUCTION **/
        /**
         * @brief   Creation of a new ViewportPart.
         * @param   x           Position on X axis of the ViewportPart.
         * @param   y           Position on Y axis of the ViewportPart.
         * @param   width       Width of the ViewportPart.
         * @param   height      Height of the ViewportPart.
         */
        ViewportPart(
                     const int& x,
                     const int& y,
                     const int& width,
                     const int& height
                    ) ;

        /**
         * @brief   Destruction of the ViewportPart.
         */
        virtual ~ViewportPart() ;

                                                             	 /** SETTERS **/
        /**
         * @brief   Set the color of a pixel.
         * @param   x       Position of the pixel on X axis.
         * @param   y       Position of the pixel on Y axis.
         * @param   color   Color of the pixel to set.
         */
        void setPixelColor(
                           const int& x,
                           const int& y,
                           const PixelColor& color
                          ) ;

                                                             	 /** GETTERS **/
        /**
         * @brief   Get pixels from the ViewportPart.
         * @return  List of pixel colors in the ViewportPart.
         */
        int* getPixels() const ;

        /**
         * @brief   Get the position on X axis of the ViewportPart.
         * @return  Position on X axis of the ViewportPart.
         */
        int getX() const ;

        /**
         * @brief   Get the position on Y axis of the ViewportPart.
         * @return  Position on Y axis of the ViewportPart.
         */
        int getY() const ;

        /**
         * @brief   Get the width of the ViewportPart.
         * @return  Width of the Texture.
         */
        int getWidth() const ;

        /**
         * @brief   Get the height of the ViewportPart.
         * @return  Height of the Texture.
         */
        int getHeight() const ;
} ;

#endif
