/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		Time.cpp                   */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/30/2014                 */
/* UPDATE:      03/30/2014                 */
/*                                         */
/* Macro and functions to easily handle    */
/* date and time access, conversions and   */
/* other manipulations.                    */
/*******************************************/

#include <DOOMStrings.h>
#include <utils/Time.h>
#include <debug/Test.h>
#include <debug/Log.h>
#include <time.h>

namespace Doom {

    namespace Time {

        char* GetDateTime(char* dateTimeBuffer, size_t bufferSize) {
            // Check the size of the buffer
            CHECK_CONDITION(
                            (bufferSize >= DateTimeBufferSize),
                            TimeMsg::Error::DateTimeBufferTooSmall
                           ) ;

            time_t now ;
            struct tm* timeinfo ;

            time(&now) ;
            timeinfo = localtime(&now) ;
            strftime(dateTimeBuffer, bufferSize, "%D %T", timeinfo) ;
            return dateTimeBuffer ;
        }

        char* GetDate(char* dateBuffer, size_t bufferSize) {
            // Check the size of the buffer
            CHECK_CONDITION(
                            (bufferSize >= DateBufferSize),
                            TimeMsg::Error::DateBufferTooSmall
                           ) ;

            time_t now ;
            struct tm* timeinfo ;

            time(&now) ;
            timeinfo = localtime(&now) ;
            strftime(dateBuffer, bufferSize, "%D", timeinfo) ;
            return dateBuffer ;
        }

        char* GetTime(char* timeBuffer, size_t bufferSize) {
            // Check the size of the buffer
            CHECK_CONDITION(
                            (bufferSize >= TimeBufferSize),
                            TimeMsg::Error::TimeBufferTooSmall
                           ) ;

            time_t now ;
            struct tm* timeinfo ;

            time(&now) ;
            timeinfo = localtime(&now) ;
            strftime(timeBuffer, bufferSize, "%T", timeinfo) ;
            return timeBuffer ;
        }

    } ;

} ;
