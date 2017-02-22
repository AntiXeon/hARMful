#include <modules/points/UTPoint3Di.hpp>
#include <geometry/points/Point3Di.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTPoint3Di::UTPoint3Di() {}

    UTPoint3Di::~UTPoint3Di() {}

    void UTPoint3Di::allocation() {
        Point3Di p1 ;
        check(compare(p1.getX(), 0)) ;
        check(compare(p1.getY(), 0)) ;
        check(compare(p1.getZ(), 0)) ;

        Scalar p2X = 9 ;
        Scalar p2Y = -56 ;
        Scalar p2Z = 45 ;
        Point3Di p2(p2X, p2Y, p2Z) ;
        check(compare(p2.getX(), p2X)) ;
        check(compare(p2.getY(), p2Y)) ;
        check(compare(p2.getZ(), p2Z)) ;

        Point3Di p3(p2) ;
        check(compare(p3.getX(), p2X)) ;
        check(compare(p3.getY(), p2Y)) ;
        check(compare(p3.getZ(), p2Z)) ;
        check(compare(p3.getX(), p2.getX())) ;
        check(compare(p3.getY(), p2.getY())) ;
        check(compare(p3.getZ(), p2.getZ())) ;

        p1.setX(p2Y) ;
        p1.setY(p2Z) ;
        p1.setZ(p2X) ;
        check(compare(p1.getX(), p2Y)) ;
        check(compare(p1.getY(), p2Z)) ;
        check(compare(p1.getZ(), p2X)) ;
        check(compare(p1.getX(), p2.getY())) ;
        check(compare(p1.getY(), p2.getZ())) ;
        check(compare(p1.getZ(), p2.getX())) ;

        Scalar p4X = -2241 ;
        Scalar p4Y = 0 ;
        Scalar p4Z = 52 ;
        Point3Di p4(p4X, p4Y, p4Z) ;
        p1.set(p4) ;
        check(compare(p1.getX(), p4X)) ;
        check(compare(p1.getY(), p4Y)) ;
        check(compare(p1.getZ(), p4Z)) ;
        check(compare(p1.getX(), p4.getX())) ;
        check(compare(p1.getY(), p4.getY())) ;
        check(compare(p1.getZ(), p4.getZ())) ;

        p4.set(p2X, p2Y, p2Z) ;
        check(compare(p4.getX(), p2X)) ;
        check(compare(p4.getY(), p2Y)) ;
        check(compare(p4.getZ(), p2Z)) ;
        check(compare(p4.getX(), p2.getX())) ;
        check(compare(p4.getY(), p2.getY())) ;
        check(compare(p4.getZ(), p2.getZ())) ;
    }

    void UTPoint3Di::utilities() {
        Scalar p1X = 94 ;
        Scalar p1Y = -56 ;
        Scalar p1Z = 9 ;
        Point3Di p1(p1X, p1Y, p1Z) ;

        Scalar p2X = -54 ;
        Scalar p2Y = 418 ;
        Scalar p2Z = 9 ;
        Point3Di p2(p2X, p2Y, p2Z) ;

        // Translation
        p1.translate(p2) ;
        check(compare(p1.getX(), p1X + p2X)) ;
        check(compare(p1.getY(), p1Y + p2Y)) ;
        check(compare(p1.getZ(), p1Z + p2Z)) ;

        p2.translate(p1X, p1Y, p1Z) ;
        check(compare(p2.getX(), p1X + p2X)) ;
        check(compare(p2.getY(), p1Y + p2Y)) ;
        check(compare(p2.getZ(), p1Z + p2Z)) ;

        p2.translate(p2Y, p2X, p2Z) ;
        check(compare(p2.getX(), p1X + p2X + p2Y)) ;
        check(compare(p2.getY(), p1Y + p2Y + p2X)) ;
        check(compare(p2.getZ(), p1Z + p2Z + p2Z)) ;

        // Dot product
        Scalar expectedP1DotP2 = (p1.getX() * p2.getX()) + (p1.getY() * p2.getY()) + (p1.getZ() * p2.getZ()) ;
        Scalar computedP1DotP2 = p1.dot(p2) ;
        check(compare(computedP1DotP2, expectedP1DotP2)) ;
    }
}
