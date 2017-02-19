#include <matrices/Matrix3x3f.hpp>

namespace Mind {
    Matrix3x3f::Matrix3x3f(const Scalar& value) : SquareMatrixf(3, value) {}

    Matrix3x3f::Matrix3x3f(const SquareMatrixf& copied) : SquareMatrixf(copied) {}

    Matrix3x3f::~Matrix3x3f() {}

    void Matrix3x3f::multiply(const Matrix3x3f& other) {
        // Copy data from the other matrix.
        SIMD::Vector4f transposedOther[] = {
            other.m_data[0],
            other.m_data[1],
            other.m_data[2],
            other.m_data[3]
        } ;

        // Transpose the rows of the other matrix to compute the product.
        SIMD::Vector4f::transposeMatrix(
            transposedOther[0],
            transposedOther[1],
            transposedOther[2],
            transposedOther[3]
        ) ;

        // Multiply the vectors of the matrices.
        m_data[0] = m_data[0] * transposedOther[0] ;
        m_data[1] = m_data[1] * transposedOther[1] ;
        m_data[2] = m_data[2] * transposedOther[2] ;
        m_data[3] = m_data[3] * transposedOther[3] ;
    }

    void Matrix3x3f::setColumnValues(const size_t& column, const Point2Df& values) {
        Scalar* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        Scalar* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
    }

    void Matrix3x3f::setColumnValues(const size_t& column, const Point3Df& values) {
        Scalar* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        Scalar* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
        Scalar* row2Values = m_data[2] ;
        row2Values[column] = values.getZ() ;
    }

    void Matrix3x3f::setRowValues(const size_t& row, const Point2Df& values) {
        Scalar* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
    }

    void Matrix3x3f::setRowValues(const size_t& row, const Point3Df& values) {
        Scalar* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
        columnValues[2] = values.getZ() ;
    }

    Matrix3x3f& Matrix3x3f::operator=(const Matrix3x3f& other) {
        std::copy(
            std::begin(other.m_data),
            std::end(other.m_data),
            std::begin(m_data)
        ) ;
        return *this ;
    }
} ;
