#include <modules/points/UTPoint2Di.hpp>
#include <geometry/points/Point2Di.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTPoint2Di::UTPoint2Di() {}

    UTPoint2Di::~UTPoint2Di() {}

    void UTPoint2Di::allocation() {
        Point2Di p1 ;
        check(p1.getX() == 0) ;
        check(p1.getY() == 0) ;

        Scalar p2X = 9 ;
        Scalar p2Y = -56 ;
        Point2Di p2(p2X, p2Y) ;
        check(p2.getX() == p2X) ;
        check(p2.getY() == p2Y) ;

        Point2Di p3(p2) ;
        check(p3.getX() == p2X) ;
        check(p3.getY() == p2Y) ;
        check(p3.getX() == p2.getX()) ;
        check(p3.getY() == p2.getY()) ;

        p1.setX(p2Y) ;
        p1.setY(p2X) ;
        check(p1.getX() == p2Y) ;
        check(p1.getY() == p2X) ;
        check(p1.getX() == p2.getY()) ;
        check(p1.getY() == p2.getX()) ;

        Scalar p4X = -15 ;
        Scalar p4Y = 89 ;
        Point2Di p4(p4X, p4Y) ;
        p1.set(p4) ;
        check(p1.getX() == p4X) ;
        check(p1.getY() == p4Y) ;
        check(p1.getX() == p4.getX()) ;
        check(p1.getY() == p4.getY()) ;

        p4.set(p2X, p2Y) ;
        check(p4.getX() == p2X) ;
        check(p4.getY() == p2Y) ;
        check(p4.getX() == p2.getX()) ;
        check(p4.getY() == p2.getY()) ;
    }

    void UTPoint2Di::utilities() {
        Scalar p1X = 94 ;
        Scalar p1Y = -56 ;
        Point2Di p1(p1X, p1Y) ;

        Scalar p2X = -54 ;
        Scalar p2Y = 418 ;
        Point2Di p2(p2X, p2Y) ;

        // Translation
        p1.translate(p2) ;
        check(p1.getX() == p1X + p2X) ;
        check(p1.getY() == p1Y + p2Y) ;

        p2.translate(p1X, p1Y) ;
        check(p2.getX() == p1X + p2X) ;
        check(p2.getY() == p1Y + p2Y) ;

        p2.translate(p2Y, p2X) ;
        check(p2.getX() == p1X + p2X + p2Y) ;
        check(p2.getY() == p1Y + p2Y + p2X) ;

        // Dot product
        Scalar expectedP1DotP2 = (p1.getX() * p2.getX()) + (p1.getY() * p2.getY()) ;
        Scalar computedP1DotP2 = p1.dot(p2) ;
        check(computedP1DotP2 == expectedP1DotP2) ;
    }
}
