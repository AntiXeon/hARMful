/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       IOException.h              */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    26/02/2015                 */
/* UPDATE:      26/02/2015                 */
/*                                         */
/* An IOException is generally thrown by   */
/* input/output operations, on files,      */
/* streams or buffers. For example :       */
/* opening, closing, reading or writing    */
/* data.                                   */
/*******************************************/


#ifndef __DOOM__IO_EXCEPTION__
#define __DOOM__IO_EXCEPTION__


#include "Exception.h"
#include <string>


namespace Doom {

    /**
     * @brief   An IOException is generally thrown by input/output operations, on
     *          files, streams or buffers. For example : opening, closing, reading
     *          or writing data.
     * @version 1.0 04/22/2014
     * @author  Denis CARLUS
     * @see     ExceptionSkeleton.h
     */
    class IOException : public Exception {
        DECLARE_EXCEPTION(IOException)
    } ;

} ;


#endif
