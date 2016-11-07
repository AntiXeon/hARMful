/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		CallStack.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	12/22/2015                 */
/* UPDATE:      12/22/2015                 */
/*                                         */
/* Functionality to display a callstack    */
/* when the application is ending in an    */
/* unexpected way (abort, exception, ...). */
/*******************************************/

#ifndef __DOOM__CALLSTACK__
#define __DOOM__CALLSTACK__

namespace Doom {

    namespace CallStack {

        /**
         * @brief   Initialize the callstack so that it is displayed when
         *          application is ending in an unexpected way (abord,
         *          exception, ...).
         *          This should be done at application start-up.
         * @param   maxStackFrames  Maximal amount of steps that are shown in
         *                          the trace. Default value is 15.
         */
        void Initialize(int maxStackFrames = 15) ;

    } ;

} ;

#endif
