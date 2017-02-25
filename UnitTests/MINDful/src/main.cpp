#include <MINDOptions.hpp>
#include <modules/dimensions/UTDimension2Df.hpp>
#include <modules/dimensions/UTDimension3Df.hpp>
#include <modules/lines/UTLine2Df.hpp>
#include <modules/points/UTPoint2Df.hpp>
#include <modules/points/UTPoint3Df.hpp>
#include <modules/rectangles/UTRectangle2Df.hpp>
#include <modules/matrices/UTMatrix2D.hpp>
#include <modules/matrices/UTMatrix3x3f.hpp>
#include <modules/matrices/UTMatrix4x4f.hpp>

static void testDimensions() {
    UTMind::UTDimension2Df().runTests() ;
    UTMind::UTDimension3Df().runTests() ;
}

static void testLines() {
    UTMind::UTLine2Df().runTests() ;
}

static void testPoints() {
    UTMind::UTPoint2Df().runTests() ;
    UTMind::UTPoint3Df().runTests() ;
}

static void testRectangles() {
    UTMind::UTRectangle2Df().runTests() ;
}

static void testMatrices() {
    UTMind::UTMatrix2D().runTests() ;
    UTMind::UTMatrix3x3f().runTests() ;
    UTMind::UTMatrix4x4f().runTests() ;
}

int main(int, char**) {
    #ifdef FORCE_EMULATED_SIMD
        std::cout << "Emulated SIMD" << std::endl ;
    #else
        std::cout << "CPU SIMD" << std::endl ;
    #endif

    testDimensions() ;
    testLines() ;
    testPoints() ;
    testRectangles() ;
    testMatrices() ;
    return UnitTest::Success() ;
}
