/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Time.h                     */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/30/2014                 */
/* UPDATE:      03/30/2014                 */
/*                                         */
/* Macro and functions to easily handle    */
/* date and time access, conversions and   */
/* other manipulations.                    */
/*******************************************/

#ifndef __DOOM__TIME__
#define __DOOM__TIME__

#include <stdlib.h>


namespace Doom {

	namespace Time {
		/** @brief 	Minimal buffer size for date storage. */
		const unsigned int DateBufferSize = 9 ;

		/** @brief 	Minimal buffer size for time storage. */
		const unsigned int TimeBufferSize = 9 ;

		/** @brief 	Minimal buffer size for date time storage. */
		const unsigned int DateTimeBufferSize = 21 ;


		/**
		 * @brief   Get a human-readable string of date and time.
		 * @param   dateTimeBuffer  Buffer where the string is written.
		 * @param   bufferSize      Size of the buffer.
		 * @return  dateTimeBuffer is returned for convenience of use.
		 * @warning Minimal buffer size of DATETIME_BUFFER_SIZE.
		 */
		char* GetDateTime(char* dateTimeBuffer, size_t bufferSize) ;

		/**
		 * @brief   Get a human-readable string of date.
		 * @param   dateBuffer      Buffer where the string is written.
		 * @param   bufferSize      Size of the buffer.
		 * @return  dateBuffer is returned for convenience of use.
		 * @warning Minimal buffer size of DATE_BUFFER_SIZE.
		 */
		char* GetDate(char* dateBuffer, size_t bufferSize) ;

		/**
		 * @brief   Get a human-readable string of time.
		 * @param   timeBuffer      Buffer where the string is written.
		 * @param   bufferSize      Size of the buffer.
		 * @return  timeBuffer is returned for convenience of use.
		 * @warning Minimal buffer size of TIME_BUFFER_SIZE.
		 */
		char* GetTime(char* timeBuffer, size_t bufferSize) ;

	} ;

} ;


#endif
