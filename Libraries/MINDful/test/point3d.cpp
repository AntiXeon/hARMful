#include <geometry/points/Point2Df.h>
#include <geometry/points/Point2Di.h>
#include <geometry/points/Point3Df.h>
#include <geometry/points/Point3Di.h>
#include <geometry/dimensions/Dimension3Df.h>
#include <geometry/dimensions/Dimension3Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Point3Df p3d1 ;
    cout << "Point #1 = " << p3d1 << endl ;

    Point3Df p3d2(5.45f, 4.123f, -2.82f) ;
    cout << "Point #2 = " << p3d2 << endl ;

    Point3Df p3d3(6.3f, 2.96f, 5.45f) ;
    cout << "Point #3 = " << p3d3 << endl ;
    cout << "Point #3 / 2 = " << (p3d3 / 2.f) << endl ;

    Point3Df p3d4(-5.01f, 8.5601f, 4.097f) ;
    cout << "Point #4 = " << p3d4 << endl ;
    cout << "Point #4 * 5 = " << (p3d4 * 5.f) << endl ;
    cout << "Point #4 + Point#1 = " << (p3d4 + p3d1) << endl ;
    cout << "Point #4 + Point#2 = " << (p3d4 + p3d2) << endl ;
    cout << "Point #4 - Point#2 = " << (p3d4 - p3d2) << endl ;
    cout << "Point #4 inversed = " << -p3d4 << endl ;

    cout << endl ;

    cout << "p3d2 . p3d3 = " << (p3d2.dot(p3d3)) << endl ;
    cout << "p3d2 .* p3d3 = " << (p3d2 * p3d3) << endl ;

    p3d3.normalize() ;
    cout << "Normalize p3d3 : " << p3d3 << endl ;

    Point3Df p3d5 = Point3Df::merge(p3d2, p3d4) ;
    cout << "Merge p3d2 and p3d4 : " << p3d5 << endl ;

    cout << "Distance between p3d1 and p3d2 = " << Point3Df::distance(p3d1, p3d2) << endl ;
    cout << "Distance X between p3d1 and p3d2 = " << Point3Df::distanceX(p3d1, p3d2) << endl ;
    cout << "Distance Y between p3d1 and p3d2 = " << Point3Df::distanceY(p3d1, p3d2) << endl ;

    cout << endl ;

    Point3Df p3d9(p3d4) ;
    cout << "Is " << p3d4 << " equal to " << p3d4 << "? " << (p3d4 == p3d4) << endl ;
    cout << "Is " << p3d4 << " equal to " << p3d3 << "? " << (p3d4 == p3d3) << endl ;
    cout << "Is " << p3d4 << " equal to " << p3d9 << "? " << (p3d4 == p3d9) << endl ;

    cout << "Is " << p3d4 << " different of " << p3d4 << "? " << (p3d4 != p3d4) << endl ;
    cout << "Is " << p3d4 << " different of " << p3d3 << "? " << (p3d4 != p3d3) << endl ;
    cout << "Is " << p3d4 << " different of " << p3d9 << "? " << (p3d4 != p3d9) << endl ;

    cout << endl ;
    cout << "Point #9 original " << p3d9 << endl ;
    p3d9 *= 3.f ;
    cout << "Scaled (multiplied) by 3: " << p3d9 << endl ;
    p3d9 += p3d2 ;
    cout << "Added to Point #2: " << p3d9 << endl ;
    p3d9 -= p3d4 ;
    cout << "Substracted to Point #4: " << p3d9 << endl ;
    p3d9 /= 4.f ;
    cout << "Divided by 4: " << p3d9 << endl ;

    p3d9.setX(6.f) ;
    cout << "Set to X = 6 : " << p3d9 << endl ;
    p3d9.setY(12.f) ;
    cout << "Set to Y = 12 : " << p3d9 << endl ;
    p3d9.setZ(8.f) ;
    cout << "Set to Z = 8 : " << p3d9 << endl ;
    p3d9.set(7.f, 14.f, 2.f) ;
    cout << "Set to (7, 14, 2) : " << p3d9 << endl ;


    cout << endl ;
    cout << (Dimension3Df) p3d1 << endl ;
    cout << (Dimension3Df) p3d4 << endl ;
    cout << (Dimension3Df) p3d9 << endl ;

    cout << (Point2Df) p3d1 << endl ;
    cout << (Point2Df) p3d4 << endl ;
    cout << (Point2Df) p3d9 << endl ;

    return 0 ;
}
