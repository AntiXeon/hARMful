/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       SizedStack.h               */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    02/17/2015                 */
/* UPDATE:      02/17/2015                 */
/*                                         */
/* A SizedStack is a stack with a          */
/* predefined size.                        */
/*******************************************/

#ifndef __DOOM__SIZED_STACK__
#define __DOOM__SIZED_STACK__


#include <utils/Mutex.h>
#include <debug/Test.h>


namespace Doom {

    /**
    * @brief   A SizedStack is a stack with a predefined size.
    * @author  CB (c) 2015
    * @version 0.1     2015/02/17
    */
    template <class T>
    class SizedStack {

        private:
            /**
             * @brief   Array representing the SizedStack.
             */
            T* m_stack ;

            /**
             * @brief   Top of the SizedStack.
             */
            char m_top ;

            /**
             * @brief   Current size of the SizedStack.
             */
            char m_size ;

            /**
             * @brief   Maximal size of the SizedStack.
             */
            char m_maxSize ;


            /**
             * @brief   Mutex to manage concurrent accesses.
             */
            Mutex m_mutex ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a SizedStack with a predefined maximal size.
             * @param   maxSize     Maximal size of the SizedStack.
             */
            SizedStack(char maxSize) ;

            /**
             * @brief   Destruction of the SizedStack.
             */
            virtual ~SizedStack() ;


                                                               /** UTILITIES **/
            /**
             * @brief   Push a new value to the top of the SizedStack.
             * @param   value   The value to insert.
             */
            void push(const T& value) ;

            /**
             * @brief   Remove the element on top of the SizedStack.
             */
            void pop() ;


                                                                 /** GETTERS **/
            /**
             * @brief   Test whether the SizedStack is empty.
             * @return  TRUE if the stack is empty, FALSE if it contains at
             *          least one element.
             */
            bool empty() ;

            /**
             * @brief   Get the size of the SizedStack.
             * @return  The current size of the SizedStack.
             */
            unsigned char size() ;

            /**
             * @brief   Get the top element of the SizedStack.
             * @return  The top element of the SizedStack.
             */
            T& top() ;


        private:
            /**
             * @brief   Class invariant.
             */
            void invariant() ;
    } ;

    #include "SizedStack/SizedStack.impl"

} ;


#endif
