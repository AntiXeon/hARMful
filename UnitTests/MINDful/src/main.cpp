#include <modules/UTDimension2Df.hpp>
#include <modules/UTDimension2Di.hpp>
#include <modules/UTDimension3Df.hpp>
#include <modules/UTDimension3Di.hpp>

static void testDimensions() {
    UTMind::UTDimension2Df().runTests() ;
    UTMind::UTDimension2Di().runTests() ;
    UTMind::UTDimension3Df().runTests() ;
    UTMind::UTDimension3Di().runTests() ;
}

int main(int, char**) {
    testDimensions() ;
    return UnitTest::Success() ;
}
