#ifndef __JULIA_FRACTAL__
#define __JULIA_FRACTAL__

#include <Fractals/fractals/Fractal.h>

/**
 * @brief	A JuliaFractal is a natural phenomenon or a mathematical set that
 *          exhibits a repeating pattern displayed at every scale.
 *
 * @author  Denis CARLUS
 * @version 1.0     12/13/2015
 */
class JuliaFractal : public Fractal {
    public:
                                          	  /** CONSTRUCTION / DESTRUCTION **/
        /**
         * @brief   Create a JuliaFractal.
         * @param   spaceXBounds    Bounds of the space on X axis.
         * @param   spaceYBounds    Bounds of the space on Y axis.
         * @param   seed            Complex number used as seed of the Fractal.
         */
        JuliaFractal(
                     const Mind::Dimension2Df& spaceXBounds,
                     const Mind::Dimension2Df& spaceYBounds,
                     const ComplexNumber& seed
                    ) ;

        /** @brief  Destruction of the JuliaFractal object. */
        virtual ~JuliaFractal() ;


                                                           	   /** UTILITIES **/
        /**
         * @brief   Compute the JuliaFractal and draw it on the given window.
         * @param   window  The window to draw the Fractal on.
         * @param   colors  Colors to render a nice Fractal.
         */
        void draw(
                  SDLWindow& window,
                  FractalColors& colors
                 ) ;


    private:
        /**
         * @brief   List of parameters for multithreaded computations of the
         *          fractal.
         */
        struct JuliaFractalThreadParameters {
            public:
                JuliaFractal* Fractal ;
                SDLWindow* Window ;
                FractalColors* Colors ;
                Mind::Point2Df PartPosition ;
                Mind::Dimension2Df PartSize ;
                Mind::Dimension2Df PartZoom ;
        } ;

        /**
         * @brief   Pointer to the function to draw a part of the JuliaFractal.
         */
        typedef void* (*JuliaFractalMethod)(void* parameter) ;

        /**
         * @brief   Draw a part of the fractal.
         * @param   parameter   A JuliaFractalThreadParameters object.
         * @return  NULL.
         */
        static void* drawPart(void* parameter) ;
} ;

#endif
