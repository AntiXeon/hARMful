#include <matrices/Matrix4x4f.hpp>
#include <iomanip>

namespace Mind {
    Matrix4x4f::Matrix4x4f(const Scalar& value) : SquareMatrixf(4, value) {}

    Matrix4x4f::Matrix4x4f(const Matrix4x4f& mat) : SquareMatrixf(mat) {}

    Matrix4x4f::~Matrix4x4f() {}

    void Matrix4x4f::multiply(const Matrix4x4f& other) {
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

    void Matrix4x4f::setColumnValues(const size_t& column, const Point2Df& values) {
        float* row0Values = (float*) m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = (float*) m_data[1] ;
        row1Values[column] = values.getY() ;
    }

    void Matrix4x4f::setColumnValues(const size_t& column, const Point3Df& values) {
        float* row0Values = (float*) m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = (float*) m_data[1] ;
        row1Values[column] = values.getY() ;
        float* row2Values = (float*) m_data[2] ;
        row2Values[column] = values.getZ() ;
    }

    void Matrix4x4f::setRowValues(const size_t& row, const Point2Df& values) {
        float* columnValues = (float*) m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
    }

    void Matrix4x4f::setRowValues(const size_t& row, const Point3Df& values) {
        float* columnValues = (float*) m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
        columnValues[2] = values.getZ() ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(const Scalar& scalar) {
        unsigned int length = size() ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] *= scalar ;
        }
        return *this ;
    }

    Matrix4x4f Matrix4x4f::operator*(const Scalar& scalar) {
        Matrix4x4f mat(*this) ;
        mat *= scalar ;
        return mat ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(Matrix4x4f& other) {
        // Transpose the matrix to easily compute the product of each line of
        // "this" by each column of "other".
        Matrix4x4f otherCopy = other ;
        SIMD::Vector4f::transposeMatrix(
            otherCopy.m_data[0],
            otherCopy.m_data[1],
            otherCopy.m_data[2],
            otherCopy.m_data[3]
        ) ;

        // Multiply each line of "this" by each column of "other".
        // Then add each element of the resulting row and store it in "this".
        unsigned int length = size() ;
        for (unsigned int thisRowIndex = 0 ; thisRowIndex < length ; thisRowIndex++) {
            Array4f rowResult ;
            for(unsigned int otherRowIndex = 0 ; otherRowIndex < length ; otherRowIndex++) {
                SIMD::Vector4f mulRow = m_data[thisRowIndex] * otherCopy.m_data[otherRowIndex] ;
                Scalar value = mulRow.horizontalAdd() ;
                rowResult[otherRowIndex] = value ;
            }
            m_data[thisRowIndex].set(rowResult) ;
        }

        return *this ;
    }

    Matrix4x4f Matrix4x4f::operator*(Matrix4x4f& other) {
        Matrix4x4f mat(*this) ;
        mat *= other ;
        return mat ;
    }

    Matrix4x4f& Matrix4x4f::operator+=(Matrix4x4f& other) {
        unsigned int length = size() ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] += other[rowIndex] ;
        }
        return *this ;
    }

    Matrix4x4f Matrix4x4f::operator+(Matrix4x4f& other) {
        Matrix4x4f mat(*this) ;
        mat += other ;
        return mat ;
    }

    Matrix4x4f& Matrix4x4f::operator=(const Matrix4x4f& other) {
        std::copy(
            std::begin(other.m_data),
            std::end(other.m_data),
            std::begin(m_data)
        ) ;
        return *this ;
    }
} ;
