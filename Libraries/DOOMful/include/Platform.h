/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Processor.h                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	04/10/2014                 */
/* UPDATE:      04/10/2014                 */
/*                                         */
/* Load platform specific modules and      */
/* environment.                            */
/*******************************************/

#ifndef __DOOM_PLATFORM__
#define __DOOM_PLATFORM__

#if (defined _WIN32) || defined (_WIN64)
    #error "MS Windows is not yet a supported platform"

    // Compiled for Windows platforms
    #define ON_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

#elif (defined __linux__)
    // Compiled for Linux platforms
    #define ON_LINUX
    #define ON_UNIX

#elif (defined __APPLE__) || (defined __MACH__)
    #error "MacOS is not yet a supported platform"

    // Compiled for MacOS X platforms
    #define ON_MACOSX
    #define ON_UNIX

#elif (defined __unix__)
    // Compiled for other UNIX platforms
    #define ON_UNIX

#else
    #error "Unknown compilation platform..."
#endif


#if (defined ON_UNIX)
    #ifndef _GNU_SOURCE
        #define _GNU_SOURCE
    #endif
    #include <unistd.h>
#endif


#if defined(__LP64__)
// LP64 machine, OS X or Linux
    #define PTR64
#elif defined(_WIN64)
// LLP64 machine, Windows
    #define PTR64
#else
// 32-bit machine, Windows or Linux or OS X
    #define PTR32
#endif


#endif // __DOOM_PLATFORM__
