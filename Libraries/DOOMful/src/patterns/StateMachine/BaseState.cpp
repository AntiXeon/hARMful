/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		BaseState.cpp              */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/31/2015                 */
/* UPDATE:      01/31/2015                 */
/*                                         */
/* Base class to create states in a State  */
/* Machine.                                */
/*******************************************/

#include <patterns/StateMachine/BaseState.h>
#include <stddef.h>

namespace Doom {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BaseState::BaseState() {}

    BaseState::~BaseState() {
        // Delete the transitions object that have been created.
        TransitionIterator it = m_transitions.begin() ;
        for (; it != m_transitions.end() ; ++it) {
            delete (it -> second) ;
        }
    }

                                                               /** UTILITIES **/
    void BaseState::addTransition(
                                  BaseState* toward,
                                  BaseStateTransition* transition
                                 ) {
        if ((toward != NULL) && (transition != NULL)) {
            m_transitions[toward] = transition ;
        }
    }

    bool BaseState::canMakeTransitionTo(BaseState* toward) {
        if (m_transitions.count(toward) == 1) {
            return m_transitions[toward] -> getCondition() ;
        }
        else {
            return false ;
        }
    }

} ;
