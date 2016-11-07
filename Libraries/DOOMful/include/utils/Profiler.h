/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Profiler.h                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/20/2016                 */
/* UPDATE:      01/20/2016                 */
/*                                         */
/* Profiler to follow spent time in        */
/* different parts of an application.      */
/*******************************************/

#ifndef __DOOM__PROFILER__
#define __DOOM__PROFILER__

#include <string>


namespace Doom {

    /**
     * @brief   The Profiler allows following spent time in different part of an
     *          application.
     *          - Start adding a profiling source ;
     *          - Then, declare beginning and ending of measure for such
     *            profiling source ;
     *          - When profiling for a loop time of the application is done,
     *            flush the profiler and get informations at the beginning of
     *            the next main loop.
     * @warning It is recommanded to use the macros at the end of file.
     */
    namespace Profiler {

        /** @brief  Time unit type. */
        typedef long int Time ;

        /**
         * @brief   Initialize profiler.
         */
        void Initialize() ;

        /**
         * @brief   Add a new profiling source.
         * @param   name    Name of the new source.
         */
        void AddProfilingSource(const std::string& name) ;

        /**
         * @brief   Start profiling a source.
         * @param   name    Name of the source to profile.
         * @return  ID of the profiling session for the given source.
         */
        int StartProfiling(const std::string& name) ;

        /**
         * @brief   Stop profiling a source.
         * @param   name        Name of the source to stop profiling.
         * @param   sessionID   ID of the session to stop profiling.
         * @warning If the @a sessionID value is invalid, all sessions are
         *          stopped.
         * @warning This function must be called in the same function than
         *          StartProfiling function.
         */
        void StopProfiling(const std::string& name, int sessionID) ;

        /**
         * @brief   Flush the profiler to store data until the next flush time.
         */
        void Flush() ;

        /**
         * @brief   Free all data used by the Profiler.
         */
        void Close() ;


        /**
         * @brief   Get the spent time for the given source of profiling.
         * @param   name    Name of the source of profiling.
         * @return  Cumulated time for the wanted source of profiling, zero if
         *          no such source has been registered.
         * @warning This function is always available. Notice that it only
         *          returns value of previous main loop of the software, until
         *          Flush() has been called.
         */
        Time GetTime(const std::string& name) ;

    } ;

} ;


#ifdef DEBUG
    #define Profiler_Initialize()       Doom::Profiler::Initialize()
    #define Profiler_AddSource(name)    Doom::Profiler::AddProfilingSource(name)
    #define Profiler_Start(name)        int Profiler_SessionID = Doom::Profiler::StartProfiling(name)
    #define Profiler_Stop(name)         Doom::Profiler::StopProfiling(name, Profiler_SessionID)
    #define Profiler_Flush()            Doom::Profiler::Flush()
    #define Profiler_Close()            Doom::Profiler::Close()
    #define Profiler_GetTime(name)      Doom::Profiler::GetTime(name)
#else
    #define Profiler_Initialize()
    #define Profiler_AddSource(name)
    #define Profiler_Start(name)
    #define Profiler_Stop(name)
    #define Profiler_Flush()
    #define Profiler_Close()
    #define Profiler_GetTime(name)   -1
#endif


#endif
