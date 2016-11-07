#include <math.h>
#include <test_float.h>
#include <geometry/rectangles/Rectangle2Df.h>
#include <mock_assert.h>

using namespace std ;
using namespace Mind ;

/** @brief  Test allocation of Rectangle2D objects. */
static void ftest_allocation() {
    // Default constructor
    {
        Rectangle2Df r ;
        assert(r.getBottomLeftCornerX() == 0.f) ;
        assert(r.getBottomLeftCornerY() == 0.f) ;
        assert(r.getUpRightCornerX() == 0.f) ;
        assert(r.getUpRightCornerY() == 0.f) ;
        assert(r.getWidth() == 0.f) ;
        assert(r.getHeight() == 0.f) ;
    }

    // Rectangle from Point and Dimension
    {
        Scalar pCoordX = 48.85f ;
        Scalar pCoordY = -56.485f ;
        Point2Df pBottomLeft(pCoordX, pCoordY) ;
        Scalar width = 125.f ;
        Scalar height = 418.48f ;
        Dimension2Df dim(width, height) ;
        bool isCentered = true ;
        Rectangle2Df r(pBottomLeft, dim, !isCentered) ;

        assert(fclose_to(r.getBottomLeftCornerX(), pCoordX)) ;
        assert(fclose_to(r.getBottomLeftCornerY(), pCoordY)) ;
        assert(fclose_to(r.getUpRightCornerX(), pCoordX + width)) ;
        assert(fclose_to(r.getUpRightCornerY(), pCoordY + height)) ;
        assert(fclose_to(r.getWidth(), width)) ;
        assert(fclose_to(r.getHeight(), height)) ;
    }

    // Rectangle from Point and Dimension (centered)
    {
        Scalar pCoordX = 48.85f ;
        Scalar pCoordY = -56.485f ;
        Point2Df pBottomLeft(pCoordX, pCoordY) ;
        Scalar width = 125.f ;
        Scalar height = 418.48f ;
        Dimension2Df dim(width, height) ;
        bool isCentered = true ;
        Rectangle2Df r(pBottomLeft, dim, isCentered) ;

        assert(fclose_to(r.getBottomLeftCornerX(), pCoordX - (width / 2.f))) ;
        assert(fclose_to(r.getBottomLeftCornerY(), pCoordY - (height / 2.f))) ;
        assert(fclose_to(r.getUpRightCornerX(), pCoordX + (width / 2.f))) ;
        assert(fclose_to(r.getUpRightCornerY(), pCoordY + (height / 2.f))) ;
        assert(fclose_to(r.getWidth(), width)) ;
        assert(fclose_to(r.getHeight(), height)) ;
    }

    // Copy constructor
    {
        Scalar pCoordX = -964.498f ;
        Scalar pCoordY = 4185.148574f ;
        Point2Df pBottomLeft(pCoordX, pCoordY) ;
        Scalar width = 158.0418f ;
        Scalar height = 154.25748f ;
        Dimension2Df dim(width, height) ;
        bool isCentered = true ;
        Rectangle2Df rOriginal(pBottomLeft, dim, !isCentered) ;
        Rectangle2Df rCopy(rOriginal) ;

        assert(fclose_to(rCopy.getBottomLeftCornerX(),  rOriginal.getBottomLeftCornerX())) ;
        assert(fclose_to(rCopy.getBottomLeftCornerY(),  rOriginal.getBottomLeftCornerY())) ;
        assert(fclose_to(rCopy.getUpRightCornerX(),     rOriginal.getUpRightCornerX())) ;
        assert(fclose_to(rCopy.getUpRightCornerY(),     rOriginal.getUpRightCornerY())) ;
        assert(fclose_to(rCopy.getWidth(),              rOriginal.getWidth())) ;
        assert(fclose_to(rCopy.getHeight(),             rOriginal.getHeight())) ;
    }

    // Rectangle from Point and Dimension (as individual values)
    {
        Scalar pCoordX = 48.85f ;
        Scalar pCoordY = -56.485f ;
        Scalar width = 125.f ;
        Scalar height = 418.48f ;
        bool isCentered = true ;
        Rectangle2Df r(pCoordX, pCoordY, width, height, !isCentered) ;

        assert(fclose_to(r.getBottomLeftCornerX(), pCoordX)) ;
        assert(fclose_to(r.getBottomLeftCornerY(), pCoordY)) ;
        assert(fclose_to(r.getUpRightCornerX(), pCoordX + width)) ;
        assert(fclose_to(r.getUpRightCornerY(), pCoordY + height)) ;
        assert(fclose_to(r.getWidth(), width)) ;
        assert(fclose_to(r.getHeight(), height)) ;
    }

    // Rectangle from Point and Dimension (as individual values, centered)
    {
        Scalar pCoordX = 48.85f ;
        Scalar pCoordY = -56.485f ;
        Scalar width = 125.f ;
        Scalar height = 418.48f ;
        bool isCentered = true ;
        Rectangle2Df r(pCoordX, pCoordY, width, height, isCentered) ;

        assert(fclose_to(r.getBottomLeftCornerX(), pCoordX - (width / 2.f))) ;
        assert(fclose_to(r.getBottomLeftCornerY(), pCoordY - (height / 2.f))) ;
        assert(fclose_to(r.getUpRightCornerX(), pCoordX + (width / 2.f))) ;
        assert(fclose_to(r.getUpRightCornerY(), pCoordY + (height / 2.f))) ;
        assert(fclose_to(r.getWidth(), width)) ;
        assert(fclose_to(r.getHeight(), height)) ;
    }

    // Rectangle from two points
    {
        Scalar p1CoordX = 4187.418974f ;
        Scalar p1CoordY = -125.148f ;
        Point2Df p1(p1CoordX, p1CoordY) ;
        Scalar p2CoordX = 9874.48f ;
        Scalar p2CoordY = 4189.1584f ;
        Point2Df p2(p2CoordX, p2CoordY) ;
        Rectangle2Df r(p1, p2) ;

        assert(fclose_to(r.getBottomLeftCornerX(), p1CoordX)) ;
        assert(fclose_to(r.getBottomLeftCornerY(), p1CoordY)) ;
        assert(fclose_to(r.getUpRightCornerX(), p2CoordX)) ;
        assert(fclose_to(r.getUpRightCornerY(), p2CoordY)) ;
        assert(fclose_to(r.getWidth(), (p2CoordX - p1CoordX))) ;
        assert(fclose_to(r.getHeight(), (p2CoordY - p1CoordY))) ;
    }

    // Rectangle from two points (as individual values)
    {
        Scalar p1CoordX = -12.848f ;
        Scalar p1CoordY = 158.418f ;
        Scalar p2CoordX = 154.1485f ;
        Scalar p2CoordY = 944.4185f ;
        Rectangle2Df r(p1CoordX, p1CoordY, p2CoordX, p2CoordY) ;

        assert(fclose_to(r.getBottomLeftCornerX(), p1CoordX)) ;
        assert(fclose_to(r.getBottomLeftCornerY(), p1CoordY)) ;
        assert(fclose_to(r.getUpRightCornerX(), p2CoordX)) ;
        assert(fclose_to(r.getUpRightCornerY(), p2CoordY)) ;
        assert(fclose_to(r.getWidth(), (p2CoordX - p1CoordX))) ;
        assert(fclose_to(r.getHeight(), (p2CoordY - p1CoordY))) ;
    }
}

