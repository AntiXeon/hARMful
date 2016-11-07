#ifndef __SIN_SMOOTH_IN_INTERPOLATION__
#define __SIN_SMOOTH_IN_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Smooth interpolation of values.
     *          This interpolation follows the formula
     *          <b>y(x) = ((cos((PI * x) + PI)) + 1) / 2</b> for x in [0;1].
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class SmoothInInterpolation : public IInterpolation {
        public:
            /**
             * @brief   Create a SmoothInInterpolation.
             */
            SmoothInInterpolation() ;

            /**
             * @brief   Destruction of the SmoothInInterpolation.
             */
            virtual ~SmoothInInterpolation() ;

            /**
             * @brief   Interpolate values to get the current value factor.
             * @param   last    Last of the animation to compute the
             *                  interpolation at the wanted moment.
             * @param   now     Current time in the animation to determine the
             *                  factor value.
             * @return  The factor to compute the current transition value.
             */
            Mind::Scalar interpolate(const int& last, const int& now) ;
    } ;

} ;


#endif
