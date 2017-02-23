#include <modules/matrices/UTMatrix2D.hpp>
#include <matrices/Matrix2D.hpp>
#include <string>
#include <iostream>

using namespace Mind ;

namespace UTMind {
    UTMatrix2D::UTMatrix2D() {}

    UTMatrix2D::~UTMatrix2D() {}

    void UTMatrix2D::allocation() {
        // Matrices of integers.
        {
            Matrix2D<int> m1 ;
            check(m1[0][0] == 0) ;

            const int m2Default = 5 ;
            Matrix2D<int> m2(1, 1, m2Default) ;
            check(m2[0][0] == m2Default) ;

            const int m3Width = 2 ;
            const int m3Height = 4 ;
            const int m3Default = -7 ;
            Matrix2D<int> m3(m3Width, m3Height, m3Default) ;
            check(m3[0][0] == m3Default) ;
            check(m3[1][1] == m3Default) ;
            check(m3[0][3] == m3Default) ;
            check(m3[0][0] == m3.at(0, 0)) ;
            check(m3[1][1] == m3.at(1, 1)) ;
            check(m3[0][3] == m3.at(0, 3)) ;
            check(m3.cols() == m3Width) ;
            check(m3.rows() == m3Height) ;
        }

        // Matrices of floats.
        {
            Matrix2D<float> m1 ;
            check(m1[0][0] == 0.f) ;

            const float m2Default = -9.98f ;
            Matrix2D<float> m2(1, 1, m2Default) ;
            check(compare(m2[0][0], m2Default)) ;


            const int m3Width = 2915 ;
            const int m3Height = 18 ;
            const float m3Default = 17858887.97f ;
            Matrix2D<float> m3(m3Width, m3Height, m3Default) ;
            check(m3[2574][14] == m3Default) ;
            check(m3[174][2] == m3Default) ;
            check(m3[6][0] == m3Default) ;
            check(m3[2574][14] == m3.at(2574, 14)) ;
            check(m3[174][2] == m3.at(174, 2)) ;
            check(m3[6][0] == m3.at(6, 0)) ;
            check(m3.cols() == m3Width) ;
            check(m3.rows() == m3Height) ;
        }

        // Matrices of double.
        {
            Matrix2D<double> m1 ;
            check(m1[0][0] == 0.) ;

            const double m2Default = 18.35 ;
            Matrix2D<double> m2(1, 1, m2Default) ;
            check(compare(m2[0][0], m2Default)) ;

            const int m3Width = 7751 ;
            const int m3Height = 9927 ;
            const double m3Default = 0.5e-11 ;
            Matrix2D<double> m3(m3Width, m3Height, m3Default) ;
            check(m3[5711][7] == m3Default) ;
            check(m3[0][9298] == m3Default) ;
            check(m3[1841][551] == m3Default) ;
            check(m3[5711][7] == m3.at(5711, 7)) ;
            check(m3[0][9298] == m3.at(0, 9298)) ;
            check(m3[1841][551] == m3.at(1841, 551)) ;
            check(m3.cols() == m3Width) ;
            check(m3.rows() == m3Height) ;
        }
    }

    void UTMatrix2D::utilities() {
        size_t width = 5 ;
        size_t height = 2 ;
        const int InitialValue = 123 ;
        Matrix2D<int> mat(width, height, InitialValue) ;
        mat.reserve(24, 32) ;
        check(mat.cols() == width) ;
        check(mat.rows() == height) ;

        // Increase matrix size.
        width = 9 ;
        height = 8 ;
        const int ResizeValue = 456 ;
        mat.resize(width, height, ResizeValue) ;
        check(mat.at(2, 1) == InitialValue) ;
        check(mat[4][1] == InitialValue) ;
        check(mat.at(4, 5) == ResizeValue) ;
        check(mat[6][6] == ResizeValue) ;
        check(mat.cols() == width) ;
        check(mat.rows() == height) ;

        // Decrease matrix size.
        width = 3 ;
        height = 2 ;
        const int NotUsedValue = 789 ;
        mat.resize(width, height, NotUsedValue) ;
        check(mat.at(1, 1) == InitialValue) ;
        check(mat[0][1] == InitialValue) ;
        check(mat.cols() == width) ;
        check(mat.rows() == height) ;

        mat.clear() ;
        check(mat.cols() == 0) ;
        check(mat.rows() == 0) ;
    }
}
