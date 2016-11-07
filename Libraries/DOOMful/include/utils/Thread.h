/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Thread.h                   */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/*                                         */
/* Determine the thread class to use       */
/* according to the platform.              */
/* Only include this file to get the right */
/* thread class.                           */
/*******************************************/


#ifndef __DOOM__THREAD__
#define __DOOM__THREAD__

#include <Platform.h>

// Types specific to C++ DOOMful version
#ifdef ON_WINDOWS
	#define Thread WinThread
    #include <utils/Threads/WinThread.h>
#else
	#define Thread POSIXThread
    #include <utils/Threads/POSIXThread.h>
#endif

#endif
