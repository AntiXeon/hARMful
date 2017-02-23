#include <modules/rectangles/UTRectangle.hpp>
#include <string>
#include <iostream>

namespace UTMind {
    UTRectangle::UTRectangle() {}

    UTRectangle::~UTRectangle() {}

    void UTRectangle::runTests() {
        allocation() ;
        translation() ;
        contain() ;
        intersect() ;
        position() ;
        operators() ;
    }
}
