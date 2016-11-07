/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		ObserverInterface.h        */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/31/2014                 */
/* UPDATE:      03/31/2014                 */
/*                                         */
/* Interface to manage the Observer        */
/* pattern design in combination with      */
/* Observable class.                       */
/*******************************************/


#ifndef __DOOM__OBSERVER_INTERFACE__
#define __DOOM__OBSERVER_INTERFACE__


namespace Doom {

    class Observable ;


    /**
    * @brief Interface to set the Observer pattern design.
    *        It is based on the Java implementation of the Observer pattern design.
    */
    class ObserverInterface {
        public:
            /** @brief   */
            virtual void update(Observable* obs, void* arg) = 0 ;
    } ;

} ;

#endif
