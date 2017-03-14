#include <modules/matrices/UTMatrix3x3f.hpp>
#include <matrices/Matrix3x3f.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTMatrix3x3f::UTMatrix3x3f() {}

    UTMatrix3x3f::~UTMatrix3x3f() {}

    void UTMatrix3x3f::allocation() {
        // Default constructor.
        Matrix3x3f m1 ;
        check(m1.at(0, 0) == 0.f) ;
        check(m1.at(1, 0) == 0.f) ;
        check(m1.at(1, 2) == 0.f) ;
        check(m1.at(2,1) == 0.f) ;
        check(m1.size() == 3) ;

        // Initial value.
        const Scalar m2DefaultValue = 5.24f ;
        Matrix3x3f m2(m2DefaultValue) ;
        check(m2.at(0, 0) == m2DefaultValue) ;
        check(m2.at(1, 0) == m2DefaultValue) ;
        check(m2.at(1, 2) == m2DefaultValue) ;
        check(m2.at(2,1) == m2DefaultValue) ;

        // Copy constructor.
        Matrix3x3f m3(m2) ;
        check(m2.at(0, 0) == m2DefaultValue) ;
        check(m2.at(1, 0) == m2DefaultValue) ;
        check(m2.at(1, 2) == m2DefaultValue) ;
        check(m2.at(2,1) == m2DefaultValue) ;
    }

    void UTMatrix3x3f::utilities() {
        // Identity and clear.
        Matrix3x3f m1 ;
        m1.identity() ;
        check(m1.at(0, 0) == 1.f) ;
        check(m1.at(0, 1) == 0.f) ;
        check(m1.at(0, 2) == 0.f) ;
        check(m1.at(1,0) == 0.f) ;
        check(m1.at(1, 1) == 1.f) ;
        check(m1.at(1, 2) == 0.f) ;
        check(m1.at(2, 0) == 0.f) ;
        check(m1.at(2, 1) == 0.f) ;
        check(m1.at(2,2) == 1.f) ;
        m1.clear() ;
        check(m1.at(0, 0) == 0.f) ;
        check(m1.at(0, 1) == 0.f) ;
        check(m1.at(0, 2) == 0.f) ;
        check(m1.at(1,0) == 0.f) ;
        check(m1.at(1, 1) == 0.f) ;
        check(m1.at(1, 2) == 0.f) ;
        check(m1.at(2, 0) == 0.f) ;
        check(m1.at(2, 1) == 0.f) ;
        check(m1.at(2,2) == 0.f) ;

        // Set values from points.
        Matrix3x3f m2 ;
        m2.identity() ;

        // ...by column.
        const Scalar p1X = 6.947f ;
        const Scalar p1Y = 7.577f ;
        Point2Df p1(p1X, p1Y) ;
        m2.setColumnValues(0, p1) ;

        const Scalar p2X = 9.7f ;
        const Scalar p2Y = -0.25f ;
        const Scalar p2Z = 1.76f ;
        Point3Df p2(p2X, p2Y, p2Z) ;
        m2.setColumnValues(2, p2) ;

        check(m2.at(0, 0) == p1X) ;
        check(m2.at(0, 1) == 0.f) ;
        check(m2.at(0, 2) == p2X) ;
        check(m2.at(1, 0) == p1Y) ;
        check(m2.at(1, 1) == 1.f) ;
        check(m2.at(1, 2) == p2Y) ;
        check(m2.at(2, 0) == 0.f) ;
        check(m2.at(2, 1) == 0.f) ;
        check(m2.at(2, 2) == p2Z) ;

        // ...by row.
        const Scalar p3X = -1.24f ;
        const Scalar p3Y = 0.57f ;
        Point2Df p3(p3X, p3Y) ;
        m2.setRowValues(1, p3) ;

        const Scalar p4X = 11.39f ;
        const Scalar p4Y = 7.495f ;
        const Scalar p4Z = -0.06f ;
        Point3Df p4(p4X, p4Y, p4Z) ;
        m2.setRowValues(2, p4) ;

        check(m2.at(0, 0) == p1X) ;
        check(m2.at(0, 1) == 0.f) ;
        check(m2.at(0, 2) == p2X) ;
        check(m2.at(1,0) == p3X) ;
        check(m2.at(1, 1) == p3Y) ;
        check(m2.at(1, 2) == p2Y) ;
        check(m2.at(2, 0) == p4X) ;
        check(m2.at(2, 1) == p4Y) ;
        check(m2.at(2,2) == p4Z) ;

        // Copy matrix.
        Matrix3x3f m3 ;
        m3.identity() ;
        m3 = m2 ;

        check(m3.at(0, 0) == p1X) ;
        check(m3.at(0, 1) == 0.f) ;
        check(m3.at(0, 2) == p2X) ;
        check(m3.at(1,0) == p3X) ;
        check(m3.at(1, 1) == p3Y) ;
        check(m3.at(1, 2) == p2Y) ;
        check(m3.at(2, 0) == p4X) ;
        check(m3.at(2, 1) == p4Y) ;
        check(m3.at(2,2) == p4Z) ;

        // Set a unique value.
        Scalar lifeAndUniverse = 42.f ;
        m3.at(0, 1, lifeAndUniverse) ;
        check(m3.at(0, 0) == p1X) ;
        check(m3.at(0, 1) == lifeAndUniverse) ;
        check(m3.at(0, 2) == p2X) ;
        check(m3.at(1,0) == p3X) ;
        check(m3.at(1, 1) == p3Y) ;
        check(m3.at(1, 2) == p2Y) ;
        check(m3.at(2, 0) == p4X) ;
        check(m3.at(2, 1) == p4Y) ;
        check(m3.at(2,2) == p4Z) ;
    }

    void UTMatrix3x3f::operators() {
        Matrix3x3f m1 ;
        m1.at(0, 0, 1.f) ;
        m1.at(0, 1, 2.f) ;
        m1.at(0, 2, 3.f) ;
        m1.at(1, 0, 4.f) ;
        m1.at(1, 1, 5.f) ;
        m1.at(1, 2, 6.f) ;
        m1.at(2, 0, 7.f) ;
        m1.at(2, 1, 8.f) ;
        m1.at(2, 2, 9.f) ;

        Matrix3x3f m2 ;
        m2.at(0, 0, 5.f) ;
        m2.at(0, 1, 9.f) ;
        m2.at(0, 2, 7.f) ;
        m2.at(1, 0, 1.f) ;
        m2.at(1, 1, 8.f) ;
        m2.at(1, 2, 6.f) ;
        m2.at(2, 0, 3.f) ;
        m2.at(2, 1, 2.f) ;
        m2.at(2, 2, 4.f) ;

        Matrix3x3f m3 = m1 * m2 ;
        check(m3.at(0,0) == 16.f) ;
        check(m3.at(0,1) == 31.f) ;
        check(m3.at(0,2) == 31.f) ;
        check(m3.at(1,0) == 43.f) ;
        check(m3.at(1,1) == 88.f) ;
        check(m3.at(1,2) == 82.f) ;
        check(m3.at(2,0) == 70.f) ;
        check(m3.at(2,1) == 145.f) ;
        check(m3.at(2,2) == 133.f) ;

        Matrix3x3f m4 = m1 + m2 ;
        check(m4.at(0,0) == 6.f) ;
        check(m4.at(0,1) == 11.f) ;
        check(m4.at(0,2) == 10.f) ;
        check(m4.at(1,0) == 5.f) ;
        check(m4.at(1,1) == 13.f) ;
        check(m4.at(1,2) == 12.f) ;
        check(m4.at(2,0) == 10.f) ;
        check(m4.at(2,1) == 10.f) ;
        check(m4.at(2,2) == 13.f) ;
    }
}
