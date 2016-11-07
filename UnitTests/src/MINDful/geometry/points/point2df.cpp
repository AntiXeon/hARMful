#include <math.h>
#include <mock_assert.h>
#include <test_float.h>
#include <geometry/points/Point2Df.h>

using namespace std ;
using namespace Mind ;

/** @brief  Test allocation of Point2D objects. */
static void ftest_allocation() {
    Point2Df p1 ;
    assert(fclose_to(p1.getX(), 0.f)) ;
    assert(fclose_to(p1.getY(), 0.f)) ;

    Scalar p2X = 9.48f ;
    Scalar p2Y = -56.474f ;
    Point2Df p2(p2X, p2Y) ;
    assert(fclose_to(p2.getX(), p2X)) ;
    assert(fclose_to(p2.getY(), p2Y)) ;

    Point2Df p3(p2) ;
    assert(fclose_to(p3.getX(), p2X)) ;
    assert(fclose_to(p3.getY(), p2Y)) ;
    assert(fclose_to(p3.getX(), p2.getX())) ;
    assert(fclose_to(p3.getY(), p2.getY())) ;

    p1.setX(p2Y) ;
    p1.setY(p2X) ;
    assert(fclose_to(p1.getX(), p2Y)) ;
    assert(fclose_to(p1.getY(), p2X)) ;
    assert(fclose_to(p1.getX(), p2.getY())) ;
    assert(fclose_to(p1.getY(), p2.getX())) ;

    Scalar p4X = -2241.4f ;
    Scalar p4Y = 0.04854f ;
    Point2Df p4(p4X, p4Y) ;
    p1.set(p4) ;
    assert(fclose_to(p1.getX(), p4X)) ;
    assert(fclose_to(p1.getY(), p4Y)) ;
    assert(fclose_to(p1.getX(), p4.getX())) ;
    assert(fclose_to(p1.getY(), p4.getY())) ;

    p4.set(p2X, p2Y) ;
    assert(fclose_to(p4.getX(), p2X)) ;
    assert(fclose_to(p4.getY(), p2Y)) ;
    assert(fclose_to(p4.getX(), p2.getX())) ;
    assert(fclose_to(p4.getY(), p2.getY())) ;
}

/** @brief  Test utilities on Point2D objects. */
static void ftest_utilities() {
    Scalar p1X = 94.415f ;
    Scalar p1Y = -56.44f ;
    Point2Df p1(p1X, p1Y) ;

    Scalar p2X = -54.45f ;
    Scalar p2Y = 418.88781f ;
    Point2Df p2(p2X, p2Y) ;

    // Translation
    p1.translate(p2) ;
    assert(fclose_to(p1.getX(), p1X + p2X)) ;
    assert(fclose_to(p1.getY(), p1Y + p2Y)) ;

    p2.translate(p1X, p1Y) ;
    assert(fclose_to(p2.getX(), p1X + p2X)) ;
    assert(fclose_to(p2.getY(), p1Y + p2Y)) ;

    p2.translate(p2Y, p2X) ;
    assert(fclose_to(p2.getX(), p1X + p2X + p2Y)) ;
    assert(fclose_to(p2.getY(), p1Y + p2Y + p2X)) ;

    // Dot product
    Scalar expectedP1DotP2 = (p1.getX() * p2.getX()) + (p1.getY() * p2.getY()) ;
    Scalar computedP1DotP2 = p1.dot(p2) ;
    assert(fclose_to(computedP1DotP2, expectedP1DotP2)) ;
}

int main() {
    ftest_allocation() ;
    ftest_utilities() ;

    return TestResult ; // Defined in <mock_assert.h>
}
