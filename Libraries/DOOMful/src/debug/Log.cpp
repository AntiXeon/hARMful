/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Log.cpp                    */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/28/2014                 */
/* UPDATE:      03/28/2014                 */
/*                                         */
/* Functions to easily generate log files. */
/*******************************************/

#include <DOOMStrings.h>
#include <debug/Log.h>
#include <debug/Test.h>
#include <utils/Time.h>
#include <utils/Mutex.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>



#define PRINT_MSG_TYPE(type) {                                      \
    switch (type) {                                                 \
		case Doom::Log::LogCritical:								\
        case Doom::Log::LogError:                                   \
            printf(TERMTEXT_MSG_ERROR) ;                            \
            break ;                                                 \
                                                                    \
        case Doom::Log::LogWarning:                                 \
            printf(TERMTEXT_MSG_WARNING) ;                          \
            break ;                                                 \
                                                                    \
        case Doom::Log::LogInfo:                                    \
            printf(TERMTEXT_MSG_INFO) ;                             \
            break ;                                                 \
                                                                    \
        case Doom::Log::LogDebug:                                   \
            printf(TERMTEXT_MSG_DEBUG) ;                            \
            break ;                                                 \
    }                                                               \
}




namespace Doom {

	namespace Log {

        /** @brief  Pointer to the file containing the journal. */
        FILE* JournalFile = NULL ;
        /** @brief  Limit level to log some messages only. */
        Doom::Log::Level MaxLevel = Doom::Log::LogDebug ;
        /** @brief  To know if the file is opened. */
        bool IsOpenedFile = false ;
        /**
         * @brief   Semaphore used to make the log system thread-safe on
         *          write/close.
         */
        Doom::Mutex AccessWrite ;


        void InitSystem(
                        const char* filepath,
                        const Doom::Log::Level& limit
                       ) {
            if (!filepath) {

                // Initialize the errno value as no error
                errno = 0 ;

                JournalFile = fopen(filepath, "a") ;
                STOP_ON_ERRNO() ;

                MaxLevel = limit ;
                IsOpenedFile = true ;
            }
        }

        void Output(
                    const Doom::Log::Level& level,
                    FILE* output,
                    const char* format,
                    va_list* arguments
                   ) {
            AccessWrite.lock() ;
                if (IsOpenedFile && (level <= MaxLevel)) {
                    // Check the log file is correctly opened
                    CHECK_CONDITION((output != NULL), Doom::LogMsg::Error::CannotLogToFile) ;

                    // Printf date time before log entry
                    char timeBuffer[Doom::Time::DateTimeBufferSize] ;
                    Doom::Time::GetDateTime(timeBuffer, Doom::Time::DateTimeBufferSize) ;
                    fprintf(output, "[%s] ", timeBuffer) ;

                    // Write the log message
                    vfprintf(output, format, *arguments) ;

                    // Add a end-line character if not yet written.
                    char lastCharacter = format[strlen(format) - 1] ;
                    if (lastCharacter != '\n')
                        fprintf(output, "\n") ;

                    // Flush to immediately write log to journal
                    fflush(output) ;
                }
            AccessWrite.unlock() ;
        }

        void Write(
                   const Doom::Log::Level& level,
                   const char* format,
                   ...
                  ) {
            // Write the log message
            va_list argumentsList ;
            va_start(argumentsList, format) ;
            va_end(argumentsList) ;

            Output(level, JournalFile, format, &argumentsList) ;
        }

        void WritePrint(
                        const Doom::Log::Level& level,
                        const char* format,
                        ...
                       ) {
            // Write the log message
            va_list argumentsListJournal, argumentsListPrint  ;
            va_start(argumentsListJournal, format) ;
            va_end(argumentsListJournal) ;
            va_copy(argumentsListPrint, argumentsListJournal) ;

            Output(level, JournalFile, format, &argumentsListJournal) ;

            if (level <= MaxLevel) {
                PRINT_MSG_TYPE(level) ;
                Output(level, stdout, format, &argumentsListPrint) ;
                printf(TERMTEXT_DEFAULT) ;
            }
        }

        void Stop() {
            AccessWrite.lock() ;
                fclose(JournalFile) ;
                IsOpenedFile = false ;
            AccessWrite.unlock() ;
        }

        bool IsReady() {
            AccessWrite.lock() ;
                bool isReady = IsOpenedFile ;
            AccessWrite.unlock() ;
            return isReady ;
        }

    } ;

} ;
