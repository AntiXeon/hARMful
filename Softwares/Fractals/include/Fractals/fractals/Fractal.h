#ifndef __FRACTAL_BASE__
#define __FRACTAL_BASE__

#include <MINDful/geometry/dimensions/Dimension2Df.h>
#include <Fractals/fractals/ComplexNumber.h>
#include <Fractals/graphics/SDLWindow.h>
#include <Fractals/graphics/FractalColors.h>

/**
 * @brief	A Fractal is a natural phenomenon or a mathematical set that
 *          exhibits a repeating pattern that displays at every scale.
 *
 * @author  Denis CARLUS
 * @version 1.0     12/13/2015
 */
class Fractal {
    protected:
        /** @brief  Bounds of the space on X axis. */
        Mind::Dimension2Df m_spaceXBounds ;

        /** @brief  Bounds of the space on Y axis. */
        Mind::Dimension2Df m_spaceYBounds ;

        /**
         * @brief   Complex number used as seed of the Fractal.
         */
        ComplexNumber m_seed ;


    public:
                                          	  /** CONSTRUCTION / DESTRUCTION **/
        /**
         * @brief   Create a generic Fractal.
         * @param   spaceXBounds    Bounds of the space on X axis.
         * @param   spaceYBounds    Bounds of the space on Y axis.
         * @param   seed            Complex number used as seed of the Fractal.
         */
        Fractal(
                const Mind::Dimension2Df& spaceXBounds,
                const Mind::Dimension2Df& spaceYBounds,
                const ComplexNumber& seed
               ) ;

        /** @brief  Destruction of the Fractal object. */
        virtual ~Fractal() ;


                                                           	   /** UTILITIES **/
        /**
         * @brief   Compute the Fractal and draw it on the given window.
         * @param   window   The window to draw the Fractal on.
         * @param   colors   Colors to render a nice Fractal.
         */
        virtual void draw(
                          SDLWindow& window,
                          FractalColors& colors
                         ) = 0 ;


                                                             	 /** SETTERS **/
        /**
         * @brief   Set the bounds of the Fractal.
         * @param   spaceXBounds    Bounds of the space on X axis.
         * @param   spaceYBounds    Bounds of the space on Y axis.
         */
        void setBounds(
                       const Mind::Dimension2Df& spaceXBounds,
                       const Mind::Dimension2Df& spaceYBounds
                      ) ;

        /**
         * @brief   Set the seed of the Fractal.
         * @param   seed            Complex number used as seed of the Fractal.
         */
        void setSeed(const ComplexNumber& seed) ;
} ;


#endif
