/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		CallStack.cpp              */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	12/22/2015                 */
/* UPDATE:      12/22/2015                 */
/*                                         */
/* Functionality to display a callstack    */
/* when the application is ending in an    */
/* unexpected way (abort, exception, ...). */
/*******************************************/

#include <utils/CallStack.h>
#include <DOOMStrings.h>
#include <utils/Mutex.h>
#include <debug/Log.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>

namespace Doom {

    namespace CallStack {

        static Mutex mutexCallStack ;
        static int maxFrames ;

        static void Print(int) {
            mutexCallStack.lock() ;
                // Storage for the stack trace address data.
                void* listAddresses[maxFrames + 1] ;
                // Retrieve the current stack addresses.
                int amountOfAddresses = backtrace(
                                                  listAddresses,
                                                  sizeof(listAddresses) / sizeof(void*)
                                                 ) ;

                if (amountOfAddresses == 0) {
                    Log::Write(Log::LogError, CallStackMsg::Text::Corrupt) ;
                    return ;
                }
                else {
                    Log::Write(Log::LogError, CallStackMsg::Text::Title) ;
                }

                // Resolve the addresses to retrieve strings containing
                // filename(function+address).
                // The returned array symbolsList must be manually freed.
                char** symbolsList = backtrace_symbols(listAddresses, amountOfAddresses) ;
                // Allocate string that will containg the demangled function name.
                size_t MaxFunctionNameLength = 256 ;
                char* functionName = new char[MaxFunctionNameLength] ;

                for (int addressIndex = 0 ; addressIndex < amountOfAddresses ; ++addressIndex) {
                    char* beginName = 0 ;
                    char* beginOffset = 0 ;
                    char* endOffset = 0 ;

                    // Parse the string of the symbol to find the parentheses and "+address"
                    // offset surrounding the mangled name:
                    // ./module(function+0x12345) [0x123456789]
                    bool continueParsing = true ;
                    char* p = symbolsList[addressIndex] ;
                    for (; *p != '\0' && continueParsing ; ++p) {
                        if (*p == '(') {
                            beginName = p ;
                        }
                        else if (*p == '+') {
                            beginOffset = p ;
                        }
                        else if ((*p == ')') && (beginOffset != 0)) {
                            endOffset = p ;
                            continueParsing = false ;
                        }
                    }


                    if ((beginName != 0) && (beginOffset != 0) && (endOffset != 0) && ((beginName < beginOffset))) {
                        *beginName++ = '\0' ;
                        *beginOffset++ = '\0' ;
                        *endOffset = '\0' ;

                        // Mangled name is now in [beginName, beginOffset] and caller offset
                        // is in [beginName, endOffset]. Now apply __cxa_demangle():
                        int status ;
                        char* returnedFunctionName = abi::__cxa_demangle(beginName, functionName, &MaxFunctionNameLength, &status) ;

                        if (status == 0) {
                            // Use possibly realloc-ed string.
                            functionName = returnedFunctionName ;
                            Log::Write(
                                       Log::LogError,
                                       "  %s : %s+%s",
                                       symbolsList[addressIndex],
                                       functionName,
                                       beginOffset
                                      ) ;
                        }
                        else {
                            // Demangling failed, just output the function name as a C
                            // function without arguments.
                            Log::Write(
                                       Log::LogError,
                                       "  %s : %s()+%s",
                                       symbolsList[addressIndex],
                                       beginName,
                                       beginOffset
                                    ) ;
                        }
                    }
                    else {
                        // Unable to parse the line, print the whole line.
                        Log::Write(
                                   Log::LogError,
                                   "  %s",
                                   symbolsList[addressIndex]
                                  ) ;
                    }
                }

                delete functionName ;
                delete symbolsList ;
            mutexCallStack.unlock() ;

            abort() ;
        }


        void Initialize(int maxStackFrames) {
            maxFrames = maxStackFrames ;
            signal(SIGSEGV, Print) ;
        }

    } ;

} ;
