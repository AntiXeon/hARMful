#ifndef __OBSERVERINTERFACE_H__
#define __OBSERVERINTERFACE_H__

class Observable ;

/**
 * @brief Abstract class (interface) to set the Observer pattern design.
 *        It is based on the Java implementation of the Observer pattern design.
 * @version 1.0
 */
class ObserverInterface {
    public:
        virtual void update(Observable* obs, void* arg) = 0 ;
} ;

#endif
