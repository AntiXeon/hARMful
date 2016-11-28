#include <utils/StringExt.hpp>
#include <utils/Random.hpp>
#include <cmath>

namespace Doom {
    namespace StringExt {
        void CaseChar(std::string& stringCap, size_t position, CharacterCase charCase) {
            if (position > stringCap.length()) {
                return ;
            }

            char character = stringCap[position] ;
            switch(charCase) {
                case CharacterCase::Upper:
                    if (character >= 'a' && character <= 'z') {
                        stringCap[position] += (int8_t)(CharacterCase::Upper) ;
                    }
                    break ;

                case CharacterCase::Lower:
                    if (character >= 'A' && character <= 'Z') {
                        stringCap[position] += (int8_t)(CharacterCase::Lower) ;
                    }
                    break ;
            }
        }

        void CaseFirst(std::string& stringCap, CharacterCase charCase) {
            CaseChar(stringCap, 0, charCase) ;
        }

        void CaseWords(std::string& stringCap, CharacterCase charCase) {
            size_t characterPosition = 0 ;
            bool insideWord = false ;
            for (char& character : stringCap) {
                if (!insideWord) {
                    insideWord = true ;
                    CaseChar(stringCap, characterPosition, charCase) ;
                }
                else {
                    bool isLowerLetter = (character >= 'a') && (character <= 'z') ;
                    bool isUpperLetter = (character >= 'A') && (character <= 'Z') ;
                    bool isLetter = isLowerLetter || isUpperLetter ;
                    bool isNumber = (character >= '0') && (character <= '9') ;

                    if (!isLetter && !isNumber) {
                        insideWord = false ;
                    }
                }
                characterPosition++ ;
            }
        }

        void TextCase(std::string& stringCap, CharacterCase charCase) {
            size_t characterPosition = 0 ;
            for (char& character : stringCap) {
                CaseChar(stringCap, characterPosition, charCase) ;
                characterPosition++ ;
            }
        }

        /**
         * Trim the beginning of a string.
         * @param   stringToTrim The string to trim.
         */
        static void TrimFront(std::string& stringToTrim) {
            size_t strLength = stringToTrim.length() - 1 ;
            size_t index = 0 ;

            bool continueToTrim = true ;
            while(continueToTrim) {
                switch(stringToTrim[index]) {
                    case ' ':
                    case '\a':
                    case '\b':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\v':
                        // Move the index to remove the character to delete.
                        index = index + 1 ;
                        continueToTrim = (index < strLength) ;
                        break ;

                    default:
                        // Stop trimming and substring with the index.
                        continueToTrim = false ;
                        stringToTrim = stringToTrim.substr(index) ;
                        break ;
                }
            }
        }

        /**
         * Trim the ending of a string.
         * @param   stringToTrim The string to trim.
         */
        static void TrimBack(std::string& stringToTrim) {
            size_t strLength = stringToTrim.length() - 1 ;
            size_t index = strLength ;

            bool continueToTrim = true ;
            while(continueToTrim) {
                switch(stringToTrim[index]) {
                    case ' ':
                    case '\a':
                    case '\b':
                    case '\n':
                    case '\r':
                    case '\t':
                    case '\v':
                        // Move the index to remove the character to delete.
                        index = index - 1 ;
                        continueToTrim = (index > 0) ;
                        break ;

                    default:
                        // Stop trimming and substring with the index.
                        continueToTrim = false ;
                        stringToTrim = stringToTrim.substr(0, index + 1) ;
                        break ;
                }
            }
        }

        void Trim(std::string& stringToTrim) {
            if (stringToTrim.empty()) {
                return ;
            }

            TrimFront(stringToTrim) ;
            TrimBack(stringToTrim) ;
        }

        std::vector<std::string> Split(const std::string& toSplit, const std::string& characters) {
            std::vector<std::string> result ;

            std::size_t previousPosition = 0 ;
            std::size_t foundPosition = toSplit.find_first_of(characters) ;
            while (foundPosition != std::string::npos) {
                std::size_t length = foundPosition - previousPosition ;
                std::string part = toSplit.substr(previousPosition, length) ;
                if (part.size() > 0) {
                    result.push_back(part) ;
                }

                previousPosition = foundPosition + 1 ;
                foundPosition = toSplit.find_first_of(characters, previousPosition + 1) ;
            }
            result.push_back(toSplit.substr(previousPosition)) ;

            return result ;
        }

        std::string ToStringi(int32_t value, unsigned char base) {
            const char ASCIINumberStart = '0' ;
            const unsigned short MAX_BUFFER = 127 ;
            char buffer[MAX_BUFFER + 2] ;

            unsigned short offset = MAX_BUFFER + 1 ;
            bool isNegative = (value < 0) ;
            while ((value != 0) && (offset > 0)) {
                int32_t tmp = value ;
                value = value / base ;
                buffer[offset] = std::abs(tmp - (value * base)) + ASCIINumberStart ;
                if (buffer[offset] > '9') {
                    // Add difference between 9 and A in the ASCII table.
                    buffer[offset] += 8 ;
                }
                offset-- ;
            }

            if (isNegative) {
                buffer[offset] = '-' ;
            }

            return std::string(buffer + offset + 1) ;
        }

        std::string ToStringf(float value, unsigned char precision) {
            int32_t integer = (int32_t) value ;
            float fractional = value - integer ;

            // Convert the integer part.
            std::string representation(ToStringi(integer)) ;

            // Get the fractional part with the wanted precision.
            if (precision == 0) {
                return representation ;
            }

            unsigned int power_fractional = 1 ;
            for (unsigned char power = 0 ; power < precision ; power++) {
                power_fractional *= 10 ;
            }
            long fractional_integer = (fractional * (double) power_fractional) ;
            representation += "." ;
            representation += ToStringi(fractional_integer) ;

            return representation ;
        }

        std::string Random(unsigned int length) {
            const std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" ;
            return Random(length, alphanum) ;
        }

        std::string Random(unsigned int length, const std::string& characters) {
            Random::Initialize() ;

            std::string output(length, '\0') ;
            size_t charactersListLength = characters.length() ;
            for (size_t index = 0 ; index < length ; ++index) {
                int characterPosition = Random::GetInteger(0, charactersListLength) ;
                char pickedCharacter = characters[characterPosition] ;
                output[index] = pickedCharacter ;
            }
            return output ;
        }
    }
}
