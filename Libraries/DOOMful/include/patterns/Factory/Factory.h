/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Factory.h                  */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    09/30/2015                 */
/* UPDATE:      09/30/2015                 */
/*                                         */
/* A Factory creates new objects.          */
/*******************************************/

#ifndef __DOOM__FACTORY__
#define __DOOM__FACTORY__


namespace Doom {

    /**
     * @brief   A Factory creates new objects.
     * @author  CB (c) 2015
     * @version 0.1     2015/09/30
     */
    template <class TClass, class TInterface>
    class Factory {
        public:
            /** @brief  Creation of a Factory. */
            Factory() ;

            /** @brief  Destruction of the Factory. */
            virtual ~Factory() ;

            /** @brief  Create an object from the Factory. */
            TInterface* create() ;
    } ;

    #include "Factory.impl"

} ;


#endif
