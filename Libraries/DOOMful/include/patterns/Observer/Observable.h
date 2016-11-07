/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Observable.h               */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.1                        */
/* CREATION:	03/31/2014                 */
/* UPDATE:      03/31/2014                 */
/*                                         */
/* Base class to handle the Observer       */
/* design pattern, in combination with the */
/* ObserverInterface.                      */
/*                                         */
/* V1.1: Replace semaphore by Mutex.       */
/*******************************************/

#ifndef __DOOM__OBSERVABLE__
#define __DOOM__OBSERVABLE__

#include "ObserverInterface.h"

#include <assert.h>
#include <set>
#include <utils/Mutex.h>


namespace Doom {

    class ObserverInterface ;


    /**
    * @brief Abstract class based on the Java implementation of the
    *        Observer design pattern.
    *        An observable object can notify its ObserverInterfaces in order to
    *        make them update data of the observable object itself : they can
    *        handle inaccessible data to the observable object.
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
            Doom::Mutex m_access ;

        public:
                                                            /** CONSTRUCTORS **/
            /** @brief Create the Observable object. */
            Observable() ;

            /** @brief Destroy the Observable object. */
            virtual ~Observable() ;

                                                               /** UTILITIES **/
            /**
            * @brief Add an ObserverInterface.
            * @param o     The ObserverInterface of the current object.
            */
            virtual void addObserver(ObserverInterface* o) ;

            /**
            * @brief Remove an ObserverInterface.
            * @param o     The ObserverInterface to remove.
            */
            virtual void removeObserver(ObserverInterface* o) ;

            /**
            * @brief Clear the list of ObserverInterfaces.
            */
            virtual void removeObservers() ;

            /**
            * @brief If the object has changed, ObserverInterfaces must be
            *        notified.
            *        The object is then set as not changed anymore.
            */
            virtual void notifyObservers() ;

            /**
            * @brief If the object has changed, ObserverInterfaces must be
            *        notified.
            *        The object is then set as not changed anymore.
            * @param arg   The argument to give to the ObserverInterfaces.
            */
            virtual void notifyObservers(void* arg) ;

            /**
            * @brief To know if the object has changed.
            * @return TRUE if the object has changed, FALSE else.
            */
            virtual bool hasChanged() ;

            /**
            * @brief Count how many ObserverInterfaces are listed for the
            *        current object.
            * @return Amount of ObserverInterfaces on the current object.
            */
            virtual unsigned int countObservers() ;


        protected:
            /**
            * @brief Set the object as changed.
            */
            virtual void setChanged() ;

            /**
            * @brief Set the object as unchanged.
            */
            virtual void clearChanged() ;
    } ;

} ;

#endif
