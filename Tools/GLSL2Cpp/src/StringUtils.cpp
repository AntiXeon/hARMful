#include <StringUtils.hpp>

std::string StringUtils::FirstUpLetter(const std::string& input) {
    std::string output = input ;
    output[0] = toupper(output[0]) ;

    size_t length = input.size() ;
    for (size_t index = 1 ; index < length ; index++) {
        output[index] = tolower(output[index]) ;
    }

    return output ;
}

std::string StringUtils::UpperCase(const std::string& input) {
    std::string output = input ;

    size_t length = input.size() ;
    for (size_t index = 0 ; index < length ; index++) {
        output[index] = toupper(output[index]) ;
    }

    return output ;
}

std::string StringUtils::RemoveUnderscoreChars(
    const std::string& input,
    const bool upFirstChar
) {
    std::string output ;
    size_t length = input.size() ;
    bool upperChar = false ;

    output.reserve(length) ;

    size_t index = 0 ;
    if (upFirstChar) {
        output += toupper(input[0]) ;
        index = 1 ;
    }

    for (; index < length ; ++index) {
        if (input[index] != '_') {
            if (upperChar) {
                output += toupper(input[index]) ;
                upperChar = false ;
            }
            else {
                output += input[index] ;
            }
        }
        else {
            upperChar = true ;
        }
    }

    return output ;
}
