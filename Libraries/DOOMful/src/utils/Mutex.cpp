/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Mutex.cpp                  */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    02/17/2015                 */
/* UPDATE:      02/17/2015                 */
/*                                         */
/* A Mutex helps to control concurrent     */
/* accesses.                               */
/*******************************************/

#ifdef __cplusplus


#include <utils/Mutex.h>
#include <debug/Log.h>
#include <debug/Test.h>


namespace Doom {

                                              /** CONSTRUCTION / DESTRUCTION **/
    Mutex::Mutex() {
        errno = 0 ;
        pthread_mutexattr_init(&m_attributes) ;
        STOP_ON_ERRNO() ;
        pthread_mutexattr_settype(&m_attributes, PTHREAD_MUTEX_ERRORCHECK) ;
        STOP_ON_ERRNO() ;

        pthread_mutex_init(&m_mutex, &m_attributes) ;
        STOP_ON_ERRNO() ;
    }

    Mutex::~Mutex() {
        errno = 0 ;
        pthread_mutex_destroy(&m_mutex) ;
        STOP_ON_ERRNO() ;
    }


                                                               /** UTILITIES **/
    void Mutex::lock() const {
        errno = 0 ;
        errno = pthread_mutex_lock((pthread_mutex_t*) &m_mutex) ;
        STOP_ON_ERRNO() ;
    }


    void Mutex::try_lock() const {
        errno = 0 ;
        errno = pthread_mutex_trylock((pthread_mutex_t*) &m_mutex) ;
        STOP_ON_ERRNO() ;
    }


    void Mutex::unlock() const {
        errno = 0 ;
        errno = pthread_mutex_unlock((pthread_mutex_t*) &m_mutex) ;
        STOP_ON_ERRNO() ;
    }

} ;


#endif
