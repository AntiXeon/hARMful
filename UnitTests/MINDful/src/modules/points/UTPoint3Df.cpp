#include <modules/points/UTPoint3Df.hpp>
#include <geometry/points/Point3Df.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTPoint3Df::UTPoint3Df() {}

    UTPoint3Df::~UTPoint3Df() {}

    void UTPoint3Df::allocation() {
        Point3Df p1 ;
        check(compare(p1.get(Point3Df::Axis::X), 0.f)) ;
        check(compare(p1.get(Point3Df::Axis::Y), 0.f)) ;
        check(compare(p1.get(Point3Df::Axis::Z), 0.f)) ;

        Scalar p2X = 9.48f ;
        Scalar p2Y = -56.474f ;
        Scalar p2Z = 45.8f ;
        Point3Df p2(p2X, p2Y, p2Z) ;
        check(compare(p2.get(Point3Df::Axis::X), p2X)) ;
        check(compare(p2.get(Point3Df::Axis::Y), p2Y)) ;
        check(compare(p2.get(Point3Df::Axis::Z), p2Z)) ;

        Point3Df p3(p2) ;
        check(compare(p3.get(Point3Df::Axis::X), p2X)) ;
        check(compare(p3.get(Point3Df::Axis::Y), p2Y)) ;
        check(compare(p3.get(Point3Df::Axis::Z), p2Z)) ;
        check(compare(p3.get(Point3Df::Axis::X), p2.get(Point3Df::Axis::X))) ;
        check(compare(p3.get(Point3Df::Axis::Y), p2.get(Point3Df::Axis::Y))) ;
        check(compare(p3.get(Point3Df::Axis::Z), p2.get(Point3Df::Axis::Z))) ;

        p1.set(Point3Df::Axis::X, p2Y) ;
        p1.set(Point3Df::Axis::Y, p2Z) ;
        p1.set(Point3Df::Axis::Z, p2X) ;
        check(compare(p1.get(Point3Df::Axis::X), p2Y)) ;
        check(compare(p1.get(Point3Df::Axis::Y), p2Z)) ;
        check(compare(p1.get(Point3Df::Axis::Z), p2X)) ;
        check(compare(p1.get(Point3Df::Axis::X), p2.get(Point3Df::Axis::Y))) ;
        check(compare(p1.get(Point3Df::Axis::Y), p2.get(Point3Df::Axis::Z))) ;
        check(compare(p1.get(Point3Df::Axis::Z), p2.get(Point3Df::Axis::X))) ;

        Scalar p4X = -2241.4f ;
        Scalar p4Y = 0.04854f ;
        Scalar p4Z = 52.377f ;
        Point3Df p4(p4X, p4Y, p4Z) ;
        p1.set(p4) ;
        check(compare(p1.get(Point3Df::Axis::X), p4X)) ;
        check(compare(p1.get(Point3Df::Axis::Y), p4Y)) ;
        check(compare(p1.get(Point3Df::Axis::Z), p4Z)) ;
        check(compare(p1.get(Point3Df::Axis::X), p4.get(Point3Df::Axis::X))) ;
        check(compare(p1.get(Point3Df::Axis::Y), p4.get(Point3Df::Axis::Y))) ;
        check(compare(p1.get(Point3Df::Axis::Z), p4.get(Point3Df::Axis::Z))) ;

        p4.set(p2X, p2Y, p2Z) ;
        check(compare(p4.get(Point3Df::Axis::X), p2X)) ;
        check(compare(p4.get(Point3Df::Axis::Y), p2Y)) ;
        check(compare(p4.get(Point3Df::Axis::Z), p2Z)) ;
        check(compare(p4.get(Point3Df::Axis::X), p2.get(Point3Df::Axis::X))) ;
        check(compare(p4.get(Point3Df::Axis::Y), p2.get(Point3Df::Axis::Y))) ;
        check(compare(p4.get(Point3Df::Axis::Z), p2.get(Point3Df::Axis::Z))) ;
    }

    void UTPoint3Df::utilities() {
        Scalar p1X = 94.415f ;
        Scalar p1Y = -56.44f ;
        Scalar p1Z = 9.4f ;
        Point3Df p1(p1X, p1Y, p1Z) ;

        Scalar p2X = -54.45f ;
        Scalar p2Y = 418.88781f ;
        Scalar p2Z = 9.67f ;
        Point3Df p2(p2X, p2Y, p2Z) ;

        // Translation
        p1.translate(p2) ;
        check(compare(p1.get(Point3Df::Axis::X), p1X + p2X)) ;
        check(compare(p1.get(Point3Df::Axis::Y), p1Y + p2Y)) ;
        check(compare(p1.get(Point3Df::Axis::Z), p1Z + p2Z)) ;

        p2.translate(p1X, p1Y, p1Z) ;
        check(compare(p2.get(Point3Df::Axis::X), p1X + p2X)) ;
        check(compare(p2.get(Point3Df::Axis::Y), p1Y + p2Y)) ;
        check(compare(p2.get(Point3Df::Axis::Z), p1Z + p2Z)) ;

        p2.translate(p2Y, p2X, p2Z) ;
        check(compare(p2.get(Point3Df::Axis::X), p1X + p2X + p2Y)) ;
        check(compare(p2.get(Point3Df::Axis::Y), p1Y + p2Y + p2X)) ;
        check(compare(p2.get(Point3Df::Axis::Z), p1Z + p2Z + p2Z)) ;

        // Dot product
        Scalar expectedP1DotP2 = (p1.get(Point3Df::Axis::X) * p2.get(Point3Df::Axis::X)) + (p1.get(Point3Df::Axis::Y) * p2.get(Point3Df::Axis::Y)) + (p1.get(Point3Df::Axis::Z) * p2.get(Point3Df::Axis::Z)) ;
        Scalar computedP1DotP2 = p1.dot(p2) ;
        check(compare(computedP1DotP2, expectedP1DotP2)) ;
    }
}
