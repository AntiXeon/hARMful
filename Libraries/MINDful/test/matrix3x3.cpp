#include <matrices/Matrix3x3f.h>
#include <geometry/points/Point2Df.h>
#include <geometry/points/Point2Di.h>
#include <geometry/points/Point3Df.h>
#include <geometry/points/Point3Di.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Matrix3x3f mat(2.f) ;

    cout << "Initial full of zeros" << endl ;
    cout << mat << endl ;
    cout << endl ;


    mat.identity() ;
    cout << "Identity matrix" << endl ;
    cout << mat << endl ;
    cout << endl ;


    mat.at(0, 1, 3.f) ;
    mat.at(2, 1, 5.f) ;
    mat.at(2, 0, 7.f) ;
    mat.at(1, 1, 9.f) ;
    mat.at(1, 0, 11.f) ;
    mat.at(1, 2, 13.f) ;
    mat[0][2] = 17.f ;
    cout << "Custom matrix" << endl ;
    cout << mat << endl ;
    cout << endl ;

    cout << "[0,0] = " << mat.at(0,0) << endl ;
    cout << "[1,0] = " << mat[1][0] << endl ;
    cout << "[0,2] = " << mat.at(0,2) << endl ;
    cout << "[1,2] = " << mat.at(1,2) << endl ;
    cout << "[2,2] = " << mat[2][2] << endl ;
    cout << endl ;

    mat.clear() ;
    cout << "Cleared matrix" << endl ;
    cout << mat << endl ;
    cout << endl ;

    cout << "-------- MULTIPLY --------" << endl << endl ;

    Matrix3x3f matA ;
    matA[0][0] = 1.f ; matA[1][0] = 2.f ; matA[2][0] = 3.f ;
    matA[0][1] = 4.f ; matA[1][1] = 5.f ; matA[2][1] = 6.f ;
    matA[0][2] = 7.f ; matA[1][2] = 8.f ; matA[2][2] = 9.f ;
    cout << "Matrix A = " << matA << endl ;

    Matrix3x3f matB ;
    matB[0][0] = 9.f ; matB[1][0] = 8.f ; matB[2][0] = 7.f ;
    matB[0][1] = 6.f ; matB[1][1] = 5.f ; matB[2][1] = 4.f ;
    matB[0][2] = 3.f ; matB[1][2] = 2.f ; matB[2][2] = 1.f ;
    cout << "Matrix B = " << matB << endl ;

    matA.multiply(matB) ;
    cout << "A x B = " << matA << endl ;


    cout << "Set columns :" << endl ;
    cout << endl ;

    Matrix3x3f matC ;
    Point2Df p1(3.f, 9.f) ;
    Point3Df p2(6.f, 7.f, 8.f) ;
    matC.setColumnValues(1, p1) ;
    cout << "Set " << p1 << " at column " << 1 << ": " << matC << endl ;
    matC.setRowValues(2, p2) ;
    cout << "Set " << p1 << " at row " << 2 << ": " << matC << endl ;

    return 0 ;
}
