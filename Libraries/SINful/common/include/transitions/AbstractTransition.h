#ifndef __SIN_ABSTRACT_TRANSITION__
#define __SIN_ABSTRACT_TRANSITION__


#include <transitions/interpolations/IInterpolation.h>


namespace Sin {

    /**
     * @brief   Base class for creating transitions.
     * @author  CB (c) 2016
     * @version 0.1     2016/02/09
     */
    class AbstractTransition {
        private:
            /**
             * @brief   Last of the transition.
             */
            unsigned int m_timeLast ;

            /**
             * @brief   Time currently reached in the transition.
             */
            unsigned int m_timeCurrent ;

            /**
             * @brief   Interpolation used by the AbstractTransition.
             */
            IInterpolation* m_interpolation ;



        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new AbstractTransition.
             * @param   last            Last of the while transition.
             * @param   interpolation   Interpolation used to compute the
             *                          intermediary values.
             */
            AbstractTransition(const int& last, IInterpolation* interpolation) ;

            /**
             * @brief   Destruction of the AbstractTransition.
             * @warning Interpolation is not destroyed.
             */
            virtual ~AbstractTransition() ;

                                                             /*** UTILITIES ***/
            /**
             * @brief   Increase the time value used to compute the intermediary
             *          values.
             * @param   increase    Amount of the increase of time.
             *                      Default is 1.
             */
            void increaseTime(const unsigned int& increase = 1) ;

            /**
             * @brief   Compute the transition from start to end property, for
             *          the current time in transition.
             * @param   start   Start value property to be animated.
             * @param   end     End value property to be animated.
             * @param   result  The value for the current time of the transition
             *                  property.
             */
            virtual void compute(
                                 const void* start,
                                 const void* end,
                                 void* result
                                ) = 0 ;


        protected:
                                                     /*** SETTERS / GETTERS ***/
            /**
             * @brief   Get the factor to interpolate values at the current
             *          time.
             * @return  Factor used to compute the transition values at the
             *          current time.
             */
            Mind::Scalar getInterpolation() ;

    } ;

} ;


#endif
