/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE :       Console.cpp                */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    01/05/2015                 */
/* UPDATE:      01/05/2015                 */
/*                                         */
/* A Console to write and get information  */
/* in a thread-safe way.                   */
/*******************************************/

#ifdef __cplusplus

#include <utils/Console.h>
#include <iostream>
#include <limits>
#include <stdarg.h>
#include <stdio.h>

namespace Doom {

    namespace Console {

        /**
         * @brief   Mutex to protect console writing and reading.
         */
        static Mutex ConsoleMutex ;

        /**
         * @brief   State of the Console.
         */
        static State ConsoleState = ConsoleOK ;


        static void ClearInputStream() {
            std::cin.clear() ;
            std::cin.seekg(0, std::ios::end) ;

            if (!std::cin.fail()) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max()) ;
            }
            else {
                std::cin.clear() ;
            }
        }

        static void CheckInputStream() {
            if (std::cin.eof()) {
                ConsoleState = ConsoleError ;
                ClearInputStream() ;
            }
            else if (std::cin.bad()) {
                ConsoleState = ConsoleBad ;
                ClearInputStream() ;
            }
            else if (std::cin.fail()) {
                ConsoleState = ConsoleFail ;
                ClearInputStream() ;
            }
            else {
                ConsoleState = ConsoleOK ;
            }
        }



        void Write(const char* format, ...) {
            va_list arguments ;
            va_start(arguments, format) ;
            va_end(arguments) ;

            size_t formatLength = strlen(format) ;
            bool printNewLine = (format[formatLength - 2] != '\n') ;

            ConsoleMutex.lock() ;
                vprintf(format, arguments) ;
                if (printNewLine) {
                    printf("\n") ;
                }
            ConsoleMutex.unlock() ;
        }


        State ReadString(std::string& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadInt8(int8_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadUInt8(uint8_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadInt16(int16_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadUInt16(uint16_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadInt32(int32_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadUInt32(uint32_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadInt64(int64_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadUInt64(uint64_t& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadFloat(float& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

        State ReadDouble(double& output) {
            ConsoleMutex.lock() ;
                std::cin >> output ;
                CheckInputStream() ;
                State currentState = ConsoleState ;
            ConsoleMutex.unlock() ;

            return currentState ;
        }

    } ;

} ;

#endif
