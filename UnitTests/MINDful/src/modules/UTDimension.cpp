#include <modules/UTDimension.hpp>
#include <string>
#include <iostream>

namespace UTMind {
    UTDimension::UTDimension() {}

    UTDimension::~UTDimension() {}

    void UTDimension::runTests() {
        allocation() ;
        scalarOperations() ;
        dimensionsOperations() ;
        equality() ;
        inequality() ;
        setter() ;
        cast() ;
    }
}
