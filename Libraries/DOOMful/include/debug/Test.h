/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Test.h                     */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/22/2014                 */
/* UPDATE:      03/22/2014                 */
/*                                         */
/* Macro and functions to perform tests,   */
/* assertions and various bug tracking     */
/* tools.                                  */
/*******************************************/

#ifndef __DOOM__TEST__
#define __DOOM__TEST__

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Log.h"
#include "Print.h"


/**
 * @brief   Check if a condition is checked. An error message is displayed when
 *          the condition is wrong.
 * @param   cond    The condition to be checked.
 * @param   error   The error message to display if the condition is bad.
 */
#define CHECK_CONDITION(cond, msg) {                                        	\
    if (cond == 0) {                                                        	\
        Doom::Log::WritePrint(													\
							  Doom::Log::LogError,                              \
			                  "[%s:%d %s() %s] %s",                             \
			                  __FILE__,                                         \
			        		  __LINE__,                                         \
			        		  __func__,                                         \
			        		  GET_VAR_NAME(cond),                               \
			        		  msg												\
						     ) ;                                                \
    }                                                                       	\
}

/**
 * @brief   Check if a condition is checked. An error message is displayed when
 *          the condition is wrong and the program exits.
 * @param   cond    The condition to be checked.
 * @param   error   The error message to display if the condition is bad.
 */
#define ABORT_CONDITION(cond, msg) {                                        	\
    if (cond == 0) {                                                        	\
        Doom::Log::WritePrint(												    \
							  Doom::Log::LogError,                              \
	                 		  "[%s:%d %s() %s] %s",                             \
			                  __FILE__,                                         \
			        		  __LINE__,                                         \
			        		  __func__,                                         \
			        		  GET_VAR_NAME(cond),                               \
			        		  msg												\
					   		 ) ;                                                \
        abort() ;                                                           	\
    }                                                                       	\
}


/**
 * @brief   Log the file, function and line of an error.
 * @param   type    The type of log message.
 */
#define LOG_FILEINFO(type) {                                                	\
    Doom::Log::WritePrint(                                                      \
	               		  type,                                                 \
	               		  "%s:%d %s()",                                         \
	               		  __FILE__,                                             \
	               		  __LINE__,                                             \
	               		  __func__                                              \
            	  		 ) ;                                                    \
}


/**
 * @brief   Check a condition. A warning message is displayed when the condition
 *          is wrong.
 * @param   DOOM_File_With_Error        The file where the error occurred.
 * @param   DOOM_Line_With_Error        Line where the error occurred.
 * @param   DOOM_Function_With_Error    Function in which the StopOnErrno() one
 *                                      is called.
 */
void PrintErrno(
				const char* DOOM_File_With_Error,
				int DOOM_Line_With_Error,
				const char* DOOM_Function_With_Error
               ) ;

/**
 * @brief   Check a condition. An error message is displayed when the condition
 *          is wrong and the program exits.
 * @param   DOOM_File_With_Error        The file where the error occurred.
 * @param   DOOM_Line_With_Error        Line where the error occurred.
 * @param   DOOM_Function_With_Error    Function in which the StopOnErrno() one
 *                                      is called.
 */
void StopOnErrno(
                 const char* DOOM_File_With_Error,
                 int DOOM_Line_With_Error,
                 const char* DOOM_Function_With_Error
                ) ;

/**
 * @brief   Check a condition. An error message is displayed when the condition
 *          is wrong and the program exits. An additional message defined by
 *          the user can be added.
 * @param   DOOM_File_With_Error        The file where the error occurred.
 * @param   DOOM_Line_With_Error        Line where the error occurred.
 * @param   DOOM_Function_With_Error    Function in which the StopOnErrno() one
 *                                      is called.
 * @param   User_Message                Message written by the user to complete
 *                                      the errno message.
 */
void StopOnErrnoWithMsg(
                        const char* DOOM_File_With_Error,
                        int DOOM_Line_With_Error,
                        const char* DOOM_Function_With_Error,
                        const char* User_Message
                       ) ;

#define WARN_ON_ERRNO() PrintErrno(__FILE__, __LINE__, __func__)

/**
 * @brief   Check if a condition is checked. An error message is displayed when
 *          the condition is wrong and the program exits.
 */
#define STOP_ON_ERRNO() StopOnErrno(__FILE__, __LINE__, __func__)

 /**
 * @brief   Check if a condition is checked. An error message is displayed when
 *          the condition is wrong and the program exits.
 * @param   msg     Add a user message.
 */
#define STOP_ON_ERRNO_MSG(msg) StopOnErrnoWithMsg(__FILE__, __LINE__, __func__, msg)


/** @brief  Enter critical section with the given semaphore. */
#define ENTER_CRITICAL_SECTION(mutex) pthread_mutex_lock((pthread_mutex_t*) &mutex)
/** @brief  Leave critical section with the given semaphore. */
#define LEAVE_CRITICAL_SECTION(mutex) pthread_mutex_unlock((pthread_mutex_t*) &mutex)


#endif
