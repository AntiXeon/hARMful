#include <geometry/dimensions/Dimension2Df.h>
#include <geometry/dimensions/Dimension2Di.h>
#include <geometry/dimensions/Dimension3Df.h>
#include <geometry/dimensions/Dimension3Di.h>
#include <geometry/points/Point2Df.h>
#include <geometry/points/Point2Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Dimension2Df dim2d1 ;
    cout << "Dim #1 = " << dim2d1 << endl ;

    Dimension2Df dim2d2(5.2f, 3.9f) ;
    cout << "Dim #2 = " << dim2d2 << endl ;

    Dimension2Df dim2d3(6.f, 2.4f) ;
    cout << "Dim #3 = " << dim2d3 << endl ;
    cout << "Dim #3 / 2 = " << (dim2d3 / 2.f) << endl ;

    Dimension2Df dim2d4(-5.f, 8.f) ;
    cout << "Dim #4 = " << dim2d4 << endl ;
    cout << "Dim #4 * 5 = " << (dim2d4 * 5.f) << endl ;
    cout << "Dim #4 + Dim#1 = " << (dim2d4 + dim2d1) << endl ;
    cout << "Dim #4 + Dim#2 = " << (dim2d4 + dim2d2) << endl ;
    cout << "Dim #4 - Dim#2 = " << (dim2d4 - dim2d2) << endl ;

    cout << endl ;

    Dimension2Df dim2d5(dim2d4) ;
    cout << "Is " << dim2d5 << " equal to " << dim2d4 << "? " << (dim2d4 == dim2d4) << endl ;
    cout << "Is " << dim2d5 << " equal to " << dim2d3 << "? " << (dim2d4 == dim2d3) << endl ;
    cout << "Is " << dim2d5 << " equal to " << dim2d5 << "? " << (dim2d4 == dim2d5) << endl ;

    cout << "Is " << dim2d5 << " different of " << dim2d4 << "? " << (dim2d4 != dim2d4) << endl ;
    cout << "Is " << dim2d5 << " different of " << dim2d3 << "? " << (dim2d4 != dim2d3) << endl ;
    cout << "Is " << dim2d5 << " different of " << dim2d5 << "? " << (dim2d4 != dim2d5) << endl ;

    cout << endl ;
    cout << "Dim #5 original " << dim2d5 << endl ;
    dim2d5 *= 3 ;
    cout << "Scaled (multiplied) by 3: " << dim2d5 << endl ;
    dim2d5 += dim2d2 ;
    cout << "Added to Dim #2: " << dim2d5 << endl ;
    dim2d5 -= dim2d4 ;
    cout << "Substracted to Dim #4: " << dim2d5 << endl ;
    dim2d5 /= 4 ;
    cout << "Divided by 4: " << dim2d5 << endl ;

    dim2d5.setWidth(6) ;
    cout << "Set to Width = 6 : " << dim2d5 << endl ;
    dim2d5.setHeight(12) ;
    cout << "Set to Height = 12 : " << dim2d5 << endl ;
    dim2d5.set(7, 14) ;
    cout << "Set size to (7, 14) : " << dim2d5 << endl ;


    cout << endl ;
    cout << (Dimension3Df) dim2d1 << endl ;
    cout << (Dimension3Df) dim2d4 << endl ;
    cout << (Dimension3Df) dim2d5 << endl ;

    cout << (Point2Df) dim2d1 << endl ;
    cout << (Point2Df) dim2d4 << endl ;
    cout << (Point2Df) dim2d5 << endl ;

    return 0 ;
}
