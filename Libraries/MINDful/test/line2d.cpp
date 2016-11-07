#include <geometry/lines/Line2Df.h>
#include <geometry/lines/Line2Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Line2Di l2d1 ;
    cout << "Line#1 = " << l2d1 << endl ;
    cout << l2d1.length() << endl ;
    cout << l2d1.lengthSquared() << endl ;
    cout << l2d1.isEmpty() << endl ;

    Line2Di l2d2(Point2Di(5, 4), Point2Di(9, -2)) ;
    cout << "Line#2 = " << l2d2 << endl ;
    cout << l2d2.length() << endl ;
    cout << l2d2.lengthSquared() << endl ;
    cout << l2d2.isEmpty() << endl ;

    Line2Di l2d3(Point2Di(-9, -6), Point2Di(5, 4)) ;
    cout << "Line#3 = " << l2d3 << endl ;
    cout << l2d3.length() << endl ;
    cout << l2d3.isEmpty() << endl ;

    Line2Di l2d4(Point2Di(5, -2), Point2Di(10, 3)) ;
    cout << "Line#4 = " << l2d4 << endl ;
    cout << l2d4.length() << endl ;
    cout << l2d4.isEmpty() << endl ;

    cout << endl ;

    cout << "Are Line#1 and Line#2 contiguous ? " << l2d1.isContiguousTo(l2d2) << endl ;
    cout << "Are Line#3 and Line#2 contiguous ? " << l2d3.isContiguousTo(l2d2) << endl ;

    cout << endl ;

    Point2Di p2d(5, 8) ;
    cout << p2d << endl ;
    cout << "CCW Line#1 = " << (int) Line2Di::CCW(l2d1, p2d) << endl ;
    cout << "CCW Line#2 = " << (int) Line2Di::CCW(l2d2, p2d) << endl ;
    cout << "CCW Line#3 = " << (int) Line2Di::CCW(l2d3, p2d) << endl ;
    cout << "CCW Line#4 = " << (int) Line2Di::CCW(l2d4, p2d) << endl ;

    cout << endl ;
    cout << "Relative Line#2 = " << Line2Di::relative(l2d2) << endl ;
    cout << "Relative Line#4 = " << Line2Di::relative(l2d4) << endl ;

    cout << endl ;

    cout << "Line#2 intersects Line#3 ? = " << l2d2.intersects(l2d3) << endl ;
    cout << "Line#2 intersects Line#4 ? = " << l2d2.intersects(l2d4) << endl ;

    cout << "Distance Line#2 to " << p2d << ": " << l2d2.distanceTo(p2d) << endl ;
    cout << "Distance Line#2 to " << p2d << ": " << l2d2.distanceSquaredTo(p2d) << endl ;
    cout << "Distance Line#2 to (0, 0): " << l2d2.distanceTo(0, 0) << endl ;
    cout << "Distance Line#2 to (0, 0): " << l2d2.distanceSquaredTo(0, 0) << endl ;

    cout << endl ;

    cout << "Start of Line#2 : " << l2d2.getStartPoint() << endl ;
    cout << "End of Line#2 : " << l2d2.getEndPoint() << endl ;
    cout << "Bounds of Line#2 : " << l2d2.getBounds() << endl ;
    cout << "Bounds of Line#1 : " << l2d1.getBounds() << endl ;

    cout << endl ;

    Line2Di l2d5(l2d2) ;
    Line2Di l2d6 = l2d5 ;
    cout << "Line#2 == Line#2 ? " << (l2d2 == l2d2) << endl ;
    cout << "Line#2 == Line#4 ? " << (l2d2 == l2d4) << endl ;
    cout << "Line#2 == Line#5 ? " << (l2d2 == l2d5) << endl ;
    cout << "Line#2 == Line#6 ? " << (l2d2 == l2d6) << endl ;
    cout << "Line#2 != Line#2 ? " << (l2d2 != l2d2) << endl ;
    cout << "Line#2 != Line#4 ? " << (l2d2 != l2d4) << endl ;
    cout << "Line#2 != Line#5 ? " << (l2d2 != l2d5) << endl ;
    cout << "Line#2 != Line#6 ? " << (l2d2 != l2d6) << endl ;

    return 0 ;
}
