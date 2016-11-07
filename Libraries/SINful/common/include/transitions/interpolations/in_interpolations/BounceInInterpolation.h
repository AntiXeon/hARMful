#ifndef __SIN_BOUNCE_IN_INTERPOLATION__
#define __SIN_BOUNCE_IN_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Bounce interpolation of values.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class BounceInInterpolation : public IInterpolation {
        private:
            /**
             * @brief   Magic numbers to compute the bounce interpolation.
             */
            static const Mind::Scalar BounceMagic[10] ;

        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a BounceInInterpolation.
             */
            BounceInInterpolation() ;

            /**
             * @brief   Destruction of the BounceInInterpolation.
             */
            virtual ~BounceInInterpolation() ;

                                                             /*** UTILITIES ***/
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
