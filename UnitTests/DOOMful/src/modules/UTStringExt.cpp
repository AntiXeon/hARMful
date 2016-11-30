#include <modules/UTStringExt.hpp>
#include <utils/StringExt.hpp>

namespace UTDoom {
    UTStringExt::UTStringExt() {}

    UTStringExt::~UTStringExt() {}

    void UTStringExt::runTests() {
        changeCase() ;
        split() ;
        numberToString() ;
        random() ;
    }

    void UTStringExt::changeCase() {
        // This is a test to check if the continuous integration can succeed on
        // a good result.
        check(true) ;
    }

    void UTStringExt::split() {

    }

    void UTStringExt::numberToString() {

    }

    void UTStringExt::random() {

    }
}
