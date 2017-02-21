#include <modules/lines/UTLine2Di.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTLine2Di::UTLine2Di() {}

    UTLine2Di::~UTLine2Di() {}

    void UTLine2Di::allocation() {
        Line2Di l1 ;
        check(l1.getStartX() == 0) ;
        check(l1.getStartY() == 0) ;
        check(l1.getEndX() == 0) ;
        check(l1.getEndY() == 0) ;

        int pStartX = 5 ;
        int pStartY = 0 ;
        Point2Di pStart(pStartX, pStartY) ;

        int pEndX = 54 ;
        int pEndY = -452 ;
        Point2Di pEnd(pEndX, pEndY) ;

        Line2Di l2(pStart, pEnd) ;
        check(l2.getStartX() == pStartX) ;
        check(l2.getStartY() == pStartY) ;
        check(l2.getEndX() == pEndX) ;
        check(l2.getEndY() == pEndY) ;
        check(l2 != l1) ;

        Line2Di l3(l2) ;
        check(l3.getStartX() == l2.getStartX()) ;
        check(l3.getStartY() == l2.getStartY()) ;
        check(l3.getEndX() == l2.getEndX()) ;
        check(l3.getEndY() == l2.getEndY()) ;
        check(l3 == l2) ;
    }

    void UTLine2Di::utilities() {
        // Line 1
        int p1StartX = 9 ;
        int p1StartY = 15 ;
        Point2Di p1Start(p1StartX, p1StartY) ;

        int p1EndX = -458 ;
        int p1EndY = 15 ;
        Point2Di p1End(p1EndX, p1EndY) ;

        Line2Di l1(p1Start, p1End) ;

        // Line 2
        int p2StartX = -0 ;
        int p2StartY = -87 ;
        Point2Di p2Start(p2StartX, p2StartY) ;

        int p2EndX = 78 ;
        int p2EndY = -0 ;
        Point2Di p2End(p2EndX, p2EndY) ;

        Line2Di l2(p2Start, p2End) ;

        // Line 3
        int p3EndX = -97 ;
        int p3EndY = 80 ;
        Point2Di p3End(p3EndX, p3EndY) ;

        Line2Di l3(p3End, p1Start) ;

        // Line 4
        Line2Di l4(p1End, p1Start) ;

        // Line 5
        Line2Di l5(l1) ;


        // Lengths
        double expectedL1SquaredLength = 218089 ;
        double computedL1SquaredLength = pow(p1EndX - p1StartX, 2) + pow(p1EndY - p1StartY, 2) ;
        check(expectedL1SquaredLength == expectedL1SquaredLength) ;
        double expectedL1Length = 467 ;
        double computedL1Length = sqrt(computedL1SquaredLength) ;
        check(expectedL1Length == computedL1Length) ;

        check(l1.length() == computedL1Length) ;
        check(l1.lengthSquared() == computedL1SquaredLength) ;

        // Contiguous lines
        check(!l1.isContiguousTo(l2)) ;
        check(l1.isContiguousTo(l3)) ;
        check(l1.isContiguousTo(l4)) ;
        check(!l1.isContiguousTo(l5)) ;

        // Relative CCW
        check(Line2Di::CCW(l1, Point2Di(0, 500)) == 1) ;
        check(Line2Di::CCW(l1, Point2Di(0, 0)) == -1) ;

        // Relative line to plan origin
        Line2Di relativeL1 = Line2Di::relative(l1) ;
        check(relativeL1.getStartX() == 0) ;
        check(relativeL1.getStartY() == 0) ;
        check(relativeL1.getEndX() == (p1EndX - p1StartX)) ;
        check(relativeL1.getEndY() == (p1EndY - p1StartY)) ;
    }

    void UTLine2Di::intersections() {
        // Line 1 (horizontal)
        int p1StartX = -50 ;
        int p1StartY = 10 ;
        Point2Di p1Start(p1StartX, p1StartY) ;

        int p1EndX = 480 ;
        int p1EndY = 10 ;
        Point2Di p1End(p1EndX, p1EndY) ;

        Line2Di l1(p1Start, p1End) ;

        // Line 2 (vertical)
        int p2StartX = 2 ;
        int p2StartY = -945 ;
        Point2Di p2Start(p2StartX, p2StartY) ;

        int p2EndX = 2 ;
        int p2EndY = 210;
        Point2Di p2End(p2EndX, p2EndY) ;

        Line2Di l2(p2Start, p2End) ;

        // Line 3 (to up right)
        int p3StartX = -32 ;
        int p3StartY = -5 ;
        Point2Di p3Start(p3StartX, p3StartY) ;

        int p3EndX = 95 ;
        int p3EndY = 15 ;
        Point2Di p3End(p3EndX, p3EndY) ;

        Line2Di l3(p3Start, p3End) ;

        // Line 4 (to down right)
        int p4StartX = -164 ;
        int p4StartY = 485 ;
        Point2Di p4Start(p4StartX, p4StartY) ;

        int p4EndX = 158 ;
        int p4EndY = -156 ;
        Point2Di p4End(p4EndX, p4EndY) ;

        Line2Di l4(p4Start, p4End) ;

        // Line 5 (little)
        int p5StartX = 65 ;
        int p5StartY = 23 ;
        Point2Di p5Start(p5StartX, p5StartY) ;

        int p5EndX = 66 ;
        int p5EndY = 22 ;
        Point2Di p5End(p5EndX, p5EndY) ;

        Line2Di l5(p5Start, p5End) ;

        // Line 6 (as Line 1)
        Line2Di l6(l1) ;


        check(l1.intersects(l2)) ;
        check(l1.intersects(l3)) ;
        check(l1.intersects(l4)) ;
        check(not l1.intersects(l5)) ;
        check(l1.intersects(l6)) ;

        check(l2.intersects(l1)) ;
        check(l2.intersects(l2)) ;
        check(l2.intersects(l3)) ;
        check(l2.intersects(l4)) ;
        check(not l2.intersects(l5)) ;
        check(l2.intersects(l6)) ;

        check(l3.intersects(l4)) ;
        check(not l3.intersects(l5)) ;
        check(l3.intersects(l6)) ;
    }

    void UTLine2Di::distance() {
        // Line 1
        int p1StartX = 0 ;
        int p1StartY = -10 ;
        Point2Di p1Start(p1StartX, p1StartY) ;

        int p1EndX = 0 ;
        int p1EndY = 10 ;
        Point2Di p1End(p1EndX, p1EndY) ;

        Line2Di l1(p1Start, p1End) ;


        // Distance to Point A (at 5 units on right of L1)
        Point2Di pointA(5, 0) ;
        float expectedDistanceA = pointDistance(l1, pointA) ;
        check(compare(l1.distanceTo(pointA), expectedDistanceA)) ;

        // Seem difficult to evaluate, formula not well understood...
        Point2Di pointB(10, 5) ;
        float expectedDistanceB = pointDistance(l1, pointB) ;
        check(compare(l1.distanceTo(pointB), expectedDistanceB)) ;
    }

    UTLine::LinearEquation UTLine2Di::getEquation(const Line2Di& line) {
        LinearEquation equation ;

        float diffX = line.getEndX() - line.getStartX() ;
        float diffY = line.getEndY() - line.getStartY() ;
        equation.m_gradient = diffY / diffX ;
        equation.m_yIntercept = line.getStartY() - (equation.m_gradient * line.getStartX()) ;

        return equation ;
    }

    float UTLine2Di::pointDistance(const Line2Di& line, const Point2Di& point) {
        // Line equation: ax + by + c = 0,
        // where a is the gradient and c the point at which the line crosses the
        // y-axis (b is equal to -1 here).
        auto lineEquation = getEquation(line) ;
        float a = lineEquation.m_gradient ;
        const float b = -1 ;
        float c = lineEquation.m_yIntercept ;

        float numerator = std::abs((a * point.getX()) + (b * point.getY()) + c) ;
        float denominator = std::sqrt(((a * a) + (b * b))) ;
        return numerator / denominator ;
    }
}
