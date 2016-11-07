/*******************************************/
/* DOOMful - Part of the hARMful Engine    */
/* All rights reserved (c) Denis CARLUS    */
/*                                         */
/* FILE : 		String.cpp                 */
/* AUTHOR : 	Denis CARLUS               */
/* VERSION: 	1.0                        */
/* CREATION:	03/30/2014                 */
/* UPDATE:      03/30/2014                 */
/*                                         */
/* Macro and functions to provide          */
/* additional string utilities, missing in */
/* the basic C++ standard libraries.       */
/*******************************************/

#ifdef __cplusplus

#include <utils/String.h>
#include <utils/Random.h>
#include <debug/Test.h>


// Quickly get the absolute value of a number
inline int32_t absolute(int32_t value) {
    return (value < 0) ? -value : value ;
}

namespace Doom {

    namespace String {

        /**
         * @brief   Position to begin the trimming algorithm.
         * @param   TrimFront   Trim from the beginning of the string.
         * @param   TrimBack    Trim from the end of the string.
         */
        enum TrimPosition {TrimFront, TrimBack} ;

        /**
         * @brief   Trim a string in only one direction.
         * @param   stringToTrim   The string to trim.
         * @param   motion      Motion of the trimming, from beginning or from ending.
         */
        static void Trim(std::string& stringToTrim, TrimPosition motion) {
            size_t length = stringToTrim.length() - 1 ;
            size_t index = (motion == TrimFront) ? 0 : length ;
            char step = (motion == TrimFront) ? 1 : -1 ;

            bool continueTrim = true ;
            while (continueTrim) {
                switch (stringToTrim[index]) {
                    case ' ' :
                    case '\a':
                    case '\b':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\v':
                        // Continue as it has to be removed
                        index = index + step ;
                        continueTrim = (index > 0) && (index < length) ;
                        break ;

                    default:
                        // Stop and cut from the current position
                        continueTrim = false ;

                        if (motion == TrimFront)
                            stringToTrim = stringToTrim.substr(index) ;
                        else
                            stringToTrim = stringToTrim.substr(0, index + 1) ;
                        break ;
                }
            }
        }


        void Trim(std::string& stringToTrim) {
            if (stringToTrim.empty()) return ;

            Trim(stringToTrim, TrimFront) ;
            Trim(stringToTrim, TrimBack) ;
        }


        void UppercaseChar(std::string& stringCap, size_t position) {
            if (position > stringCap.length())
                return ;

            char letter = stringCap[position] ;
            if (letter >= 'a' && letter <= 'z')
                // Difference between a lowercase letter and its uppercase version
                stringCap[position] -= 32 ;
        }


        void UppercaseFirst(std::string& stringCap) {
            UppercaseChar(stringCap, 0) ;
        }

        void UppercaseWords(std::string& stringCap) {
            bool insideWord = false ;
            for (size_t index = 0 ; index < stringCap.length() ; index++) {
                char letter = stringCap[index] ;
                if (not insideWord) {
                    if ((letter >= 'a') && (letter <= 'z')) {
                        // Difference between a lowercase letter and its uppercase version
                        stringCap[index] -= 32 ;
                        insideWord = true ;
                    }
                    else if (((letter >= 'A') && (letter <= 'Z'))
                                || ((letter >= '0') && (letter <= '9'))) {
                        insideWord = true ;
                    }
                }
                else if (not((letter >= 'A') && (letter <= 'Z'))
                            && not((letter >= 'a') && (letter <= 'z'))
                            && not((letter >= '0') && (letter <= '9'))) {
                    insideWord = false ;
                }
            }
        }

        void Uppercase(std::string& stringCap) {
            for (size_t index = 0 ; index < stringCap.length() ; index++)
                UppercaseChar(stringCap, index) ;
        }


        void LowercaseChar(std::string& stringCap, size_t position) {
            if (position > stringCap.length())
                return ;

            char letter = stringCap[position] ;
            if (letter >= 'A' && letter <= 'Z')
                // Difference between a lowercase letter and its uppercase version
                stringCap[position] += 32 ;
        }


        void LowercaseFirst(std::string& stringCap) {
            LowercaseChar(stringCap, 0) ;
        }

        void Lowercase(std::string& stringCap) {
            for (size_t index = 0 ; index < stringCap.length() ; index++)
                LowercaseChar(stringCap, index) ;
        }

        void Split(
                   const std::string& toSplit,
                   const std::string& characters,
                   std::vector<std::string>& result
                  ) {
            std::size_t previousPosition = 0 ;
            std::size_t foundPosition = toSplit.find_first_of(characters) ;
            while (foundPosition != std::string::npos) {
                std::size_t length = foundPosition - previousPosition ;
                std::string part = toSplit.substr(previousPosition, length) ;
                if (part.size() > 0) {
                    result.push_back(part) ;
                }

                previousPosition = foundPosition + 1 ;
                foundPosition = toSplit.find_first_of(
                                                      characters,
                                                      previousPosition + 1
                                                     ) ;
            }

            result.push_back(toSplit.substr(previousPosition)) ;
        }

        std::string ToStringi(int32_t value, unsigned char base) {
            static const unsigned short MAX_BUFFER = 127 ;
            static char Buffer[MAX_BUFFER + 2] ;

            unsigned short offset = MAX_BUFFER + 1 ;

            bool negative = (value < 0) ;
            while ((value != 0) && (offset > 0)) {
                int32_t tmp = value ;
                value = value / base ;
                Buffer[offset] = absolute(tmp - (value * base)) + '0' ;
                if (Buffer[offset] > '9')
                    Buffer[offset] += 8 ;
                offset-- ;
            }

            if (negative)
                Buffer[offset] = '-' ;

            return std::string(Buffer + offset + 1) ;
        }

