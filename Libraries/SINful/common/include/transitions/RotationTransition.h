#ifndef __SIN_SIZE_TRANSITION__
#define __SIN_SIZE_TRANSITION__


#include <transitions/AbstractTransition.h>


namespace Sin {

    /**
     * @brief   Animated elements on their rotation angle.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class RotationTransition : public AbstractTransition {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new RotationTransition.
             * @param   last            Last of the while transition.
             * @param   interpolation   Interpolation used to compute the
             *                          intermediary values.
             */
            RotationTransition(const int& last, IInterpolation* interpolation) ;

            /**
             * @brief   Destruction of the RotationTransition.
             */
            virtual ~RotationTransition() ;


                                                             /*** UTILITIES ***/
            /**
             * @brief   Compute the transition from start to end property, for
             *          the current time in transition.
             * @param   start   Start value property to be animated.
             * @param   end     End value property to be animated.
             * @param   result  The value for the current time of the transition
             *                  property.
             */
            void compute(
                         const void* start,
                         const void* end,
                         void* result
                        ) ;
    } ;

} ;


#endif
