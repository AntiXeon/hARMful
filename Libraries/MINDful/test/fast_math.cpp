#include <FastMath.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    const static unsigned int STEPS = 360 ;

    FastMath::init(STEPS) ;
    for (unsigned int step = 0 ; step < STEPS ; step++) {
        cout << "cos(" << step << ") = " << FastMath::cos(step) << endl ;
        cout << "sin(" << step << ") = " << FastMath::sin(step) << endl ;
        cout << "tan(" << step << ") = " << FastMath::tan(step) << endl ;
        cout << endl ;
    }

    cout << endl ;

    cout << "2^3 = " << FastMath::pow(2, 3) << endl ;
    cout << "-5^1 = " << FastMath::pow(-5, 1) << endl ;
    cout << "-2^2 = " << FastMath::pow(-2, 2) << endl ;
    cout << "4^0 = " << FastMath::pow(4, 0) << endl ;
    cout << "4^15 = " << FastMath::pow(4, 15) << endl ;

    cout << endl ;

    cout << "Round of 2.1 = " << FastMath::round(2.1f) << endl ;
    cout << "Round of 2.5 = " << FastMath::round(2.5f) << endl ;
    cout << "Round of 2.99 = " << FastMath::round(2.99f) << endl ;
    cout << "Round of -2.99 = " << FastMath::round(-2.99f) << endl ;
    cout << "Round of -2.5 = " << FastMath::round(-2.5f) << endl ;
    cout << "Round of -2.1 = " << FastMath::round(-2.1f) << endl ;

    cout << endl ;

    cout << "Floor of 2.1 = " << FastMath::floor(2.1f) << endl ;
    cout << "Floor of 2.5 = " << FastMath::floor(2.5f) << endl ;
    cout << "Floor of 2.99 = " << FastMath::floor(2.99f) << endl ;
    cout << "Floor of -2.99 = " << FastMath::floor(-2.99f) << endl ;
    cout << "Floor of -2.5 = " << FastMath::floor(-2.5f) << endl ;
    cout << "Floor of -2.1 = " << FastMath::floor(-2.1f) << endl ;

    cout << endl ;

    cout << "Ceil of 2.1 = " << FastMath::ceil(2.1f) << endl ;
    cout << "Ceil of 2.5 = " << FastMath::ceil(2.5f) << endl ;
    cout << "Ceil of 2.99 = " << FastMath::ceil(2.99f) << endl ;
    cout << "Ceil of -2.99 = " << FastMath::ceil(-2.99f) << endl ;
    cout << "Ceil of -2.5 = " << FastMath::ceil(-2.5f) << endl ;
    cout << "Ceil of -2.1 = " << FastMath::ceil(-2.1f) << endl ;

    return 0 ;
}
