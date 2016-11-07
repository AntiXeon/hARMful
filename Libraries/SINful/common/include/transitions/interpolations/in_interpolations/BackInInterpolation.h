#ifndef __SIN_BACK_IN_INTERPOLATION__
#define __SIN_BACK_IN_INTERPOLATION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Back interpolation of values.
     *          It follows the formula
     *          <b>y(x) = x^2 * ((s + 1) * x - s)</b> for x in [0;1] and s being
     *          the overshoot factor.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class BackInInterpolation : public IInterpolation {
        private:
            /**
             * @brief Factor of the back effect.
             */
            Mind::Scalar m_overshoot ;

        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a BackInInterpolation.
             * @param   overshoot   Factor of the back effect.
             */
            BackInInterpolation(const Mind::Scalar& overshoot = 1.5f) ;

            /**
             * @brief   Destruction of the BackInInterpolation.
             */
            virtual ~BackInInterpolation() ;

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
