#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include "ObserverInterface.h"

#include <assert.h>
#include <semaphore.h>
#include <set>

class ObserverInterface ;

/**
 * @brief Abstract class based on the Java implementation of the ObserverInterface
 *        pattern design.
 *        An observable object can notify its ObserverInterfaces in order to make them
 *        update data of the observable object itself : they can handle
 *        inaccessible data to the observable object.
 */
class Observable {
    private:
        /** @brief To know if the observable object has changed. */
        bool m_hasChanged ;

        /** @brief List of ObserverInterfaces. */
        std::set<ObserverInterface*> m_ObserverInterfaces ;

        /**
         * @brief Regulate the access to the object to avoid concurrency
         *        problems.
         */
        sem_t m_access ;

    public:
                                                            /** CONSTRUCTORS **/
        /** @brief Create the Observable object. */
        Observable() {
            assert(sem_init(&m_access, 0, 1) == 0) ;
        }

        /** @brief Destroy the Observable object. */
        virtual ~Observable() {}

                                                               /** UTILITIES **/
        /**
         * @brief Add an ObserverInterface.
         * @param o     The ObserverInterface of the current object.
         */
        virtual void addObserver(ObserverInterface* o) {
            sem_wait(&m_access) ;

            if (o == 0) {
                sem_post(&m_access) ;
                assert(false) ;
            }

            if (m_ObserverInterfaces.count(o) == 0)
                m_ObserverInterfaces.insert(o) ;
            
            sem_post(&m_access) ;
        }

        /**
         * @brief Remove an ObserverInterface.
         * @param o     The ObserverInterface to remove.
         */
        virtual void removeObserver(ObserverInterface* o) {
            sem_wait(&m_access) ;
            // Safely delete from the set...
            m_ObserverInterfaces.erase(o) ;
            sem_post(&m_access) ;
        }

        /**
         * @brief Clear the list of ObserverInterfaces.
         */
        virtual void removeObservers() {
            sem_wait(&m_access) ;
            m_ObserverInterfaces.clear() ;
            sem_post(&m_access) ;
        }

        /**
         * @brief If the object has changed, ObserverInterfaces must be notified.
         *        The object is then set as not changed anymore.
         */
        virtual void notifyObservers() {
            notifyObservers(0) ;
        }

        /**
         * @brief If the object has changed, ObserverInterfaces must be notified.
         *        The object is then set as not changed anymore.
         * @param arg   The argument to give to the ObserverInterfaces.
         */
        virtual void notifyObservers(void* arg) {
            sem_wait(&m_access) ;
            /* Just make a "shot" of the current list of ObserverInterfaces to safely
               iterate on it */
            std::set<ObserverInterface*> copy = m_ObserverInterfaces ;
            // Fix the state of the object for the copied list of ObserverInterfaces
            m_hasChanged = false ;
            sem_post(&m_access) ;


            std::set<ObserverInterface*>::reverse_iterator it ;
            for (it = copy.rbegin() ; it != copy.rend() ; it++) {
                (*it) -> update(this, arg) ;
            }
        }

        /**
         * @brief To know if the object has changed.
         * @return TRUE if the object has changed, FALSE else.
         */
        virtual bool hasChanged() {
            sem_wait(&m_access) ;
            bool change = m_hasChanged ;
            sem_post(&m_access) ;
            return change ;
        }

        /**
         * @brief Count how many ObserverInterfaces are listed for the current object.
         * @return Amount of ObserverInterfaces on the current object.
         */
        virtual unsigned int countObservers() {
            sem_wait(&m_access) ;
            unsigned int count = m_ObserverInterfaces.size() ;
            sem_post(&m_access) ;
            return count ;
        }

    protected:
        /**
         * @brief Set the object as changed.
         */
        virtual void setChanged() {
            sem_wait(&m_access) ;
            m_hasChanged = true ;
            sem_post(&m_access) ;
        }

        /**
         * @brief Set the object as unchanged.
         */
        virtual void clearChanged() {
            sem_wait(&m_access) ;
            m_hasChanged = false ;
            sem_post(&m_access) ;
        }
} ;

#endif
