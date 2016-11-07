/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       ArrayOutOfBoundException.h */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* An ArrayOutOfBoundException is thrown   */
/* when a user tries to access data from   */
/* an array that is not inside it.         */
/* For example, an access to the 42th      */
/* element of an array containing only 30  */
/* values.                                 */
/*******************************************/


#ifndef __DOOM__ARRAY_OUT_OF_BOUND_EXCEPTION__
#define __DOOM__ARRAY_OUT_OF_BOUND_EXCEPTION__

#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   An ArrayOutOfBoundException is thrown when a user tries to
     *          access data from an array that is not inside it. For example,
     *          an access to the 42th element of an array containing only 30 values.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class ArrayOutOfBoundException : public Exception {
        DECLARE_EXCEPTION(ArrayOutOfBoundException)
    } ;

} ;


#endif
