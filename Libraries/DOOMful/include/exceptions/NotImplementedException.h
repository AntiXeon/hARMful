/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       NotImplementedException.h  */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* A NotImplementedException is thrown     */
/* when a functionality is not yet         */
/* implemented.                            */
/*******************************************/


#ifndef __DOOM__NOTIMPLEMENTED_EXCEPTION__
#define __DOOM__NOTIMPLEMENTED_EXCEPTION__


#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   A NotImplementedException is thrown when a functionality is not yet
     *          implemented.
     * @version 1.0 03/09/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class NotImplementedException : public Exception {
        DECLARE_EXCEPTION(NotImplementedException)
    } ;

} ;


#endif
