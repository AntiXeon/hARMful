/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       NULLPointerException.h     */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    22/03/2015                 */
/* UPDATE:      22/03/2015                 */
/*                                         */
/* NULLPointerException when a pointer is  */
/* NULL while it should not be.            */
/*******************************************/


#ifndef __DOOM__NULL_POINTER_EXCEPTION__
#define __DOOM__NULL_POINTER_EXCEPTION__

#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   NULLPointerException is thrown when a pointer is NULL while it
     *          should not be.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class NULLPointerException : public Exception {
        DECLARE_EXCEPTION(NULLPointerException)
    } ;

} ;


#endif
