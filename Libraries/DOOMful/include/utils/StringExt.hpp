#ifndef __DOOM__STRING_EXTENSION__
#define __DOOM__STRING_EXTENSION__

#include <string>
#include <vector>

namespace Doom {
    namespace StringExt {
        /**
         * Offset between the upper and lower case alphabetic characters in the
         * ASCII table.
         */
        enum class CharacterCase : int8_t {
            Upper = 'A' - 'a',  // from lower to upper case in the ASCII table
            Lower = 'a' - 'A'   // from upper to lower case in the ASCII table
        } ;

        /**
         * Convert a letter in the stringto the wanted case.
         * @param stringCap The string to modify.
         * @param position  Position of the character in the string to
         *                  uppercase.
         * @param charCase  Resulting case of the letter.
         */
        void CaseChar(std::string& stringCap, size_t position, CharacterCase charCase) ;

        /**
         * Convert the first character in the string to the wanted case.
         * @param stringCap The string to modify.
         * @param charCase  Resulting case of the letters.
         */
        void CaseFirst(std::string& stringCap, CharacterCase charCase) ;

        /**
         * Convert the first character of each word in the string to the wanted
         * case.
         * @param stringCap The string to modify.
         * @param charCase  Resulting case of the letters.
         */
        void CaseWords(std::string& stringCap, CharacterCase charCase) ;

        /**
         * Change each letter in the string to the wanted case.
         * @param stringCap The string to modify.
         * @param charCase  Resulting case of the letters.
         */
        void TextCase(std::string& stringCap, CharacterCase charCase) ;


        /**
         * Remove white spaces (spaces, tabulations, new lines...) from the left
         * and the right of a string.
         * @param stringToTrim The string to trim.
         */
        void Trim(std::string& stringToTrim) ;

        /**
         * Split a string at the given characters positions.
         * @param toSplit    The string to split.
         * @param characters List of the characters to split the string at their
         *                   position.
         * @return           List of the resulting substrings.
         */
        std::vector<std::string> Split(const std::string& toSplit, const std::string& characters) ;

        /**
         * Convert an integer value to its string representation.
         * @param  value The value to convert.
         * @param  base  Base used to represent the value.
         * @return       The string containing the value representation.
         */
        std::string ToStringi(int32_t value, unsigned char base = 10) ;

        /**
         * Convert a floating value to its string representation.
         * @param  value     The value to convert.
         * @param  precision Precision of the representation.
         * @return           The string containing the value representation.
         */
        std::string ToStringf(float value, unsigned char precision = 2) ;

        /**
         * Create a random string with numbers, uppercase and lowercase letters.
         * @param  length Length of the random string.
         * @return        The generated string.
         */
        std::string Random(unsigned int length) ;

        /**
         * Create a random string with the provided characters.
         * @param  length     Length of the random string.
         * @param  characters Characters that can be used in the string
         *                    generation.
         * @return            The generated string.
         */
        std::string Random(unsigned int length, const std::string& characters) ;
    }
}


#endif
