#include <geometry/points/Point2Df.h>
#include <geometry/points/Point2Di.h>
#include <geometry/points/Point3Df.h>
#include <geometry/points/Point3Di.h>
#include <geometry/dimensions/Dimension2Df.h>
#include <geometry/dimensions/Dimension2Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Point2Di p2d1 ;
    cout << "Point #1 = " << p2d1 << endl ;

    Point2Di p2d2(5, 4) ;
    cout << "Point #2 = " << p2d2 << endl ;

    Point2Di p2d3(6, 2) ;
    cout << "Point #3 = " << p2d3 << endl ;
    cout << "Point #3 / 2 = " << (p2d3 / 2) << endl ;

    Point2Di p2d4(-5, 8) ;
    cout << "Point #4 = " << p2d4 << endl ;
    cout << "Point #4 * 5 = " << (p2d4 * 5) << endl ;
    cout << "Point #4 + Point#1 = " << (p2d4 + p2d1) << endl ;
    cout << "Point #4 + Point#2 = " << (p2d4 + p2d2) << endl ;
    cout << "Point #4 - Point#2 = " << (p2d4 - p2d2) << endl ;
    cout << "Point #4 inversed = " << -p2d4 << endl ;

    cout << endl ;

    cout << "p2d2 . p2d3 = " << (p2d2.dot(p2d3)) << endl ;
    cout << "p2d2 .* p2d3 = " << (p2d2 * p2d3) << endl ;

    p2d3.normalize() ;
    cout << "Normalize p2d3 : " << p2d3 << endl ;

    Point2Di p2d5 = Point2Di::merge(p2d2, p2d4) ;
    cout << "Merge p2d2 and p2d4 : " << p2d5 << endl ;

    cout << "Distance between p2d1 and p2d2 = " << Point2Di::distance(p2d1, p2d2) << endl ;
    cout << "Distance X between p2d1 and p2d2 = " << Point2Di::distanceX(p2d1, p2d2) << endl ;
    cout << "Distance Y between p2d1 and p2d2 = " << Point2Di::distanceY(p2d1, p2d2) << endl ;


    Point2Di p2d6(2, 8) ;
    Point2Di p2d7(2, 17) ;
    Point2Di p2d8(14, 17) ;
    cout << "Angle = " << Point2Di::angle(p2d6, p2d7, p2d8) << endl ;
    cout << "Angle orientation = " << Point2Di::angleOrientation(p2d6, p2d7, p2d8) << endl ;

    cout << endl ;

    Point2Di p2d9(p2d6) ;
    cout << "Is " << p2d6 << " equal to " << p2d6 << "? " << (p2d6 == p2d6) << endl ;
    cout << "Is " << p2d6 << " equal to " << p2d7 << "? " << (p2d6 == p2d7) << endl ;
    cout << "Is " << p2d6 << " equal to " << p2d9 << "? " << (p2d6 == p2d9) << endl ;

    cout << "Is " << p2d6 << " different of " << p2d6 << "? " << (p2d6 != p2d6) << endl ;
    cout << "Is " << p2d6 << " different of " << p2d7 << "? " << (p2d6 != p2d7) << endl ;
    cout << "Is " << p2d6 << " different of " << p2d9 << "? " << (p2d6 != p2d9) << endl ;

    cout << endl ;
    cout << "Point #9 original " << p2d9 << endl ;
    p2d9 *= 3 ;
    cout << "Scaled (multiplied) by 3: " << p2d9 << endl ;
    p2d9 += p2d2 ;
    cout << "Added to Point #2: " << p2d9 << endl ;
    p2d9 -= p2d4 ;
    cout << "Substracted to Point #4: " << p2d9 << endl ;
    p2d9 /= 4 ;
    cout << "Divided by 4: " << p2d9 << endl ;

    p2d9.setX(6) ;
    cout << "Set to X = 6 : " << p2d9 << endl ;
    p2d9.setY(12) ;
    cout << "Set to Y = 12 : " << p2d9 << endl ;
    p2d9.set(7, 14) ;
    cout << "Set to (7, 14) : " << p2d9 << endl ;


    cout << endl ;
    cout << (Dimension2Di) p2d1 << endl ;
    cout << (Dimension2Di) p2d4 << endl ;
    cout << (Dimension2Di) p2d9 << endl ;

    cout << (Point3Di) p2d1 << endl ;
    cout << (Point3Di) p2d4 << endl ;
    cout << (Point3Di) p2d9 << endl ;

    return 0 ;
}
