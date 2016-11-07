/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		BaseState.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/31/2015                 */
/* UPDATE:      01/31/2015                 */
/*                                         */
/* Base class to create states in a State  */
/* Machine.                                */
/*******************************************/

#ifndef __DOOM__BASE_STATE__
#define __DOOM__BASE_STATE__

#include <map>
#include <patterns/StateMachine/BaseStateTransition.h>


namespace Doom {

    /**
     * @brief   Base class to create states in a State Machine.
     * @author  CB (c) 2015
     * @version 0.1     2015/01/31
     */
    class BaseState {
        private:
            /**
             * @brief   List of available transitions.
             *          It is defined as an association of the toward state and
             *          the condition to check if the transition is possible.
             */
            std::map<BaseState*, BaseStateTransition*> m_transitions ;
            typedef std::map<BaseState*, BaseStateTransition*>::iterator TransitionIterator ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a BaseState.
             */
            BaseState() ;

            /**
             * @brief   Destruction of the BaseState.
             * @warning This destructor already destroy all allocated
             *          BaseStateTransition objects.
             */
            virtual ~BaseState() ;

                                                               /** UTILITIES **/
            /**
             * @brief   Add a transition from the current state to another one.
             *          This transition contains the conditions to be checked to
             *          allow the state change.
             * @param   toward      The state to enable to the transition to.
             * @param   transition  The conditions to be checked to perform the
             *                      transition.
             * @warning If set more than once, the transition is overwritten.
             */
            void addTransition(
                               BaseState* toward,
                               BaseStateTransition* transition
                              ) ;

            /**
             * @brief   Check the conditions to move to the @a toward state.
             * @param   toward  The next state for which the transition is
             *                  checked.
             * @return  TRUE if the condition is checked, FALSE otherwise.
             *          FALSE is also returned when the given @a toward state
             *          is not set as an available next state to the current
             *          one.
             */
            bool canMakeTransitionTo(BaseState* toward) ;
    } ;

} ;

#endif
