#include <modules/dimensions/UTDimension2Df.hpp>
#include <modules/dimensions/UTDimension2Di.hpp>
#include <modules/dimensions/UTDimension3Df.hpp>
#include <modules/dimensions/UTDimension3Di.hpp>

#include <modules/lines/UTLine2Df.hpp>
#include <modules/lines/UTLine2Di.hpp>

static void testDimensions() {
    UTMind::UTDimension2Df().runTests() ;
    UTMind::UTDimension2Di().runTests() ;
    UTMind::UTDimension3Df().runTests() ;
    UTMind::UTDimension3Di().runTests() ;
}

static void testLines() {
    UTMind::UTLine2Df().runTests() ;
    UTMind::UTLine2Di().runTests() ;
}

int main(int, char**) {
    testDimensions() ;
    testLines() ;
    return UnitTest::Success() ;
}
