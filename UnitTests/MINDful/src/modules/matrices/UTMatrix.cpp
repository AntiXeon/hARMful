#include <modules/matrices/UTMatrix.hpp>
#include <string>
#include <iostream>

namespace UTMind {
    UTMatrix::UTMatrix() {}

    UTMatrix::~UTMatrix() {}

    void UTMatrix::runTests() {
        allocation() ;
        utilities() ;
        operators() ;
    }
}
