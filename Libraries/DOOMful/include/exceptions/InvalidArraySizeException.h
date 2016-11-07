/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       InvalidArraySizeException.h*/
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* An InvalidArraySizeException is thrown  */
/* when the size of an array is not equal  */
/* to the expected size.                   */
/*******************************************/


#ifndef __DOOM__INVALID_ARRAY_SIZE_EXCEPTION__
#define __DOOM__INVALID_ARRAY_SIZE_EXCEPTION__

#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   An InvalidArraySizeException is thrown when the size of an
     *          array is not equal to the expected size.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class InvalidArraySizeException : public Exception {
        DECLARE_EXCEPTION(InvalidArraySizeException)
    } ;

} ;


#endif
