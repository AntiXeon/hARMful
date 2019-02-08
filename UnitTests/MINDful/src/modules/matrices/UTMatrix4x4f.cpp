#include <modules/matrices/UTMatrix4x4f.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    void UTMatrix4x4f::allocation() {
        // Default constructor.
        Matrix4x4f m1 ;
        check(m1.at(0, 0) == 0.f) ;
        check(m1.at(1, 0) == 0.f) ;
        check(m1.at(3, 1) == 0.f) ;
        check(m1.at(2,1) == 0.f) ;
        check(m1.size() == 4) ;

        // Initial value.
        const Scalar m2DefaultValue = 5.24f ;
        Matrix4x4f m2(m2DefaultValue) ;
        check(m2.at(0, 0) == m2DefaultValue) ;
        check(m2.at(1, 0) == m2DefaultValue) ;
        check(m2.at(1, 3) == m2DefaultValue) ;
        check(m2.at(2,1) == m2DefaultValue) ;

        // Copy constructor.
        Matrix4x4f m3(m2) ;
        check(m2.at(0, 0) == m2DefaultValue) ;
        check(m2.at(1, 0) == m2DefaultValue) ;
        check(m2.at(3, 2) == m2DefaultValue) ;
        check(m2.at(2,1) == m2DefaultValue) ;
    }

    void UTMatrix4x4f::utilities() {
        // Identity and clear.
        Matrix4x4f m1 ;
        m1.identity() ;
        check(m1.at(0, 0) == 1.f) ;
        check(m1.at(0, 1) == 0.f) ;
        check(m1.at(0, 2) == 0.f) ;
        check(m1.at(0, 3) == 0.f) ;
        check(m1.at(1,0) == 0.f) ;
        check(m1.at(1, 1) == 1.f) ;
        check(m1.at(1, 2) == 0.f) ;
        check(m1.at(1, 3) == 0.f) ;
        check(m1.at(2, 0) == 0.f) ;
        check(m1.at(2, 1) == 0.f) ;
        check(m1.at(2,2) == 1.f) ;
        check(m1.at(2,3) == 0.f) ;
        check(m1.at(3, 0) == 0.f) ;
        check(m1.at(3, 1) == 0.f) ;
        check(m1.at(3, 2) == 0.f) ;
        check(m1.at(3,3) == 1.f) ;
        m1.clear() ;
        check(m1.at(0, 0) == 0.f) ;
        check(m1.at(0, 1) == 0.f) ;
        check(m1.at(0, 2) == 0.f) ;
        check(m1.at(0, 3) == 0.f) ;
        check(m1.at(1,0) == 0.f) ;
        check(m1.at(1, 1) == 0.f) ;
        check(m1.at(1, 2) == 0.f) ;
        check(m1.at(1, 3) == 0.f) ;
        check(m1.at(2, 0) == 0.f) ;
        check(m1.at(2, 1) == 0.f) ;
        check(m1.at(2,2) == 0.f) ;
        check(m1.at(2,3) == 0.f) ;
        check(m1.at(3, 0) == 0.f) ;
        check(m1.at(3, 1) == 0.f) ;
        check(m1.at(3, 2) == 0.f) ;
        check(m1.at(3,3) == 0.f) ;

        // Set values from points.
        Matrix4x4f m2 ;
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
        check(m2.at(0, 3) == 0.f) ;
        check(m2.at(1,0) == p1Y) ;
        check(m2.at(1, 1) == 1.f) ;
        check(m2.at(1, 2) == p2Y) ;
        check(m2.at(1, 3) == 0.f) ;
        check(m2.at(2, 0) == 0.f) ;
        check(m2.at(2, 1) == 0.f) ;
        check(m2.at(2,2) == p2Z) ;
        check(m2.at(2, 3) == 0.f) ;
        check(m2.at(3, 0) == 0.f) ;
        check(m2.at(3, 1) == 0.f) ;
        check(m2.at(3, 2) == 0.f) ;
        check(m2.at(3, 3) == 1.f) ;

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
        check(m2.at(0, 3) == 0.f) ;
        check(m2.at(1,0) == p3X) ;
        check(m2.at(1, 1) == p3Y) ;
        check(m2.at(1, 2) == p2Y) ;
        check(m2.at(1, 3) == 0.f) ;
        check(m2.at(2, 0) == p4X) ;
        check(m2.at(2, 1) == p4Y) ;
        check(m2.at(2,2) == p4Z) ;
        check(m2.at(2, 3) == 0.f) ;
        check(m2.at(3, 0) == 0.f) ;
        check(m2.at(3, 1) == 0.f) ;
        check(m2.at(3, 2) == 0.f) ;
        check(m2.at(3, 3) == 1.f) ;

        // Copy matrix.
        Matrix4x4f m3 ;
        m3.identity() ;
        m3 = m2 ;

        check(m2.at(0, 0) == p1X) ;
        check(m2.at(0, 1) == 0.f) ;
        check(m2.at(0, 2) == p2X) ;
        check(m2.at(0, 3) == 0.f) ;
        check(m2.at(1,0) == p3X) ;
        check(m2.at(1, 1) == p3Y) ;
        check(m2.at(1, 2) == p2Y) ;
        check(m2.at(1, 3) == 0.f) ;
        check(m2.at(2, 0) == p4X) ;
        check(m2.at(2, 1) == p4Y) ;
        check(m2.at(2,2) == p4Z) ;
        check(m2.at(2, 3) == 0.f) ;
        check(m2.at(3, 0) == 0.f) ;
        check(m2.at(3, 1) == 0.f) ;
        check(m2.at(3, 2) == 0.f) ;
        check(m2.at(3, 3) == 1.f) ;

        // Set a unique value.
        Scalar lifeAndUniverse = 42.f ;
        m3.at(0, 1, lifeAndUniverse) ;
        check(m3.at(0, 0) == p1X) ;
        check(m3.at(0, 1) == lifeAndUniverse) ;
        check(m3.at(0, 2) == p2X) ;
        check(m3.at(0, 3) == 0.f) ;
        check(m3.at(1,0) == p3X) ;
        check(m3.at(1, 1) == p3Y) ;
        check(m3.at(1, 2) == p2Y) ;
        check(m3.at(1, 3) == 0.f) ;
        check(m3.at(2, 0) == p4X) ;
        check(m3.at(2, 1) == p4Y) ;
        check(m3.at(2,2) == p4Z) ;
        check(m3.at(2, 3) == 0.f) ;
        check(m3.at(3, 0) == 0.f) ;
        check(m3.at(3, 1) == 0.f) ;
        check(m3.at(3, 2) == 0.f) ;
        check(m3.at(3, 3) == 1.f) ;

        // Trace.
        Scalar expectedTrace = 8.457f ;
        check(compare(m3.trace(), expectedTrace)) ;

        // Decomposition.
        Matrix4x4f m4 ;
        Point3Df translationM4 ;
        Quaternion rotationM4 ;
        Point3Df scaleM4 ;
        m4.setRowValues(0, Point4Df(1.41421f, -1.41421f, 0.f, -0.123258f)) ;
        m4.setRowValues(1, Point4Df(1.41421f,  1.41421f, 0.f,  0.730693f)) ;
        m4.setRowValues(2, Point4Df(0.f,       0.f,      2.f,  1.03899e-08f)) ;
        m4.setRowValues(3, Point4Df(0.f,       0.f,      0.f,  1.f)) ;
        m4.decompose(translationM4, rotationM4, scaleM4) ;
        check(compare(translationM4[Point3Df::X], -0.123258f)) ;
        check(compare(translationM4[Point3Df::Y],  0.730693f)) ;
        check(compare(translationM4[Point3Df::Z],  1.03899e-08f)) ;
        check(compare(rotationM4[Quaternion::X], 0.f)) ;
        check(compare(rotationM4[Quaternion::Y], 0.f)) ;
        check(compare(rotationM4[Quaternion::Z], 0.382683f)) ;
        check(compare(rotationM4[Quaternion::W], 0.92388f)) ;
        check(compare(scaleM4[Point3Df::X], 2.f, 1e-5f)) ;
        check(compare(scaleM4[Point3Df::Y], 2.f, 1e-5f)) ;
        check(compare(scaleM4[Point3Df::Z], 2.f, 1e-5f)) ;

        // Composition.
        Matrix4x4f m5 ;
        m5.compose(translationM4, rotationM4, scaleM4) ;
        check(compare(m5.at(0, 0), m4.at(0, 0))) ;
        check(compare(m5.at(0, 1), m4.at(0, 1))) ;
        check(compare(m5.at(0, 2), m4.at(0, 2))) ;
        check(compare(m5.at(0, 3), m4.at(0, 3))) ;
        check(compare(m5.at(1, 0), m4.at(1, 0))) ;
        check(compare(m5.at(1, 1), m4.at(1, 1))) ;
        check(compare(m5.at(1, 2), m4.at(1, 2))) ;
        check(compare(m5.at(1, 3), m4.at(1, 3))) ;
        check(compare(m5.at(2, 0), m4.at(2, 0))) ;
        check(compare(m5.at(2, 1), m4.at(2, 1))) ;
        check(compare(m5.at(2, 2), m4.at(2, 2))) ;
        check(compare(m5.at(2, 3), m4.at(2, 3))) ;
        check(compare(m5.at(3, 0), m4.at(3, 0))) ;
        check(compare(m5.at(3, 1), m4.at(3, 1))) ;
        check(compare(m5.at(3, 2), m4.at(3, 2))) ;
        check(compare(m5.at(3, 3), m4.at(3, 3))) ;

        // Inverse.
        Matrix4x4f m6 ;
        Matrix4x4f m7 ;
        m7.setRowValues(0, Point4Df( 0.f, 0.f, 1.f, 5.f)) ;
        m7.setRowValues(1, Point4Df( 0.f, 3.f, 0.f, 3.f)) ;
        m7.setRowValues(2, Point4Df(-1.f, 0.f, 0.f, 2.f)) ;
        m7.setRowValues(3, Point4Df( 0.f, 0.f, 0.f, 1.f)) ;

        m7.inverse(m6) ;
        check(compare(m6.at(0, 0),  0.f)) ;
        check(compare(m6.at(0, 1),  0.f)) ;
        check(compare(m6.at(0, 2), -1.f)) ;
        check(compare(m6.at(0, 3),  2.f)) ;
        check(compare(m6.at(1, 0),  0.f)) ;
        check(compare(m6.at(1, 1),  1.f/3.f)) ;
        check(compare(m6.at(1, 2),  0.f)) ;
        check(compare(m6.at(1, 3), -1.f)) ;
        check(compare(m6.at(2, 0),  1.f)) ;
        check(compare(m6.at(2, 1),  0.f)) ;
        check(compare(m6.at(2, 2),  0.f)) ;
        check(compare(m6.at(2, 3), -5.f)) ;
        check(compare(m6.at(3, 0),  0.f)) ;
        check(compare(m6.at(3, 1),  0.f)) ;
        check(compare(m6.at(3, 2),  0.f)) ;
        check(compare(m6.at(3, 3),  1.f)) ;

        std::cout << m7 << std::endl ;
        std::cout << m6 << std::endl ;
    }

    void UTMatrix4x4f::operators() {
        Matrix4x4f m1 ;
        m1.at(0, 0, 1.f) ;
        m1.at(0, 1, 2.f) ;
        m1.at(0, 2, 3.f) ;
        m1.at(0, 3, 10.f) ;
        m1.at(1, 0, 4.f) ;
        m1.at(1, 1, 5.f) ;
        m1.at(1, 2, 6.f) ;
        m1.at(1, 3, 11.f) ;
        m1.at(2, 0, 7.f) ;
        m1.at(2, 1, 8.f) ;
        m1.at(2, 2, 9.f) ;
        m1.at(2, 3, 12.f) ;
        m1.at(3, 0, 20.f) ;
        m1.at(3, 1, 21.f) ;
        m1.at(3, 2, 22.f) ;
        m1.at(3, 3, 23.f) ;

        Matrix4x4f m2 ;
        m2.at(0, 0, 5.f) ;
        m2.at(0, 1, 9.f) ;
        m2.at(0, 2, 7.f) ;
        m2.at(0, 3, 20.f) ;
        m2.at(1, 0, 1.f) ;
        m2.at(1, 1, 8.f) ;
        m2.at(1, 2, 6.f) ;
        m2.at(1, 3, 12.f) ;
        m2.at(2, 0, 3.f) ;
        m2.at(2, 1, 2.f) ;
        m2.at(2, 2, 4.f) ;
        m2.at(2, 3, 10.f) ;
        m2.at(3, 0, 21.f) ;
        m2.at(3, 1, 11.f) ;
        m2.at(3, 2, 23.f) ;
        m2.at(3, 3, 22.f) ;

        Matrix4x4f m3 = m1 * m2 ;
        check(m3.at(0,0) == 226.f) ;
        check(m3.at(0,1) == 141.f) ;
        check(m3.at(0,2) == 261.f) ;
        check(m3.at(0,3) == 294.f) ;
        check(m3.at(1,0) == 274.f) ;
        check(m3.at(1,1) == 209.f) ;
        check(m3.at(1,2) == 335.f) ;
        check(m3.at(1,3) == 442.f) ;
        check(m3.at(2,0) == 322.f) ;
        check(m3.at(2,1) == 277.f) ;
        check(m3.at(2,2) == 409.f) ;
        check(m3.at(2,3) == 590.f) ;
        check(m3.at(3,0) == 670.f) ;
        check(m3.at(3,1) == 645.f) ;
        check(m3.at(3,2) == 883.f) ;
        check(m3.at(3,3) == 1378.f) ;

        Matrix4x4f m4 = m1 + m2 ;
        check(m4.at(0,0) == 6.f) ;
        check(m4.at(0,1) == 11.f) ;
        check(m4.at(0,2) == 10.f) ;
        check(m4.at(0,3) == 30.f) ;
        check(m4.at(1,0) == 5.f) ;
        check(m4.at(1,1) == 13.f) ;
        check(m4.at(1,2) == 12.f) ;
        check(m4.at(1,3) == 23.f) ;
        check(m4.at(2,0) == 10.f) ;
        check(m4.at(2,1) == 10.f) ;
        check(m4.at(2,2) == 13.f) ;
        check(m4.at(2,3) == 22.f) ;
        check(m4.at(3,0) == 41.f) ;
        check(m4.at(3,1) == 32.f) ;
        check(m4.at(3,2) == 45.f) ;
        check(m4.at(3,3) == 45.f) ;


        Matrix4x4f m5 = m2 + m1;
        check(m5.at(0,0) == 6.f) ;
        check(m5.at(0,1) == 11.f) ;
        check(m5.at(0,2) == 10.f) ;
        check(m5.at(0,3) == 30.f) ;
        check(m5.at(1,0) == 5.f) ;
        check(m5.at(1,1) == 13.f) ;
        check(m5.at(1,2) == 12.f) ;
        check(m5.at(1,3) == 23.f) ;
        check(m5.at(2,0) == 10.f) ;
        check(m5.at(2,1) == 10.f) ;
        check(m5.at(2,2) == 13.f) ;
        check(m5.at(2,3) == 22.f) ;
        check(m5.at(3,0) == 41.f) ;
        check(m5.at(3,1) == 32.f) ;
        check(m5.at(3,2) == 45.f) ;
        check(m5.at(3,3) == 45.f) ;
        check(m4 == m5);
        check(m4 != m3);
    }
}
