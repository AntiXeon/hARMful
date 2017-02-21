#include <modules/lines/UTLine.hpp>
#include <string>
#include <iostream>

namespace UTMind {
    UTLine::UTLine() {}

    UTLine::~UTLine() {}

    void UTLine::runTests() {
        allocation() ;
        utilities() ;
        intersections() ;
        distance() ;
    }
}