/** @brief  Test translation of Rectangle2D objects. */
static void ftest_translation() {
        Scalar p1CoordX = -964.14857f ;
        Scalar p1CoordY = -184.487f ;
        Point2Df p1(p1CoordX, p1CoordY) ;
        Scalar p2CoordX = -50.48f ;
        Scalar p2CoordY = 5.0485f ;
        Point2Df p2(p2CoordX, p2CoordY) ;
        Rectangle2Df r(p1, p2) ;

        Scalar translationX = 478.48f ;
        Scalar translationY = -55.0485f ;
        r.translate(translationX, translationY) ;

        assert(fclose_to(r.getBottomLeftCornerX(), (p1CoordX + translationX))) ;
        assert(fclose_to(r.getUpRightCornerX(), (p2CoordX + translationX))) ;
        assert(fclose_to(r.getBottomLeftCornerY(), (p1CoordY + translationY))) ;
        assert(fclose_to(r.getUpRightCornerY(), (p2CoordY + translationY))) ;
}

/** @brief  Test containing functions of Rectangle2D objects. */
static void ftest_contain() {
    Scalar p1CoordX = 48.1487f ;
    Scalar p1CoordY = -56.4185f ;
    Scalar p2CoordX = 97898.1458f ;
    Scalar p2CoordY = -4.89f ;
    Rectangle2Df r(p1CoordX, p1CoordY, p2CoordX, p2CoordY) ;

    // Contains point (yes / no)
    {
        Scalar pTestInX = 947.48f ;
        Scalar pTestInY = -7.415f ;
        Point2Df pTestIn(pTestInX, pTestInY) ;
        assert(r.contains(pTestInX, pTestInY)) ;
        assert(r.contains(pTestIn)) ;

        Scalar pTestOut1X = -455.48f ;
        Scalar pTestOut1Y = -7.415f ;
        Point2Df pTestOut1(pTestOut1X, pTestOut1Y) ;
        assert(!r.contains(pTestOut1X, pTestOut1Y)) ;
        assert(!r.contains(pTestOut1)) ;

        Scalar pTestOut2X = 947.48f ;
        Scalar pTestOut2Y = -7847.415f ;
        Point2Df pTestOut2(pTestOut2X, pTestOut2Y) ;
        assert(!r.contains(pTestOut2X, pTestOut2Y)) ;
        assert(!r.contains(pTestOut2)) ;

        Scalar pTestOut3X = -5485.87f ;
        Scalar pTestOut3Y = 4877854.415f ;
        Point2Df pTestOut3(pTestOut3X, pTestOut3Y) ;
        assert(!r.contains(pTestOut3X, pTestOut3Y)) ;
        assert(!r.contains(pTestOut3)) ;
    }

    // Contains another rectangle (yes / no)
    {
        Scalar insideP1CoordX = 9674.477f ;
        Scalar insideP1CoordY = -45.45f ;
        Point2Df insideP1(insideP1CoordX, insideP1CoordY) ;
        Scalar insideP2CoordX = 18750.48f ;
        Scalar insideP2CoordY = -21.0148f ;
        Point2Df insideP2(insideP2CoordX, insideP2CoordY) ;
        Rectangle2Df inside(insideP1, insideP2) ;

        assert(r.contains(inside)) ;
        assert(
               r.contains(
                          insideP1CoordX,
                          insideP1CoordY,
                          inside.getWidth(),
                          inside.getHeight()
                         )
              ) ;


        Scalar outsideP1CoordX = -487.477f ;
        Scalar outsideP1CoordY = -45.45f ;
        Point2Df outsideP1(outsideP1CoordX, outsideP1CoordY) ;
        Scalar outsideP2CoordX = 18750.48f ;
        Scalar outsideP2CoordY = -21.0148f ;
        Point2Df outsideP2(outsideP2CoordX, outsideP2CoordY) ;
        Rectangle2Df outside(outsideP1, outsideP2) ;

        assert(!r.contains(outside)) ;
        assert(
               !r.contains(
                           outsideP1CoordX,
                           outsideP1CoordY,
                           outside.getWidth(),
                           outside.getHeight()
                          )
              ) ;
    }
}

