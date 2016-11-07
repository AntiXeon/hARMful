/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       FactoryUnableToCreateIn... */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    22/03/2015                 */
/* UPDATE:      22/03/2015                 */
/*                                         */
/* FactoryUnableToCreateInstanceException  */
/* is thrown when a factory is unable to   */
/* create a new object.                    */
/*******************************************/


#ifndef __DOOM__FACTORY_UNABLE_TO_CREATE_INSTANCE_EXCEPTION__
#define __DOOM__FACTORY_UNABLE_TO_CREATE_INSTANCE_EXCEPTION__

#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   FactoryUnableToCreateInstanceException is thrown when a factory is
     *          unable to create a new object.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class FactoryUnableToCreateInstanceException : public Exception {
        DECLARE_EXCEPTION(FactoryUnableToCreateInstanceException)
    } ;

} ;


#endif
