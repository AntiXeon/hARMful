/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		AbstractThread.cpp         */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/* UPDATE:      01/10/2016                 */
/*                                         */
/* Abstract class  to provide a generic    */
/* API to all available threads types.     */
/*******************************************/

#include <utils/Threads/AbstractThread.h>
#include <stddef.h>


namespace Doom {

    AbstractThread::AbstractThread() : m_state(ThreadCreated) {
        m_context.setOwner(this) ;
    }

    AbstractThread::~AbstractThread() {}


    void AbstractThread::run(
                             ThreadRoutine routine,
                             void* argument,
                             volatile bool* stopCondition
                            ) {
        m_context.setRoutine(routine) ;
        m_context.setArgument(argument) ;
        m_context.setStopCondition(stopCondition) ;
        setState(ThreadRunning) ;

        run() ;
    }

    AbstractThread::ThreadContext* AbstractThread::getContext() const {
        return (ThreadContext*) &m_context ;
    }

    AbstractThread::ThreadState AbstractThread::getState() const {
        return m_state ;
    }

    void AbstractThread::setState(const ThreadState& state) {
        m_state = state ;
    }



    AbstractThread::ThreadContext::ThreadContext() : m_owner(NULL) {}

    AbstractThread::ThreadContext::~ThreadContext() {}

    void AbstractThread::ThreadContext::setOwner(AbstractThread* owner) {
        if (m_owner == NULL) {
            m_owner = owner ;
        }
    }

    void AbstractThread::ThreadContext::setRoutine(ThreadRoutine routine) {
        m_routine = routine ;
    }

    void AbstractThread::ThreadContext::setArgument(void* argument) {
        m_argument = argument ;
    }

    void AbstractThread::ThreadContext::setStopCondition(volatile bool* stopCondition) {
        m_stopCondition = stopCondition ;
    }


    AbstractThread* AbstractThread::ThreadContext::getOwner() const {
        return m_owner ;
    }

    AbstractThread::ThreadRoutine AbstractThread::ThreadContext::getRoutine() const {
        return m_routine ;
    }

    void* AbstractThread::ThreadContext::getArgument() const {
        return m_argument ;
    }

    bool AbstractThread::ThreadContext::switchStopCondition() {
        if (m_stopCondition != NULL) {
            *m_stopCondition = !(*m_stopCondition) ;
            return true ;
        }

        return false ;
    }

} ;
