#include <matrices/Matrix2D.h>
#include <iostream>

using namespace std ;
using namespace Mind ;


int main() {
    Matrix2D<short> mat(5, 5) ;
    cout << "Initial matrix (0 filled):" << endl ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;

    cout << endl ;

    cout << "Add 2 columns of 8" << endl ;
    mat.resize(5+2, 5, 8) ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;

    cout << endl ;

    cout << "Add 4 rows of 5" << endl ;
    mat.resize(7, 5+4, 5) ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;

    cout << endl ;

    cout << "Set mat[1][3] = 7" << endl ;
    mat[1][3] = 7 ;
    cout << "Set mat[3][1] = 1" << endl ;
    mat.at(3, 1) = 1 ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;

    cout << endl ;

    cout << "Set mat back to its initial size:" << endl ;
    mat.resize(5, 5) ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;
    cout << "mat[1][3] = " << mat[1][3] << endl ;
    cout << "mat[3][1] = " << mat[3][1] << endl ;

    cout << endl ;

    cout << "Reset matrix..." << endl ;
    mat.clear() ;
    cout << mat << endl ;
    cout << "mat size: " << mat.rows() << "x" << mat.cols() << endl ;

    return 0 ;
}
