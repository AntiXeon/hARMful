/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Mutex.h                    */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    02/17/2015                 */
/* UPDATE:      02/17/2015                 */
/*                                         */
/* A Mutex helps to control concurrent     */
/* accesses.                               */
/*******************************************/

#ifndef __DOOM__MUTEX__
#define __DOOM__MUTEX__


extern "C" {
    #include <pthread.h>
} ;


namespace Doom {

    /**
     * @brief   A Mutex helps to control concurrent accesses.
     *          This is an abstraction of the pthread mutex.
     * @author  CB (c) 2015
     * @version 0.1     2015/02/17
     */
    class Mutex {

        private:
            /**
             * @brief   Attributes of the mutex.
             */
            pthread_mutexattr_t m_attributes ;

            /**
             * @brief   Underlying mutex.
             */
            pthread_mutex_t m_mutex ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new Mutex.
             */
            Mutex() ;

            /**
             * @brief   Destruction of the Mutex.
             */
            virtual ~Mutex() ;


                                                               /** UTILITIES **/
            /**
             * @brief   Lock the Mutex and avoid another access to the critical
             *          section until unlock() is called. The thread is blocked
             *          until the Mutex is unlocked.
             */
            void lock() const ;


            /**
             * @brief   Try to get a Mutex. If it is not the case, the call
             *          returns immediately, without blocking the thread.
             */
            void try_lock() const ;


            /**
             * @brief   Unlock the Mutex to end a critical section.
             */
            void unlock() const ;

    } ;

} ;


#endif
