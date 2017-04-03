#include <modules/points/UTPoint2Df.hpp>
#include <geometry/points/Point2Df.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTPoint2Df::UTPoint2Df() {}

    UTPoint2Df::~UTPoint2Df() {}

    void UTPoint2Df::allocation() {
        Point2Df p1 ;
        check(compare(p1.get(Point2Df::Axis::X), 0.f)) ;
        check(compare(p1.get(Point2Df::Axis::Y), 0.f)) ;

        Scalar p2X = 9.48f ;
        Scalar p2Y = -56.474f ;
        Point2Df p2(p2X, p2Y) ;
        check(compare(p2.get(Point2Df::Axis::X), p2X)) ;
        check(compare(p2.get(Point2Df::Axis::Y), p2Y)) ;

        Point2Df p3(p2) ;
        check(compare(p3.get(Point2Df::Axis::X), p2X)) ;
        check(compare(p3.get(Point2Df::Axis::Y), p2Y)) ;
        check(compare(p3.get(Point2Df::Axis::X), p2.get(Point2Df::Axis::X))) ;
        check(compare(p3.get(Point2Df::Axis::Y), p2.get(Point2Df::Axis::Y))) ;

        p1.set(Point2Df::Axis::X, p2Y) ;
        p1.set(Point2Df::Axis::Y, p2X) ;
        check(compare(p1.get(Point2Df::Axis::X), p2Y)) ;
        check(compare(p1.get(Point2Df::Axis::Y), p2X)) ;
        check(compare(p1.get(Point2Df::Axis::X), p2.get(Point2Df::Axis::Y))) ;
        check(compare(p1.get(Point2Df::Axis::Y), p2.get(Point2Df::Axis::X))) ;

        Scalar p4X = -2241.4f ;
        Scalar p4Y = 0.04854f ;
        Point2Df p4(p4X, p4Y) ;
        p1.set(p4) ;
        check(compare(p1.get(Point2Df::Axis::X), p4X)) ;
        check(compare(p1.get(Point2Df::Axis::Y), p4Y)) ;
        check(compare(p1.get(Point2Df::Axis::X), p4.get(Point2Df::Axis::X))) ;
        check(compare(p1.get(Point2Df::Axis::Y), p4.get(Point2Df::Axis::Y))) ;

        p4.set(p2X, p2Y) ;
        check(compare(p4.get(Point2Df::Axis::X), p2X)) ;
        check(compare(p4.get(Point2Df::Axis::Y), p2Y)) ;
        check(compare(p4.get(Point2Df::Axis::X), p2.get(Point2Df::Axis::X))) ;
        check(compare(p4.get(Point2Df::Axis::Y), p2.get(Point2Df::Axis::Y))) ;
    }

    void UTPoint2Df::utilities() {
        Scalar p1X = 94.415f ;
        Scalar p1Y = -56.44f ;
        Point2Df p1(p1X, p1Y) ;

        Scalar p2X = -54.45f ;
        Scalar p2Y = 418.88781f ;
        Point2Df p2(p2X, p2Y) ;

        // Translation
        p1.translate(p2) ;
        check(compare(p1.get(Point2Df::Axis::X), p1X + p2X)) ;
        check(compare(p1.get(Point2Df::Axis::Y), p1Y + p2Y)) ;

        p2.translate(p1X, p1Y) ;
        check(compare(p2.get(Point2Df::Axis::X), p1X + p2X)) ;
        check(compare(p2.get(Point2Df::Axis::Y), p1Y + p2Y)) ;

        p2.translate(p2Y, p2X) ;
        check(compare(p2.get(Point2Df::Axis::X), p1X + p2X + p2Y)) ;
        check(compare(p2.get(Point2Df::Axis::Y), p1Y + p2Y + p2X)) ;

        // Dot product
        Scalar expectedP1DotP2 = (p1.get(Point2Df::Axis::X) * p2.get(Point2Df::Axis::X))
                                    + (p1.get(Point2Df::Axis::Y) * p2.get(Point2Df::Axis::Y)) ;
        Scalar computedP1DotP2 = p1.dot(p2) ;
        check(compare(computedP1DotP2, expectedP1DotP2)) ;
    }
}
