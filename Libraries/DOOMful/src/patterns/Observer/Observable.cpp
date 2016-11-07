/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Observable.cpp             */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.1                        */
/* CREATION:	03/31/2014                 */
/* UPDATE:      03/31/2014                 */
/*                                         */
/* Base class to handle the Observer       */
/* design pattern, in combination with the */
/* ObserverInterface.                      */
/*******************************************/

#include <patterns/Observer/Observable.h>


namespace Doom {

                                                            /** CONSTRUCTORS **/
    Observable::Observable() {}

    Observable::~Observable() {}

                                                               /** UTILITIES **/
    void Observable::addObserver(ObserverInterface* o) {
        m_access.lock() ;

        if (o == 0) {
            m_access.unlock() ;
            assert(false) ;
        }

        if (m_ObserverInterfaces.count(o) == 0)
            m_ObserverInterfaces.insert(o) ;

        m_access.unlock() ;
    }

    void Observable::removeObserver(ObserverInterface* o) {
        m_access.lock() ;
        // Safely delete from the set...
        m_ObserverInterfaces.erase(o) ;
        m_access.unlock() ;
    }

    void Observable::removeObservers() {
        m_access.lock() ;
        m_ObserverInterfaces.clear() ;
        m_access.unlock() ;
    }

    void Observable::notifyObservers() {
        notifyObservers(0) ;
    }

    void Observable::notifyObservers(void* arg) {
        m_access.lock() ;
        /* Just make a "shot" of the current list of ObserverInterfaces to
         * safely iterate on it */
        std::set<ObserverInterface*> copy = m_ObserverInterfaces ;
        // Fix the state of the object for the copied list of ObserverInterfaces
        m_hasChanged = false ;
        m_access.unlock() ;


        std::set<ObserverInterface*>::reverse_iterator it ;
        for (it = copy.rbegin() ; it != copy.rend() ; it++) {
            (*it) -> update(this, arg) ;
        }
    }

    bool Observable::hasChanged() {
        m_access.lock() ;
        bool change = m_hasChanged ;
        m_access.unlock() ;
        return change ;
    }

    unsigned int Observable::countObservers() {
        m_access.lock() ;
        unsigned int count = m_ObserverInterfaces.size() ;
        m_access.unlock() ;
        return count ;
    }


    void Observable::setChanged() {
        m_access.lock() ;
        m_hasChanged = true ;
        m_access.unlock() ;
    }

    void Observable::clearChanged() {
        m_access.lock() ;
        m_hasChanged = false ;
        m_access.unlock() ;
    }

} ;
