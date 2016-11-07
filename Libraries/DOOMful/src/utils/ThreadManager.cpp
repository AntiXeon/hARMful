#include <utils/ThreadManager.h>
#include <DOOMStrings.h>
#include <utils/Mutex.h>
#include <debug/Test.h>
#include <debug/Log.h>
#include <map>

namespace Doom {

    namespace ThreadManager {

        /** @brief  All threads created by user. */
        static std::map<std::string, Thread> Threads ;
        /** @brief  Mutex to protect ther manager data. */
        static Mutex ManagerMutex ;
        /** @brief Errno value for unknown process. */
        static const int NoSuchProcess = ESRCH ;


        bool Run(
                 const std::string& threadName,
                 Thread::ThreadRoutine routine,
                 void* argument,
                 volatile bool* stopCondition
                ) {
            bool returnedValue ;

            ManagerMutex.lock() ;
                if (Threads.count(threadName) == 0) {
                    Threads[threadName] = Thread() ;
                    AbstractThread* thread = &(Threads[threadName]) ;
                    thread -> run(routine, argument, stopCondition) ;
                    returnedValue = true ;
                }
                else {
                    Log::Write(
                               Log::LogWarning,
                               ThreadManagerMsg::Error::AlreadyInUse,
                               threadName.c_str()
                              ) ;
                    returnedValue = false ;
                }
            ManagerMutex.unlock() ;

            return returnedValue ;
        }

        bool IsRunning(const std::string& threadName) {
            bool returnedValue ;

            ManagerMutex.lock() ;
                if (Threads.count(threadName) == 1) {
                    errno = 0 ;
                    AbstractThread::ThreadState state = Threads[threadName].getState() ;
                    returnedValue = (state == AbstractThread::ThreadRunning) ;
                }
                else {
                    Log::Write(
                               Log::LogWarning,
                               ThreadManagerMsg::Error::NotRegistered,
                               threadName.c_str()
                              ) ;

                    errno = NoSuchProcess ;
                    returnedValue = false ;
                }
            ManagerMutex.unlock() ;

            return returnedValue ;
        }

        void* Join(const std::string& threadName) {
            void* returnedValue ;

            ManagerMutex.lock() ;
                if (Threads.count(threadName) == 1) {
                    errno = 0 ;     // No error
                    returnedValue = Threads[threadName].join() ;
                    Threads.erase(threadName) ;
                }
                else {
                    Log::Write(
                               Log::LogWarning,
                               ThreadManagerMsg::Error::NotRegistered,
                               threadName.c_str()
                              ) ;

                    errno = NoSuchProcess ;
                    returnedValue = NULL ;
                }
            ManagerMutex.unlock() ;

            return returnedValue ;
        }

        void* Stop(const std::string& threadName) {
            void* returnedValue ;

            ManagerMutex.lock() ;
                if (Threads.count(threadName) == 1) {
                    errno = 0 ;     // No error
                    returnedValue = Threads[threadName].stop() ;
                    Threads.erase(threadName) ;
                }
                else {
                    Log::Write(
                               Log::LogWarning,
                               ThreadManagerMsg::Error::NotRegistered,
                               threadName.c_str()
                              ) ;

                    errno = NoSuchProcess ;
                    returnedValue = NULL ;
                }
            ManagerMutex.unlock() ;

            return returnedValue ;
        }

        void StopAll() {
            ManagerMutex.lock() ;
                std::map<std::string, Thread>::iterator it = Threads.begin() ;
                for (; it != Threads.end() ; ++it) {
                    (*it).second.stop() ;
                }

                Threads.clear() ;
            ManagerMutex.unlock() ;
        }

    } ;

} ;
