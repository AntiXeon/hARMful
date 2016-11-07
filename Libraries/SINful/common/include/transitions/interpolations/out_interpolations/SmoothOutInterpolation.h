#ifndef __SIN_SMOOTH_OUT_INTERPOLATION__
#define __SIN_SMOOTH_OUT_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Smooth interpolation of values.
     *          This interpolation follows the formula
     *          <b>y(x) = ((cos((PI * x) + PI)) + 1) / 2</b> for x in [0;1].
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class SmoothOutInterpolation : public IInterpolation {
        public:
            /**
             * @brief   Create a SmoothOutInterpolation.
             */
            SmoothOutInterpolation() ;

            /**
             * @brief   Destruction of the SmoothOutInterpolation.
             */
            virtual ~SmoothOutInterpolation() ;

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
