#ifndef __GLSL2CPP__STRING_UTILS__
#define __GLSL2CPP__STRING_UTILS__

#include <string>

namespace StringUtils {
    /**
     * Set the first letter of a string upper case, the other characters are
     * lower case.
     */
    std::string FirstUpLetter(const std::string& input) ;

    /**
     * Set all the letters of a  std::string upper case.
     */
    std::string UpperCase(const std::string& input) ;

    /**
     * Remove underscore (_) and uppercase the following character.
     * @param   upFirstChar Up case the first character as well if true.
     */
    std::string RemoveUnderscoreChars(
        const std::string& input,
        const bool upFirstChar = true
    ) ;
}

#endif