        std::string ToStringf(float value, unsigned char precision) {
            int32_t integer = (int32_t) value ;
            float fractional = value - integer ;

            // Convert the integer part
            std::string representation(ToStringi(integer)) ;

            // Get the fractional part with the wanted precision
            if (precision > 0) {
                unsigned int power_fractional = 1 ;
                for (unsigned char power = 0 ; power < precision ; power++) {
                    power_fractional *= 10 ;
                }
                long fractional_integer = (fractional * (double) power_fractional) ;
                representation += "." ;
                representation += ToStringi(fractional_integer) ;
            }

            return representation ;
        }

        std::string Random(const unsigned int& length) {
            static const std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ;
            static const size_t alphanumLength = alphanum.size() ;

            Random::Initialize() ;

            std::string output ;
            output.resize(length) ;
            for (size_t index = 0 ; index < length ; ++index) {
                int characterPosition = Random::GetValue() % alphanumLength ;
                char characterAlphanum = alphanum[characterPosition] ;
                output[index] = characterAlphanum ;
            }
            return output ;
        }



        /**
         * @brief   Trim a string in only one direction.
         * @param   StringToTrim   The string to trim.
         * @param   Motion         Motion of the trimming, from beginning or from ending.
         */
        static size_t TrimOnSide(char* StringToTrim,
                                 enum TrimPosition Motion) {
            size_t length = strlen(StringToTrim) - 1 ;
            size_t index = (Motion == TrimFront) ? 0 : length ;
            char step = (Motion == TrimFront) ? 1 : -1 ;

            char continueTrim = 1 ;
            while (continueTrim) {
                switch (StringToTrim[index]) {
                    case ' ' :
                    case '\a':
                    case '\b':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\v':
                        // Continue as it has to be removed
                        index = index + step ;
                        continueTrim = (index > 0) && (index < length) ;
                        break ;

                    default:
                        // Stop and cut from the current Position
                        continueTrim = 0 ;

                        if (Motion == TrimFront)
                            return index ;
                        else
                            return index + 1 ;
                        break ;
                }
            }

            return 0 ;
        }


        void Trim(char* StringToTrim) {
            if ((StringToTrim == NULL)
                    || (strlen(StringToTrim) == 0))
                return ;

            size_t posFront = TrimOnSide(StringToTrim, TrimFront) ;
            size_t posBack  = TrimOnSide(StringToTrim, TrimBack) ;

            if (posBack > posFront) {
                size_t trimmedLength = posBack - posFront ;
                // Move the trimmed string to the first
                memmove(StringToTrim, StringToTrim + posFront, trimmedLength) ;
                // Correctly end the string
                StringToTrim[trimmedLength] = '\0' ;
            }
        }


        void UppercaseChar(char* StringCap,
                           size_t Position) {
            if (StringCap == NULL)
                return ;

            if (Position > strlen(StringCap))
                return ;

            char letter = StringCap[Position] ;
            if (letter >= 'a' && letter <= 'z')
                // Difference between a lowercase letter and its uppercase version
                StringCap[Position] -= 32 ;
        }


        void UppercaseFirst(char* StringCap) {
            UppercaseChar(StringCap, 0) ;
        }

        void UppercaseWords(char* StringCap) {
            if (StringCap == NULL)
                return ;

            size_t index ;
            size_t length = strlen(StringCap) ;
            char insideWord = 0 ;
            for (index = 0 ; index < length ; index++) {
                char letter = StringCap[index] ;

                if (!insideWord) {
                    if ((letter >= 'a') && (letter <= 'z')) {
                        // Difference between a lowercase letter and its uppercase version
                        StringCap[index] -= 32 ;
                        insideWord = 1 ;
                    }
                    else if (((letter >= 'A') && (letter <= 'Z'))
                                || ((letter >= '0') && (letter <= '9'))) {
                        insideWord = 1 ;
                    }
                }
                else if (!((letter >= 'A') && (letter <= 'Z'))
                            && !((letter >= 'a') && (letter <= 'z'))
                            && !((letter >= '0') && (letter <= '9'))) {
                    insideWord = 0 ;
                }
            }
        }

        void Uppercase(char* StringCap) {
            if (StringCap == NULL)
                return ;

            size_t index ;
            size_t length = strlen(StringCap) ;
            for (index = 0 ; index < length ; index++)
                UppercaseChar(StringCap, index) ;
        }


        void LowercaseChar(char* StringCap,
                           size_t Position) {
            if (StringCap == NULL)
                return ;

            if (Position > strlen(StringCap))
                return ;

            char letter = StringCap[Position] ;
            if (letter >= 'A' && letter <= 'Z')
                // Difference between a lowercase letter and its uppercase version
                StringCap[Position] += 32 ;
        }


        void LowercaseFirst(char* StringCap) {
            LowercaseChar(StringCap, 0) ;
        }

        void Lowercase(char* StringCap) {
            if (StringCap == NULL)
                return ;

            size_t index ;
            size_t length = strlen(StringCap) ;
            for (index = 0 ; index < length ; index++)
                LowercaseChar(StringCap, index) ;
        }

    } ;

} ;

#endif //__cplusplus