/** @brief  Test intersection functions of Rectangle2D objects. */
static void ftest_intersect() {
    Scalar p1CoordX = 48.1487f ;
    Scalar p1CoordY = -56.4185f ;
    Scalar p2CoordX = 97898.1458f ;
    Scalar p2CoordY = -4.89f ;
    Rectangle2Df r(p1CoordX, p1CoordY, p2CoordX, p2CoordY) ;

    // Intersects another rectangle
    {
        // Inner rectangles are considered as intersecting the bigger one.
        Scalar insideP1CoordX = 9674.477f ;
        Scalar insideP1CoordY = -45.45f ;
        Point2Df insideP1(insideP1CoordX, insideP1CoordY) ;
        Scalar insideP2CoordX = 18750.48f ;
        Scalar insideP2CoordY = -21.0148f ;
        Point2Df insideP2(insideP2CoordX, insideP2CoordY) ;
        Rectangle2Df inside(insideP1, insideP2) ;

        assert(r.intersects(inside)) ;
        assert(
               r.intersects(
                            insideP1CoordX,
                            insideP1CoordY,
                            inside.getWidth(),
                            inside.getHeight()
                           )
              ) ;


        // Not totally outside Rectangle... should intersects.
        Scalar outside1P1CoordX = -487.477f ;
        Scalar outside1P1CoordY = -45.45f ;
        Point2Df outside1P1(outside1P1CoordX, outside1P1CoordY) ;
        Scalar outside1P2CoordX = 18750.48f ;
        Scalar outside1P2CoordY = -21.0148f ;
        Point2Df outside1P2(outside1P2CoordX, outside1P2CoordY) ;
        Rectangle2Df outside1(outside1P1, outside1P2) ;

        assert(r.intersects(outside1)) ;
        assert(
               r.intersects(
                            outside1P1CoordX,
                            outside1P1CoordY,
                            outside1.getWidth(),
                            outside1.getHeight()
                           )
              ) ;


        // Totally outside Rectangle, should not intersect.
        Scalar outside2P1CoordX = -487.477f ;
        Scalar outside2P1CoordY = 39.45f ;
        Point2Df outside2P1(outside2P1CoordX, outside2P1CoordY) ;
        Scalar outside2P2CoordX = -45.48f ;
        Scalar outside2P2CoordY = 198.0148f ;
        Point2Df outside2P2(outside2P2CoordX, outside2P2CoordY) ;
        Rectangle2Df outside2(outside2P1, outside2P2) ;

        assert(!r.intersects(outside2)) ;
        assert(
               !r.intersects(
                             outside2P1CoordX,
                             outside2P1CoordY,
                             outside2.getWidth(),
                             outside2.getHeight()
                            )
              ) ;
    }
}

