/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		POSIXThread.h              */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/10/2016                 */
/* UPDATE:      01/10/2016                 */
/*                                         */
/* POSIX thread to run multithreaded       */
/* applications on supporting operating    */
/* systems.                                */
/*******************************************/

#ifndef ON_WINDOWS

    #ifndef __DOOM__POSIX_THREAD__
    #define __DOOM__POSIX_THREAD__

    #include <utils/Threads/AbstractThread.h>
    #include <utils/PairList.h>
    #include <pthread.h>
    #include <string>

namespace Doom {

   /**
    * @brief   POSIX thread to run multithreaded applications on supporting
    *          operation systems.
    * @author  CB (c) 2016
    * @version 0.1     2016/01/10
    */
    class POSIXThread : public AbstractThread {

        private:
            /**
             * @brief   Inner thread corresponding to a POSIX thread.
             */
            pthread_t m_thread ;


        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a new POSIXThread.
             */
            POSIXThread() ;

            /**
             * @brief   Destruction of the thread.
             */
            virtual ~POSIXThread() ;


                                                     /** FROM AbstractThread **/
            /**
             * @brief   Wait for the end of the thread execution.
             * @return  Returned value by the thread routine.
             */
            void* join() ;

            /**
             * @brief   Make the thread stop as soon as possible, in a proper
             *          manner.
             * @return  Returned value by the thread routine. NULL if the
             *          routine has been canceled.
             * @warning Do not call this method if the thread has blocking
             *          functions or no stop condition. It could freeze the
             *          whole application.
             */
            void* stop() ;

            /**
             * @brief   Cancel the thread execution.
             */
            void cancel() ;


        private:
            /**
             * @brief   Make the thread run its related function.
             */
            void run() ;

            /**
             * @brief   Run the thread with all the managed behaviors.
             * @param   argThread   Thread object that must be run.
             */
            static void* ThreadMainFunction(void* argThread) ;

    } ;

} ;

    #endif  // define __DOOM__POSIX_THREAD__

#endif  // ifndef ON_WINDOWS
