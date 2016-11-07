#ifndef __SIN_INTERPOLATION_INTERFACE__
#define __SIN_INTERPOLATION_INTERFACE__


#include <MINDTypes.h>


namespace Sin {

    /**
     * @brief   Interface of interpolations of transitions.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class IInterpolation {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Destruction of the IInterpolation.
             */
            virtual ~IInterpolation() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Interpolate values to get the current value factor.
             * @param   last    Last of the animation to compute the
             *                  interpolation at the wanted moment.
             * @param   now     Current time in the animation to determine the
             *                  factor value.
             * @return  The factor to compute the current transition value.
             */
            virtual Mind::Scalar interpolate(const int& last, const int& now) = 0 ;
    } ;

} ;


#endif