/** @brief  Test position functions of Rectangle2D objects. */
static void ftest_position() {
    Scalar p1CoordX = 12.64f ;
    Scalar p1CoordY = 0.128f ;
    Scalar p2CoordX = 645.54f ;
    Scalar p2CoordY = 150.418f ;
    Rectangle2Df r(p1CoordX, p1CoordY, p2CoordX, p2CoordY) ;

    // Point on left
    {
        Scalar pLeftX = 0.4185f ;
        Scalar pLeftY = 18.485f ;
        Point2Df pLeft(pLeftX, pLeftY) ;

        assert(r.position(pLeftX, pLeftY) & Rectangle2Df::PointOnLeft) ;
        assert(r.position(pLeft) & Rectangle2Df::PointOnLeft) ;
    }

    // Point on top
    {
        Scalar pTopX = 45.74f ;
        Scalar pTopY = 1887.4867f ;
        Point2Df pTop(pTopX, pTopY) ;

        assert(r.position(pTopX, pTopY) & Rectangle2Df::PointAbove) ;
        assert(r.position(pTop) & Rectangle2Df::PointAbove) ;
    }

    // Point on right
    {
        Scalar pRightX = 985.485f ;
        Scalar pRightY = 54.574f ;
        Point2Df pRight(pRightX, pRightY) ;

        assert(r.position(pRightX, pRightY) & Rectangle2Df::PointOnRight) ;
        assert(r.position(pRight) & Rectangle2Df::PointOnRight) ;
    }

    // Point on bottom
    {
        Scalar pBottomX = 45.74f ;
        Scalar pBottomY = -1887.4867f ;
        Point2Df pBottom(pBottomX, pBottomY) ;

        assert(r.position(pBottomX, pBottomY) & Rectangle2Df::PointBelow) ;
        assert(r.position(pBottom) & Rectangle2Df::PointBelow) ;
    }
}

