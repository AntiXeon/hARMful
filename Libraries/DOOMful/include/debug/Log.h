/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* File : 		Log.h                      */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/28/2014                 */
/* UPDATE:      03/28/2014                 */
/*                                         */
/* Functions to easily generate log files. */
/*******************************************/

#ifndef __DOOM__LOG__
#define __DOOM__LOG__

#include "Print.h"
#include "../Types.h"


#define TERMTEXT_MSG_INFO       TERMTEXT_BOLD TERMTEXT_CYAN
#define TERMTEXT_MSG_DEBUG      TERMTEXT_BOLD TERMTEXT_GREEN
#define TERMTEXT_MSG_WARNING    TERMTEXT_BOLD TERMTEXT_YELLOW
#define TERMTEXT_MSG_ERROR      TERMTEXT_BOLD TERMTEXT_RED


/**
 * @brief	Print an information text.
 * @param   text    The text of the information.
 */
#define PRINT_INFO(text) 	printf(TERMTEXT_MSG_INFO text TERMTEXT_DEFAULT "\n")

/**
 * @brief	Print a debug text.
 * @param   text    The text of the debug.
 */
#define PRINT_DEBUG(text) printf(TERMTEXT_MSG_DEBUG text TERMTEXT_DEFAULT "\n")

/**
 * @brief	Print a warning text.
 * @param   text    The text of the warning.
 */
#define PRINT_WARNING(text) printf(TERMTEXT_MSG_WARNING text TERMTEXT_DEFAULT "\n")

/**
 * @brief	Print an error text.
 * @param   text    The text of the error.
 */
#define PRINT_ERROR(text) 	printf(TERMTEXT_MSG_ERROR text TERMTEXT_DEFAULT "\n")



namespace Doom {

	namespace Log {

		/**
		 * @brief	Available log levels.
		 */
		enum Level {
					LogCritical,
				    LogError,
				    LogWarning,
				    LogInfo,
				    LogDebug
				   } ;

		/**
		 * @brief   Initialize the log system.
		 * @param   filepath    File path to write logs.
		 * @param   limit       Limit level to log some messages only.
		 */
		void InitSystem(
						const char* filepath,
	                    const Level& limit
					   ) ;

		/**
		 * @brief   Write a log message to the log journal.
		 * @param   level       Level of the message to filter unwanted ones.
		 * @param   format      Format of the message.
		 * @param   ...         Parameters to write variable values to the log
		 *						journal.
		 */
		void Write(const Level& level, const char* format, ...) ;

		/**
		 * @brief   Write a log message to the log journal and print it on terminal.
		 * @param   level       Level of the message to filter unwanted ones.
		 * @param   format      Format of the message.
		 * @param   ...         Parameters to write variable values to the log
		 *						journal.
		 */
		void WritePrint(const Level& level, const char* format, ...) ;

		/**
		 * @brief  	Close the log file.
		 */
		void Stop() ;


		/**
		 * @brief  	To know if the logging system is ready to be used.
		 */
		bool IsReady() ;

	} ;

} ;


#endif
