/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		BaseStateMachine.h         */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/31/2015                 */
/* UPDATE:      01/31/2015                 */
/*                                         */
/* Base class to create State Machines.    */
/*******************************************/

#ifndef __DOOM__BASE_STATE_MACHINE__
#define __DOOM__BASE_STATE_MACHINE__


#include <vector>
#include <stddef.h>
#include <patterns/StateMachine/BaseState.h>

namespace Doom {

    /**
     * @brief   Base class to create State Machines.
     * @author  CB (c) 2015
     * @version 0.1     2015/01/31
     */
    template<class StateClass>
    class BaseStateMachine {
        private:
            /**
             * @brief   Current state of the state machine.
             */
            StateClass* m_currentState ;

            /**
             * @brief   List of the states available to the current state
             *          machine.
             */
            std::vector<StateClass> m_states ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Creation of a StateMachine.
             */
            BaseStateMachine(const int& maxStateID) ;

            /**
             * @brief   Destruction of the StateMachine.
             */
            virtual ~BaseStateMachine() ;

                                                               /** UTILITIES **/
            /**
             * @brief   Check the transition to the given state.
             * @param   state   State ID in the state machine.
             *                  This ID is array-index based, starting from
             *                  zero. It is highly recommanded to used
             *                  enumerations value to make it much more
             *                  readable.
             * @return  TRUE if the transition can be performed; FALSE
             *          otherwise.
             */
            bool checkTransitionTo(const int& state) ;

            /**
             * @brief   Try to change the current state to the given one.
             * @param   state   State ID in the state machine.
             *                  This ID is array-index based, starting from
             *                  zero. It is highly recommanded to used
             *                  enumerations value to make it much more
             *                  readable.
             * @return  TRUE when transition is successfully done; FALSE
             *          otherwise.
             */
            bool tryTransitionTo(const int& state) ;

        protected:
            /**
             * @brief   Add a new state to the state machine.
             * @param   stateID     ID of the state to add.
             * @param   state       State o
             */
            void addState(const int& stateID, const StateClass& state) ;

            /**
             * @brief   Define the states of the state machine.
             */
            virtual void defineStates() = 0 ;

                                                       /** GETTERS / SETTERS **/
            /**
             * @brief   Set the initial state of the state machine
             * @param   state   State defined as the initial one in the state
             *                  machine.
             */
            void setInitialState(const StateClass* state) ;


        public:
            /**
             * @brief  Get the current state of the state machine.
             */
            StateClass* getCurrentState() ;
    } ;

    #include <patterns/StateMachine/BaseStateMachine.impl>

} ;

#endif
