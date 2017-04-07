#include <modules/rectangles/UTRectangle.hpp>
#include <string>
#include <iostream>

namespace UTMind {
    void UTRectangle::runTests() {
        allocation() ;
        translation() ;
        contain() ;
        intersect() ;
        position() ;
        operators() ;
    }
}
