/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       UnexpectedValueException.h */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    19/04/2015                 */
/* UPDATE:      19/04/2015                 */
/*                                         */
/* An UnexpectedValueException is thrown   */
/* when a value that should not be given   */
/* is found.                               */
/*******************************************/


#ifndef __DOOM__UNEXPECTED_VALUE_EXCEPTION__
#define __DOOM__UNEXPECTED_VALUE_EXCEPTION__


#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   An UnexpectedValueException is thrown when a value that should not
     *          be given is found.
     * @version 1.0 19/04/2015
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class UnexpectedValueException : public Exception {
        DECLARE_EXCEPTION(UnexpectedValueException)
    } ;

} ;


#endif
