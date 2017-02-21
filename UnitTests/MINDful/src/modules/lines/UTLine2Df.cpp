#include <modules/lines/UTLine2Df.hpp>
#include <string>
#include <iostream>
#include <cmath>

using namespace Mind ;

namespace UTMind {
    UTLine2Df::UTLine2Df() {}

    UTLine2Df::~UTLine2Df() {}

    void UTLine2Df::allocation() {
        Line2Df l1 ;
        check(l1.getStartX() == 0.f) ;
        check(l1.getStartY() == 0.f) ;
        check(l1.getEndX() == 0.f) ;
        check(l1.getEndY() == 0.f) ;

        Scalar pStartX = 5.75f ;
        Scalar pStartY = 0.574f ;
        Point2Df pStart(pStartX, pStartY) ;

        Scalar pEndX = 54.12f ;
        Scalar pEndY = -452.4f ;
        Point2Df pEnd(pEndX, pEndY) ;

        Line2Df l2(pStart, pEnd) ;
        check(l2.getStartX() == pStartX) ;
        check(l2.getStartY() == pStartY) ;
        check(l2.getEndX() == pEndX) ;
        check(l2.getEndY() == pEndY) ;
        check(l2 != l1) ;

        Line2Df l3(l2) ;
        check(l3.getStartX() == l2.getStartX()) ;
        check(l3.getStartY() == l2.getStartY()) ;
        check(l3.getEndX() == l2.getEndX()) ;
        check(l3.getEndY() == l2.getEndY()) ;
        check(l3 == l2) ;
    }

    void UTLine2Df::utilities() {
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
        check(compare(expectedL1SquaredLength, expectedL1SquaredLength)) ;
        double expectedL1Length = 467.82509491154918163612 ;
        double computedL1Length = sqrt(computedL1SquaredLength) ;
        check(compare(expectedL1Length, computedL1Length)) ;

        check(compare(l1.length(), computedL1Length)) ;
        check(compare(l1.lengthSquared(), computedL1SquaredLength)) ;

        // Contiguous lines
        check(!l1.isContiguousTo(l2)) ;
        check(l1.isContiguousTo(l3)) ;
        check(l1.isContiguousTo(l4)) ;
        check(!l1.isContiguousTo(l5)) ;

        // Relative CCW
        check(Line2Df::CCW(l1, Point2Df(0.f, 500.f)) == 1) ;
        check(Line2Df::CCW(l1, Point2Df(0.f, 0.f)) == -1) ;

        // Relative line to plan origin
        Line2Df relativeL1 = Line2Df::relative(l1) ;
        check(relativeL1.getStartX() == 0.f) ;
        check(relativeL1.getStartY() == 0.f) ;
        check(relativeL1.getEndX() == (p1EndX - p1StartX)) ;
        check(relativeL1.getEndY() == (p1EndY - p1StartY)) ;
    }

    void UTLine2Df::intersections() {
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

    void UTLine2Df::distance() {
        // Line 1
        Scalar p1StartX = -14.87f ;
        Scalar p1StartY = 128.12f ;
        Point2Df p1Start(p1StartX, p1StartY) ;

        Scalar p1EndX = 98.45f ;
        Scalar p1EndY = 124.58f ;
        Point2Df p1End(p1EndX, p1EndY) ;

        Line2Df l1(p1Start, p1End) ;


        // Distance to Point A
        Point2Df pointA(4.f, -9.f) ;
        float computedDistanceA = l1.distanceTo(pointA) ;
        float expectedDistanceA = pointDistance(l1, pointA) ;
        check(compare(computedDistanceA, expectedDistanceA)) ;

        Point2Df pointB(3.f, 5.f) ;
        float computedDistanceB = l1.distanceTo(pointB) ;
        float expectedDistanceB = pointDistance(l1, pointB) ;
        check(compare(computedDistanceB, expectedDistanceB)) ;
    }

    UTLine::LinearEquation UTLine2Df::getEquation(const Line2Df& line) {
        LinearEquation equation = { 0.f, 0.f } ;

        float diffX = line.getEndX() - line.getStartX() ;
        float diffY = line.getEndY() - line.getStartY() ;

        if (!compare(diffX, 0.f) && !compare(diffY, 0.f)) {
            equation.m_gradient = diffY / diffX ;
            equation.m_yIntercept = line.getStartY() - (equation.m_gradient * line.getStartX()) ;
        }

        return equation ;
    }

    float UTLine2Df::pointDistance(const Line2Df& line, const Point2Df& point) {
        // Line equation: ax + by + c = 0,
        // where a is the gradient and c the point at which the line crosses the
        // y-axis (b is equal to -1 here).
        auto lineEquation = getEquation(line) ;
        float a = lineEquation.m_gradient ;
        const float b = -1.f ;
        float c = lineEquation.m_yIntercept ;

        float numerator = std::abs((a * point.getX()) + (b * point.getY()) + c) ;
        float denominator = std::sqrt(((a * a) + (b * b))) ;
        return numerator / denominator ;
    }
}
