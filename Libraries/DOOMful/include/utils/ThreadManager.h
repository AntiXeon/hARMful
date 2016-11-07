/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       ThreadManager.h            */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/*                                         */
/* Create and destroy threads in a         */
/* controlled manner to easily provide     */
/* multithreading applications.            */
/*******************************************/

#ifndef __DOOM__THREAD_MANAGER__
#define __DOOM__THREAD_MANAGER__

#include <string>
#include <utils/Thread.h>


namespace Doom {

   /**
    * @brief   Create and destroy threads in a controlled manner to easily
    *          provide multithreading applications.
    * @author  CB (c) 2016
    * @version 0.1     2016/01/10
    */
    namespace ThreadManager {

        /**
         * @brief   Create a thread from a routine and start its execution.
         * @param   threadName      Name used to identify the thread.
         * @param   routine         The routine from which the thread starts its
         *                          execution.
         * @param   argument        Argument given to the routine.
         * @param   stopCondition   Address to the variable used as stop
         *                          condition in the thread.
         * @return  TRUE if the thread can be created, FALSE if the given name
         *          is already in use.
         */
        bool Run(
                 const std::string& threadName,
                 Thread::ThreadRoutine routine,
                 void* argument,
                 volatile bool* stopCondition
                ) ;

        /**
         * @brief   Check if a thread is running.
         * @param   threadName      Name used to identify the thread.
         * @return  TRUE if the thread is running, FALSE if it is in another
         *          state or the given name is not registered.
         * @warning Sets errno to "No such process" if given name is not
         *          registered. Returns NULL in such case.
         */
        bool IsRunning(const std::string& threadName) ;

        /**
         * @brief   Wait for the end of a thread. Otherwise, a process can be
         *          killed before its threads has finished their task.
         * @param   threadName  Name of the thread to wait.
         * @return  The returned value by the thread function. NULL on error.
         * @warning Sets errno to "No such process" if given name is not
         *          registered. Returns NULL in such case.
         */
        void* Join(const std::string& threadName) ;

        /**
         * @brief   Stop a thread with the given name.
         * @param   threadName  Name of the thread to stop.
         * @return  The returned value by the thread function. NULL on error.
         * @warning Sets errno to "No such process" if given name is not
         *          registered. Returns NULL in such case.
         */
        void* Stop(const std::string& threadName) ;

        /**
         * @brief  Stop all the running threads.
         */
        void StopAll() ;

    } ;

} ;

#endif
