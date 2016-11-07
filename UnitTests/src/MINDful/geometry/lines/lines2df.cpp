#include <math.h>
#include <mock_assert.h>
#include <test_float.h>
#include <geometry/lines/Line2Df.h>

using namespace std ;
using namespace Mind ;

/** @brief  Test allocation of Line2D objects. */
static void ftest_allocation() {
    Line2Df l1 ;
    assert(l1.getStartX() == 0.f) ;
    assert(l1.getStartY() == 0.f) ;
    assert(l1.getEndX() == 0.f) ;
    assert(l1.getEndY() == 0.f) ;

    Scalar pStartX = 5.75f ;
    Scalar pStartY = 0.574f ;
    Point2Df pStart(pStartX, pStartY) ;

    Scalar pEndX = 54.12f ;
    Scalar pEndY = -452.4f ;
    Point2Df pEnd(pEndX, pEndY) ;

    Line2Df l2(pStart, pEnd) ;
    assert(l2.getStartX() == pStartX) ;
    assert(l2.getStartY() == pStartY) ;
    assert(l2.getEndX() == pEndX) ;
    assert(l2.getEndY() == pEndY) ;
    assert(l2 != l1) ;

    Line2Df l3(l2) ;
    assert(l3.getStartX() == l2.getStartX()) ;
    assert(l3.getStartY() == l2.getStartY()) ;
    assert(l3.getEndX() == l2.getEndX()) ;
    assert(l3.getEndY() == l2.getEndY()) ;
    assert(l3 == l2) ;
}

/** @brief  Test utilities on Line2D objects. */
static void ftest_utilities() {
    // Line 1
    Scalar p1StartX = 9.785f ;
    Scalar p1StartY = 15.41f ;
    Point2Df p1Start(p1StartX, p1StartY) ;

    Scalar p1EndX = -458.04f ;
    Scalar p1EndY = 15.112f ;
    Point2Df p1End(p1EndX, p1EndY) ;

    Line2Df l1(p1Start, p1End) ;

    // Line 2
    Scalar p2StartX = -0.024f ;
    Scalar p2StartY = -87.254f ;
    Point2Df p2Start(p2StartX, p2StartY) ;

    Scalar p2EndX = 78.1f ;
    Scalar p2EndY = -0.145f ;
    Point2Df p2End(p2EndX, p2EndY) ;

    Line2Df l2(p2Start, p2End) ;

    // Line 3
    Scalar p3EndX = -97.1f ;
    Scalar p3EndY = 80.f ;
    Point2Df p3End(p3EndX, p3EndY) ;

    Line2Df l3(p3End, p1Start) ;

    // Line 4
    Line2Df l4(p1End, p1Start) ;

    // Line 5
    Line2Df l5(l1) ;


    // Lengths
    double expectedL1SquaredLength = 218860.319429 ;
    double computedL1SquaredLength = pow(p1EndX - p1StartX, 2) + pow(p1EndY - p1StartY, 2) ;
    assert(fclose_to(expectedL1SquaredLength, expectedL1SquaredLength)) ;
    double expectedL1Length = 467.82509491154918163612 ;
    double computedL1Length = sqrt(computedL1SquaredLength) ;
    assert(fclose_to(expectedL1Length, computedL1Length)) ;

    assert(fclose_to(l1.length(), computedL1Length)) ;
    assert(fclose_to(l1.lengthSquared(), computedL1SquaredLength)) ;

    // Contiguous lines
    assert(!l1.isContiguousTo(l2)) ;
    assert(l1.isContiguousTo(l3)) ;
    assert(l1.isContiguousTo(l4)) ;
    assert(!l1.isContiguousTo(l5)) ;

    // Relative CCW
    assert(Line2Df::CCW(l1, Point2Df(0.f, 500.f)) == 1) ;
    assert(Line2Df::CCW(l1, Point2Df(0.f, 0.f)) == -1) ;

    // Relative line to plan origin
    Line2Df relativeL1 = Line2Df::relative(l1) ;
    assert(relativeL1.getStartX() == 0.f) ;
    assert(relativeL1.getStartY() == 0.f) ;
    assert(relativeL1.getEndX() == (p1EndX - p1StartX)) ;
    assert(relativeL1.getEndY() == (p1EndY - p1StartY)) ;
}

