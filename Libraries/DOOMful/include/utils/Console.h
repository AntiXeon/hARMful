/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* GNU GENERAL PUBLIC LICENSE version 3    */
/*                                         */
/* FILE :       Console.h                  */
/* AUTHOR :     Denis CARLUS               */
/* VERSION:     1.0                        */
/* CREATION:    01/05/2015                 */
/* UPDATE:      01/05/2015                 */
/*                                         */
/* A Console to write and get information  */
/* in a thread-safe way.                   */
/*******************************************/

#ifndef __DOOM__CONSOLE__
#define __DOOM__CONSOLE__


#include <utils/Mutex.h>
#include <debug/Test.h>
#include <string>
#include <stdint.h>


namespace Doom {

   /**
    * @brief   A Console to write and get information in a thread-safe way.
    * @author  CB (c) 2015
    * @version 0.1     2015/02/17
    */
    namespace Console {

        /**
         * @brief   State of the Console.
         */
        enum State {
                    ConsoleError,
                    ConsoleBad,
                    ConsoleFail,
                    ConsoleOK
                   } ;

        /**
         * @brief   Write messages on the Console.
         * @param   format  Format of the text to display and the list of
         *                  the parameters to display.
         */
        void Write(const char* format, ...) ;



        /**
         * @brief   Read a string from the Console.
         * @param   output  The read string.
         * @return  State of the Console once data are read.
         */
        State ReadString(std::string& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadInt8(int8_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadUInt8(uint8_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadInt16(int16_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadUInt16(uint16_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadInt32(int32_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadUInt32(uint32_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadInt64(int64_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadUInt64(uint64_t& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadFloat(float& output) ;

        /**
         * @brief   Read an integer value from the Console.
         * @param   output  The read value.
         * @return  State of the Console once data are read.
         */
        State ReadDouble(double& output) ;

    } ;

} ;

#endif
