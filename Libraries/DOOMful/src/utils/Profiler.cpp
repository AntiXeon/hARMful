/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Profiler.pp                */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	01/20/2016                 */
/* UPDATE:      01/20/2016                 */
/*                                         */
/* Profiler to follow spent time in        */
/* different parts of an application.      */
/*******************************************/

#include <utils/Profiler.h>
#include <utils/Mutex.h>
#include <debug/Test.h>

#include <map>
#include <vector>
#include <time.h>


namespace Doom {

    namespace Profiler {

        /**
         * @brief   Protect Profiler of concurrent accesses.
         */
        static Mutex ProfilerMutex ;

        /**
         * @brief   List of sources of profiling associated to their sessions ID
         *          and times for each session ID.
         */
        static std::map< std::string, std::vector<timespec> > ProfilingQueues ;
        typedef std::map< std::string, std::vector<timespec> >::iterator ProfilingQueueIterator ;

        /**
         * @brief   Cumulated time of sessions for each profiling source on
         *          previous main loop of the software.
         */
        static std::map< std::string, Time > PreviousTotalTimes ;
        typedef std::map< std::string, Time >::iterator TotalTimesIterator ;


        /**
         * @brief   Compute difference in time.
         * @param   start   Start time data.
         * @param   end     End time data.
         * @param   diff    Output containing the difference of time between
         *                  @a start and @a end.
         * @return  @a diff parameter for convenient use.
         */
        static timespec& DiffTime(
                                  const timespec& start,
                                  const timespec& end,
                                  timespec& diff
                                 ) {
            if ((end.tv_nsec - start.tv_nsec) < 0) {
                diff.tv_sec = end.tv_sec - start.tv_sec - 1 ;
                diff.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec ;
            }
            else {
                diff.tv_sec = end.tv_sec - start.tv_sec ;
                diff.tv_nsec = end.tv_nsec - start.tv_nsec ;
            }
            return diff ;
        }

        /**
         * @brief   Convert data in timespec structure to last in microseconds.
         * @param   diff    The timespec to convert.
         * @return  Amount of microseconds in @a diff timespec structure.
         */
        static long DiffTimeValue(const timespec& diff) {
            // Convert to microseconds.
            long totalTime = (diff.tv_nsec / 1000) ;
            if (diff.tv_sec > 0) {
                totalTime += (diff.tv_sec * 1000000) ;
            }
            return totalTime ;
        }



        void Initialize() {}

        void AddProfilingSource(const std::string& name) {
            ProfilerMutex.lock() ;
                ProfilingQueues[name].reserve(4) ;
            ProfilerMutex.unlock() ;
        }

        // *** This is only supported on GNU/Linux!! ***
        int StartProfiling(const std::string& name) {
            int returnedValue = 0 ;
            ProfilerMutex.lock() ;
                int sessionID = ProfilingQueues[name].size() ;
                // CLOCK_MONOTONIC is not affected by clock change by system
                // administrator. It gives a relative value from a starting point.
                struct timespec gettime_now ;
                if (clock_gettime(CLOCK_MONOTONIC, &gettime_now) == 0) {
                    // Store the starting time (nanoseconds).
                    ProfilingQueues[name].push_back(gettime_now) ;
                    returnedValue = sessionID ;
                }
                else {
                    WARN_ON_ERRNO() ;
                    // An error occurred when getting starting time.
                    returnedValue = -1 ;
                }
            ProfilerMutex.unlock() ;
            return returnedValue ;
        }

        // *** This is only supported on GNU/Linux!! ***
        void StopProfiling(const std::string& name, int sessionID) {
            // An error occurred when getting starting time.
            if (sessionID == -1) {
                return ;
            }

            ProfilerMutex.lock() ;
                if ((ProfilingQueues.count(name) == 0)
                        || (sessionID >= (int)ProfilingQueues[name].size())) {
                    return ;
                }

                struct timespec start = ProfilingQueues[name][sessionID] ;
                struct timespec end ;
                if (clock_gettime(CLOCK_MONOTONIC, &end) == 0) {
                    struct timespec diff ;
                    ProfilingQueues[name][sessionID] = DiffTime(start, end, diff) ;
                }
                else {
                    WARN_ON_ERRNO() ;
                }
            ProfilerMutex.unlock() ;
        }

        void Flush() {
            ProfilerMutex.lock() ;
                PreviousTotalTimes.clear() ;

                // Browse each session to get their individual cumulated times.
                // The cumulated times are then stored separately.
                ProfilingQueueIterator itQueue = ProfilingQueues.begin() ;
                for (; itQueue != ProfilingQueues.end() ; ++itQueue) {
                    // Accumulate the times for each session.
                    Time cumulatedTime = 0 ;
                    size_t amountTimesSession = (itQueue -> second).size() ;
                    for (size_t timeIndex = 0 ; timeIndex < amountTimesSession ; ++timeIndex) {
                        cumulatedTime += DiffTimeValue((itQueue -> second)[timeIndex]) ;
                    }
                    // Store the cumulated time.
                    PreviousTotalTimes[(itQueue -> first)] = cumulatedTime ;
                }

                ProfilingQueues.clear() ;
            ProfilerMutex.unlock() ;
        }

        void Close() {
            ProfilerMutex.lock() ;
                PreviousTotalTimes.clear() ;
                ProfilingQueues.clear() ;
            ProfilerMutex.unlock() ;
        }

        Time GetTime(const std::string& name) {
            ProfilerMutex.lock() ;
                Time cumulatedTime = 0 ;
                if (PreviousTotalTimes.count(name) == 1) {
                    cumulatedTime = PreviousTotalTimes[name] ;
                }
            ProfilerMutex.unlock() ;
            return cumulatedTime ;
        }

    } ;

} ;
