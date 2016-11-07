#ifndef __SIN_BOUNCE_OUT_INTERPOLATION__
#define __SIN_BOUNCE_OUT_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Bounce interpolation of values.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class BounceOutInterpolation : public IInterpolation {
        private:
            /**
             * @brief   Magic numbers to compute the bounce interpolation.
             */
            static const Mind::Scalar BounceMagic[10] ;

        public:
            /**
             * @brief   Create a BounceOutInterpolation.
             */
            BounceOutInterpolation() ;

            /**
             * @brief   Destruction of the BounceOutInterpolation.
             */
            virtual ~BounceOutInterpolation() ;

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
