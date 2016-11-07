/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		String.h                   */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/30/2014                 */
/* UPDATE:      03/30/2014                 */
/*                                         */
/* Macro and functions to provide          */
/* additional string utilities, missing in */
/* the basic C/C++ standard libraries.     */
/*******************************************/

#ifndef __DOOM__STRING__
#define __DOOM__STRING__

#include <string>
#include <vector>
#include <stdint.h>

namespace Doom {

    namespace String {

        /**
         * @brief   Erase blank space before and after any printable character.
         * @param   stringToTrim    The string whose surrounding blank spaces
         *                          have to be removed.
         */
        void Trim(std::string& stringToTrim) ;


        /**
         * @brief   Set a cap at the given position.
         * @param   stringCap   The string to modify.
         * @param   position    Position in the string where the letter should
         *                      be an uppercase letter.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void UppercaseChar(std::string& stringCap, size_t position) ;

        /**
         * @brief   Set a cap at the first character of a given string.
         * @param   stringCap   The string to modify.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void UppercaseFirst(std::string& stringCap) ;

        /**
         * @brief   Set uppercase on the first letter of each word in the
         *          string.
         * @param   stringCap   The string to modify.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void UppercaseWords(std::string& stringCap) ;



        /**
         * @brief   Set the full string as uppercase string.
         * @param   stringCap   The string to modify.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void Uppercase(std::string& stringCap) ;


        /**
         * @brief   Set a lowercase letter at the given position.
         * @param   stringCap   The string to modify.
         * @param   position    Position in the string where the letter should
         *                      be an uppercase letter.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void LowercaseChar(std::string& stringCap, size_t position) ;

        /**
         * @brief   Set a lowercase letter at the first character of a given
         *          string.
         * @param   stringCap   The string to modify.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void LowercaseFirst(std::string& stringCap) ;

        /**
         * @brief   Set the full string as lowercase string.
         * @param   stringCap   The string to modify.
         * @warning The string is not changed if position is higher than the
         *          string length.
         */
        void Lowercase(std::string& stringCap) ;

        /**
         * @brief   Split a string at the given characters positions.
         * @param   toSplit     The string to te splitted.
         * @param   characters  Characters used to split the string.
         * @param   result      Output containing the resulting substrings.
         */
        void Split(
                   const std::string& toSplit,
                   const std::string& characters,
                   std::vector<std::string>& result
                  ) ;

        /**
         * @brief   Convert an integer value to its string representation.
         * @param   value       The value to convert.
         * @param   base        Base used to represent the value.
         * @return  The string containing the value representation.
         */
        std::string ToStringi(int32_t value, unsigned char base = 10) ;

        /**
         * @brief   Convert a floating value to its string representation.
         * @param   value       The value to convert.
         * @param   precision   Precision of the representation.
         * @return  The string containing the value representation.
         */
        std::string ToStringf(float value, unsigned char precision = 2) ;

        /**
         * @brief   Create a random string.
         * @param   length  Length of the random string.
         * @return  The random string.
         */
        std::string Random(const unsigned int& length) ;



        /**
         * @brief   Erase blank space before and after any printable character.
         * @param   StringToTrim    The string whose surrounding blank spaces have to be
         *                          removed. The string length is lower or equal to the
         *                          original one.
         * @warning The string length is not shrunk to the new real string length.
         *          If you want to make it have a smaller memory footprint, call
         *          strcpy() after using this function.
         */
        void Trim(char* StringToTrim) ;


        /**
         * @brief   Set a cap at the given Position.
         * @param   StringCap   The string to modify.
         * @param   Position    Position in the string where the letter should be an
         *                      uppercase letter.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void UppercaseChar(char* StringCap, size_t Position) ;

        /**
         * @brief   Set a cap at the first character of a given string.
         * @param   StringCap   The string to modify.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void UppercaseFirst(char* StringCap) ;

        /**
         * @brief   Set uppercase on the first letter of each word in the string.
         * @param   StringCap   The string to modify.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void UppercaseWords(char* StringCap) ;

        /**
         * @brief   Set the full string as uppercase string.
         * @param   StringCap   The string to modify.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void Uppercase(char* StringCap) ;


        /**
         * @brief   Set a lowercase letter at the given Position.
         * @param   StringCap   The string to modify.
         * @param   Position    Position in the string where the letter should be an
         *                      uppercase letter.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void LowercaseChar(char* StringCap, size_t Position) ;

        /**
         * @brief   Set a lowercase letter at the first character of a given string.
         * @param   StringCap   The string to modify.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void LowercaseFirst(char* StringCap) ;

        /**
         * @brief   Set the full string as lowercase string.
         * @param   StringCap   The string to modify.
         * @warning The string is not changed if Position is higher than the string
         *          length.
         */
        void Lowercase(char* StringCap) ;

    } ;

} ;


#endif
