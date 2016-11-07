#include <geometry/rectangles/Rectangle2Df.h>
#include <geometry/rectangles/Rectangle2Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Rectangle2Df r2d1 ;
    cout << r2d1 << endl ;
    r2d1.translate(5.f, 4.f) ;
    cout << "Translation of (5,4): " << r2d1 << endl ;
    cout << "Is empty ? " << r2d1.isEmpty() << endl ;
    Point2Df p2d(2.f, 6.f) ;
    r2d1 += p2d ;
    cout << "Added " << p2d << " : " << r2d1 << endl ;
    cout << "Is empty ? " << r2d1.isEmpty() << endl ;
    r2d1 += p2d ;
    cout << "Added " << p2d << " : " << r2d1 << endl ;
    cout << "Is empty ? " << r2d1.isEmpty() << endl ;

    cout << endl ;

    Point2Df p2d2(4.f, 5.f) ;
    cout << "Contains " << p2d2 << " ? " << r2d1.contains(p2d2) << endl ;
    Point2Df p2d3(4.f, 9.f) ;
    cout << "Contains " << p2d3 << " ? " << r2d1.contains(p2d3) << endl ;
    cout << "Contains " << p2d << " ? " << r2d1.contains(p2d) << endl ;

    cout << endl ;

    r2d1 = Rectangle2Df(1.f, 1.f, 10.f, 15.f) ;
    cout << "New Rectangle #1 = " << r2d1 << endl ;

    Rectangle2Df r2d2(3.f, 4.f, 1.f, 1.f, false) ;
    cout << "R2D2 = " << r2d2 << endl ;
    cout << "Contains " << r2d2.getBottomRightCorner() << " ? " << r2d1.contains(r2d2.getBottomRightCorner()) << endl ;
    cout << "Contains " << r2d2.getUpperLeftCorner() << " ? " << r2d1.contains(r2d2.getUpperLeftCorner()) << endl ;
    cout << "Contains " << r2d2 << " ? " << r2d1.contains(r2d2) << endl ;
    Rectangle2Df r2d3(9.f, 5.f, 1.f, 1.f, false) ;
    cout << "Contains " << r2d3 << " ? " << r2d1.contains(r2d3) << endl ;
    cout << "Contains " << r2d1 << " ? " << r2d1.contains(r2d1) << endl ;
    Rectangle2Df r2d4(18.f, 5.f, 4.f, 12.f, false) ;
    cout << "Contains " << r2d4 << " ? " << r2d1.contains(r2d4) << endl ;
    Rectangle2Df r2d5(r2d4) ;
    cout << "Contains " << r2d5 << " ? " << r2d1.contains(r2d5) << endl ;

    cout << endl ;

    Rectangle2Df r2d10(8.f, 12.f, 13.f, 19.f) ;
    cout << "Intersects " << r2d5 << " ? " << r2d1.intersects(r2d5) << endl ;
    cout << "Intersects " << r2d3 << " ? " << r2d1.intersects(r2d3) << endl ;
    cout << "Intersects " << r2d1 << " ? " << r2d1.intersects(r2d1) << endl ;
    cout << "Intersects " << r2d10 << " ? " << r2d1.intersects(r2d10) << endl ;
    Rectangle2Df r2d7(90.f, 120.f, 4.f, 12.f, false) ;
    cout << "Intersects " << r2d7 << " ? " << r2d1.intersects(r2d7) << endl ;

    cout << endl ;

    Rectangle2Df r2d8(18.f, 5.f, 4.f, 4.f, false) ;
    Rectangle2Df r2d9(16.5f, 5.f, 4.f, 12.f, false) ;
    cout << r2d4 << " == " << r2d4 << " ? " << (r2d4 == r2d4) << endl ;
    cout << r2d4 << " == " << r2d5 << " ? " << (r2d4 == r2d5) << endl ;
    cout << r2d4 << " == " << r2d1 << " ? " << (r2d4 == r2d1) << endl ;
    cout << r2d4 << " == " << r2d8 << " ? " << (r2d4 == r2d8) << endl ;
    cout << r2d4 << " == " << r2d9 << " ? " << (r2d4 == r2d9) << endl ;

    cout << endl ;

    r2d9 = r2d1 + r2d4 ;
    cout << r2d1 << " contains " << r2d4 << " ? " << r2d1.contains(r2d4) << endl ;
    cout << r2d4 << " contains " << r2d1 << " ? " << r2d4.contains(r2d1) << endl ;
    cout << r2d1 << " + " << r2d4 << " = " << r2d9 << endl ;

    cout << endl ;

    Rectangle2Di r2d6(Point2Di(4, 6), Dimension2Di(8, 8), true) ;
    cout << "Centered rectangle : " << r2d6 << endl ;
    r2d6.translate(10, -10) ;
    cout << "Moved of (10, 10) : " << r2d6 << endl ;

    Point2Di p2d4 ;
    cout << "Position of " << p2d4 << " = " << (int) r2d6.position(p2d4) << endl ;
    cout << "Position of (50, 0) = " << (int) r2d6.position(50, 0) << endl ;
    cout << "Position of (15, 50) = " << (int) r2d6.position(15, 50) << endl ;
    cout << "Position of (15, -50) = " << (int) r2d6.position(15, -50) << endl ;
    cout << "Position of (5, -50) = " << (int) r2d6.position(5, -50) << endl ;
    cout << "Position of (12, -6) = " << (int) r2d6.position(12, -6) << endl ;


    return 0 ;
}
