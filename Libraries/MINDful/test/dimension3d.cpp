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
    Dimension3Di dim3d1 ;
    cout << "Dim #1 = " << dim3d1 << endl ;

    Dimension3Di dim3d2(5, 3, 4) ;
    cout << "Dim #2 = " << dim3d2 << endl ;

    Dimension3Di dim3d3(6, 2, -5) ;
    cout << "Dim #3 = " << dim3d3 << endl ;
    cout << "Dim #3 / 2 = " << (dim3d3 / 2) << endl ;

    Dimension3Di dim3d4(-5, 8, -4) ;
    cout << "Dim #4 = " << dim3d4 << endl ;
    cout << "Dim #4 * 5 = " << (dim3d4 * 5) << endl ;
    cout << "Dim #4 + Dim#1 = " << (dim3d4 + dim3d1) << endl ;
    cout << "Dim #4 + Dim#2 = " << (dim3d4 + dim3d2) << endl ;
    cout << "Dim #4 - Dim#2 = " << (dim3d4 - dim3d2) << endl ;

    dim3d4.absolute() ;
    cout << "Absolute Dim #4 = " << dim3d4 << endl ;

    cout << endl ;

    Dimension3Di dim3d5(dim3d4) ;
    cout << "Is " << dim3d5 << " equal to " << dim3d4 << "? " << (dim3d4 == dim3d4) << endl ;
    cout << "Is " << dim3d5 << " equal to " << dim3d3 << "? " << (dim3d4 == dim3d3) << endl ;
    cout << "Is " << dim3d5 << " equal to " << dim3d5 << "? " << (dim3d4 == dim3d5) << endl ;

    cout << "Is " << dim3d5 << " different of " << dim3d4 << "? " << (dim3d4 != dim3d4) << endl ;
    cout << "Is " << dim3d5 << " different of " << dim3d3 << "? " << (dim3d4 != dim3d3) << endl ;
    cout << "Is " << dim3d5 << " different of " << dim3d5 << "? " << (dim3d4 != dim3d5) << endl ;

    cout << endl ;
    cout << "Dim #5 original " << dim3d5 << endl ;
    dim3d5 *= 3 ;
    cout << "Scaled (multiplied) by 3: " << dim3d5 << endl ;
    dim3d5 += dim3d2 ;
    cout << "Added to Dim #2: " << dim3d5 << endl ;
    dim3d5 -= dim3d4 ;
    cout << "Substracted to Dim #4: " << dim3d5 << endl ;
    dim3d5 /= 4 ;
    cout << "Divided by 4: " << dim3d5 << endl ;

    dim3d5.setWidth(6) ;
    cout << "Set to Width = 6 : " << dim3d5 << endl ;
    dim3d5.setHeight(12) ;
    cout << "Set to Height = 12 : " << dim3d5 << endl ;
    dim3d5.set(7, 14, -9) ;
    cout << "Set size to (7, 14, -9) : " << dim3d5 << endl ;


    cout << endl ;
    cout << (Dimension2Di) dim3d1 << endl ;
    cout << (Dimension2Di) dim3d4 << endl ;
    cout << (Dimension2Di) dim3d5 << endl ;

    cout << (Point3Di) dim3d1 << endl ;
    cout << (Point3Di) dim3d4 << endl ;
    cout << (Point3Di) dim3d5 << endl ;

    return 0 ;
}
