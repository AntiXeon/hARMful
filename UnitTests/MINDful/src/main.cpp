#include <modules/dimensions/UTDimension2Df.hpp>
#include <modules/dimensions/UTDimension2Di.hpp>
#include <modules/dimensions/UTDimension3Df.hpp>
#include <modules/dimensions/UTDimension3Di.hpp>

#include <modules/lines/UTLine2Df.hpp>
#include <modules/lines/UTLine2Di.hpp>

#include <modules/points/UTPoint2Df.hpp>
#include <modules/points/UTPoint2Di.hpp>
#include <modules/points/UTPoint3Df.hpp>
#include <modules/points/UTPoint3Di.hpp>

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

static void testPoints() {
    UTMind::UTPoint2Df().runTests() ;
    UTMind::UTPoint2Di().runTests() ;
    UTMind::UTPoint3Df().runTests() ;
    UTMind::UTPoint3Di().runTests() ;
}

int main(int, char**) {
    testDimensions() ;
    testLines() ;
    testPoints() ;
    return UnitTest::Success() ;
}