/** @brief  Test operators of Rectangle2D objects. */
static void ftest_operators() {
    // Operators =, == and !=
    {
        Scalar rOriginalp1CoordX = 54.45f ;
        Scalar rOriginalp1CoordY = 54.45f ;
        Scalar rOriginalp2CoordX = 968.45f ;
        Scalar rOriginalp2CoordY = 158.0485f ;
        Rectangle2Df rOriginal(
                               rOriginalp1CoordX,
                               rOriginalp1CoordY,
                               rOriginalp2CoordX,
                               rOriginalp2CoordY
                              ) ;

        Rectangle2Df rCopyConstr(rOriginal) ;
        Rectangle2Df rCopy = rOriginal ;
        assert(rCopyConstr == rCopy) ;
        assert(rOriginal == rCopy) ;
        assert(fclose_to(rCopy.getBottomLeftCornerX(),  rOriginal.getBottomLeftCornerX())) ;
        assert(fclose_to(rCopy.getBottomLeftCornerY(),  rOriginal.getBottomLeftCornerY())) ;
        assert(fclose_to(rCopy.getUpRightCornerX(),     rOriginal.getUpRightCornerX())) ;
        assert(fclose_to(rCopy.getUpRightCornerY(),     rOriginal.getUpRightCornerY())) ;
        assert(fclose_to(rCopy.getWidth(),              rOriginal.getWidth())) ;
        assert(fclose_to(rCopy.getHeight(),             rOriginal.getHeight())) ;

        Scalar rDifferentp1CoordX = 854.485f ;
        Scalar rDifferentp1CoordY = -3267.4798f ;
        Scalar rDifferentp2CoordX = 9741245.485f ;
        Scalar rDifferentp2CoordY = -94.4187f ;
        Rectangle2Df rDifferent(
                               rDifferentp1CoordX,
                               rDifferentp1CoordY,
                               rDifferentp2CoordX,
                               rDifferentp2CoordY
                              ) ;
        assert(rOriginal != rDifferent) ;
    }

    // Operators + and +=
    {
        // Point merged
        Scalar rOriginalp1CoordX = 45.14857f ;
        Scalar rOriginalp1CoordY = 5.85748f ;
        Scalar rOriginalp2CoordX = 65.9875f ;
        Scalar rOriginalp2CoordY = 15.78f ;
        Rectangle2Df rOriginal(
                               rOriginalp1CoordX,
                               rOriginalp1CoordY,
                               rOriginalp2CoordX,
                               rOriginalp2CoordY
                              ) ;

        Scalar pMergedX = -.7482f ;
        Scalar pMergedY = .4185f ;
        Point2Df pMerged(pMergedX, pMergedY) ;

        rOriginal += pMerged ;
        assert(fclose_to(rOriginal.getBottomLeftCornerX(), pMergedX)) ;
        assert(fclose_to(rOriginal.getBottomLeftCornerY(), pMergedY)) ;
        assert(fclose_to(rOriginal.getUpRightCornerX(), rOriginalp2CoordX)) ;
        assert(fclose_to(rOriginal.getUpRightCornerY(), rOriginalp2CoordY)) ;

        // Rectangle merged
        Scalar pMergedP1CoordX = 9.48f ;
        Scalar pMergedP1CoordY = -85.48f ;
        Scalar pMergedP2CoordX = 57.87f ;
        Scalar pMergedP2CoordY = 10.987f ;
        Rectangle2Df rMerged(
                             pMergedP1CoordX,
                             pMergedP1CoordY,
                             pMergedP2CoordX,
                             pMergedP2CoordY
                            ) ;
        rOriginal += rMerged ;

        assert(fclose_to(rOriginal.getBottomLeftCornerX(), pMergedX)) ;
        assert(fclose_to(rOriginal.getBottomLeftCornerY(), pMergedP1CoordY)) ;
        assert(fclose_to(rOriginal.getUpRightCornerX(), rOriginalp2CoordX)) ;
        assert(fclose_to(rOriginal.getUpRightCornerY(), rOriginalp2CoordY)) ;
    }
}

int main() {
    ftest_allocation() ;
    ftest_translation() ;
    ftest_contain() ;
    ftest_intersect() ;
    ftest_position() ;
    ftest_operators() ;

    return TestResult ; // Defined in <mock_assert.h>
}
