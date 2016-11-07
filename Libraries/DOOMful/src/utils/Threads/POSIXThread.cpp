/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		POSIXThread.h              */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/* UPDATE:      01/10/2016                 */
/*                                         */
/* POSIX thread to run multithreaded       */
/* applications on supporting operating    */
/* systems.                                */
/*******************************************/

#ifndef ON_WINDOWS

#include <utils/Threads/POSIXThread.h>
#include <debug/Log.h>
#include <debug/Test.h>

namespace Doom {
                                              /** CONSTRUCTION / DESTRUCTION **/
    POSIXThread::POSIXThread() : AbstractThread() {}

    POSIXThread::~POSIXThread() {}


                                                            /** FROM IThread **/
    void POSIXThread::run() {
        ThreadContext* context = (ThreadContext*) getContext() ;
        errno = pthread_create(
                               &m_thread,   // Thread data
                               NULL,        // Thread attributes, not used
                               &POSIXThread::ThreadMainFunction,
                               context
                              ) ;
        STOP_ON_ERRNO() ;
    }

    void* POSIXThread::join() {
        setState(ThreadJoining) ;
        void* returned = NULL ;
        errno = pthread_join(m_thread, &returned) ;
        STOP_ON_ERRNO() ;
        setState(ThreadJoined) ;
        return returned ;
    }

    void* POSIXThread::stop() {
        if (getContext() -> switchStopCondition()) {
            // Properly end the thread if possible.
            return join() ;
            setState(ThreadStopped) ;
        }
        else {
            // Otherwise, it can only be canceled.
            cancel() ;
            return NULL ;
        }
    }

    void POSIXThread::cancel() {
        errno = pthread_cancel(m_thread) ;
        STOP_ON_ERRNO() ;
    }

    void* POSIXThread::ThreadMainFunction(void* argThread) {
        ThreadContext* context = (ThreadContext*) argThread ;

        // Execute the thread routine, with its argument and get back the
        // returned value.
        void* returned ;
        returned = (context -> getRoutine())(context -> getArgument()) ;

        return returned ;
    }
} ;

#endif