/** @brief  Test intersections on Line2D objects. */
static void ftest_intersection() {
    // Line 1 (horizontal)
    Scalar p1StartX = -50.105f ;
    Scalar p1StartY = 10.f ;
    Point2Df p1Start(p1StartX, p1StartY) ;

    Scalar p1EndX = 480.12f ;
    Scalar p1EndY = 10.f ;
    Point2Df p1End(p1EndX, p1EndY) ;

    Line2Df l1(p1Start, p1End) ;

    // Line 2 (vertical)
    Scalar p2StartX = 2.3f ;
    Scalar p2StartY = -945.154f ;
    Point2Df p2Start(p2StartX, p2StartY) ;

    Scalar p2EndX = 2.3f ;
    Scalar p2EndY = 210.98785f ;
    Point2Df p2End(p2EndX, p2EndY) ;

    Line2Df l2(p2Start, p2End) ;

    // Line 3 (to up right)
    Scalar p3StartX = -32.321f ;
    Scalar p3StartY = -5.154f ;
    Point2Df p3Start(p3StartX, p3StartY) ;

    Scalar p3EndX = 95.21f ;
    Scalar p3EndY = 15.35f ;
    Point2Df p3End(p3EndX, p3EndY) ;

    Line2Df l3(p3Start, p3End) ;

    // Line 4 (to down right)
    Scalar p4StartX = -164.105f ;
    Scalar p4StartY = 485.152f ;
    Point2Df p4Start(p4StartX, p4StartY) ;

    Scalar p4EndX = 158.458f ;
    Scalar p4EndY = -156.11f ;
    Point2Df p4End(p4EndX, p4EndY) ;

    Line2Df l4(p4Start, p4End) ;

    // Line 5 (little)
    Scalar p5StartX = 65.45f ;
    Scalar p5StartY = 23.458f ;
    Point2Df p5Start(p5StartX, p5StartY) ;

    Scalar p5EndX = 66.12f ;
    Scalar p5EndY = 22.3451f ;
    Point2Df p5End(p5EndX, p5EndY) ;

    Line2Df l5(p5Start, p5End) ;

    // Line 6 (as Line 1)
    Line2Df l6(l1) ;


    assert(l1.intersects(l2)) ;
    assert(l1.intersects(l3)) ;
    assert(l1.intersects(l4)) ;
    assert(not l1.intersects(l5)) ;
    assert(l1.intersects(l6)) ;

    assert(l2.intersects(l1)) ;
    assert(l2.intersects(l2)) ;
    assert(l2.intersects(l3)) ;
    assert(l2.intersects(l4)) ;
    assert(not l2.intersects(l5)) ;
    assert(l2.intersects(l6)) ;

    assert(l3.intersects(l4)) ;
    assert(not l3.intersects(l5)) ;
    assert(l3.intersects(l6)) ;
}

/** @brief  Test distances on Line2D objects. */
static void ftest_distance() {
    // Line 1
    Scalar p1StartX = 0.f ;
    Scalar p1StartY = -10.f ;
    Point2Df p1Start(p1StartX, p1StartY) ;

    Scalar p1EndX = 0.f ;
    Scalar p1EndY = 10.f ;
    Point2Df p1End(p1EndX, p1EndY) ;

    Line2Df l1(p1Start, p1End) ;


    // Distance to Point A (at 5 units on right of L1)
    Point2Df pointA(5.f, 0.f) ;
    assert(fclose_to(l1.distanceTo(pointA), 5.f)) ;

    // Seem difficult to evaluate, formula not well understood...
    Point2Df pointB(10.f, 5.f) ;
    //assert(fclose_to(l1.distanceTo(pointB), ????.f)) ;
}

int main() {
    ftest_allocation() ;
    ftest_utilities() ;
    ftest_intersection() ;
    ftest_distance() ;

    return TestResult ; // Defined in <mock_assert.h>
}
