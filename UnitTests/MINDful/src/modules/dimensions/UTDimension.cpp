#include <modules/dimensions/UTDimension.hpp>
#include <string>
#include <iostream>

namespace UTMind {
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
