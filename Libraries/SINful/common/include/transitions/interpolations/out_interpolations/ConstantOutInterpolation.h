#ifndef __SIN_CONSTANT_OUT_INTERPOLATION__
#define __SIN_CONSTANT_OUT_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Constant interpolation of values. This makes the value directly
     *          change.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class ConstantOutInterpolation : public IInterpolation {
        public:
            /**
             * @brief   Create a ConstantOutInterpolation.
             */
            ConstantOutInterpolation() ;

            /**
             * @brief   Destruction of the ConstantOutInterpolation.
             */
            virtual ~ConstantOutInterpolation() ;

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
