#ifndef __FRACTAL_COLORS__
#define __FRACTAL_COLORS__

#include <vector>
#include <DOOMful/utils/Mutex.h>
#include <Fractals/graphics/PixelColor.h>

/**
 * @brief   Fractal colors defines steps and colors to produce nice fractal
 *          pictures.
 *
 * @author  Denis CARLUS
 * @version 1.0     12/13/2015
 */
class FractalColors {
    private:
        /**
         * @brief   Mutex to prevent concurrent accesses.
         */
        Doom::Mutex m_mutex ;

        /**
         * @brief   List of colors.
         */
        std::vector<PixelColor> m_colors ;


    public:
        /**
         * @brief   Creation of a FractalColors instance.
         * @param   fractalIterations   Amount of iterations to render the
         *                              fractal.
         */
        FractalColors(const int& fractalIterations) ;

        /** @brief Destruction of the FractalColors instance. */
        virtual ~FractalColors() ;


        /**
         * @brief   Set the key colors. They are interpolated to fill all the
         *          colors in the FractalColors and render nice fractals.
         * @param   keyColors   List of the key colors. Start from 0 to maximal
         *                      amount of iterations.
         */
        void setColors(const std::vector<PixelColor>& keyColors) ;

        /**
         * @brief   Get the color corresponding to the given iteration.
         * @warning If the iteration number is greater than the fractal
         *          iteration (given at FractalColors construction), the
         *          PixelColor of the maximal amount of iterations is returned
         *          instead.
         */
        PixelColor& getColor(const unsigned int& iteration) ;

        /**
         * @brief   Get the maximal amount of iterations for the fractal
         *          computation.
         * @return  Amount of iterations to render the fractal.
         */
        unsigned int getFractalIterations() const ;
} ;

#endif
