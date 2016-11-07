/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		BaseStateTransition.h      */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/31/2015                 */
/* UPDATE:      01/31/2015                 */
/*                                         */
/* Base class to perform transitions       */
/* between states in a state machine.      */
/*******************************************/

#ifndef __DOOM__BASE_STATE_TRANSITION__
#define __DOOM__BASE_STATE_TRANSITION__


namespace Doom {

    /**
     * @brief   Base class to perform transitions between states in a state
     *          machine.
     * @author  CB (c) 2015
     * @version 0.1     2015/01/31
     */
    class BaseStateTransition {
        public:
            /**
             * @brief   Function pointer used to check the conditions of the
             *          transition.
             */
            typedef bool (*ConditionChecker)() ;


        private:
            /**
             * @brief   Pointer to the function that checks the transition can
             *          be performed.
             */
            ConditionChecker m_condition ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new BaseStateTransition.
             * @param   condition   Pointer to the function that checks the
             *                      transition can be performed.
             */
            BaseStateTransition(ConditionChecker condition) ;

            /**
             * @brief   Destruction of the BaseStateTransition.
             */
            virtual ~BaseStateTransition() ;

                                                       /** GETTERS / SETTERS **/
            /**
             * @brief   Get the condition value.
             * @return  Value of the condition : TRUE if satisfied, FALSE else.
             */
            bool getCondition() ;
    } ;

} ;

#endif
