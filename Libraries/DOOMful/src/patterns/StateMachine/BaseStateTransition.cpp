/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		BaseStateTransition.cpp    */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/31/2015                 */
/* UPDATE:      01/31/2015                 */
/*                                         */
/* Base class to perform transitions       */
/* between states in a state machine.      */
/*******************************************/

#include <patterns/StateMachine/BaseStateTransition.h>


namespace Doom {
                                              /** CONSTRUCTION / DESTRUCTION **/
    BaseStateTransition::BaseStateTransition(BaseStateTransition::ConditionChecker condition) : m_condition(condition) {}

    BaseStateTransition::~BaseStateTransition() {}

                                                       /** GETTERS / SETTERS **/
    bool BaseStateTransition::getCondition() {
        return m_condition() ;
    }

} ;
