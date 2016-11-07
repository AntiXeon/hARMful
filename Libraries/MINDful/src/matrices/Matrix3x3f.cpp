#include <matrices/Matrix3x3f.h>


namespace Mind {
                                              /** CONSTRUCTION / DESTRUCTION **/
    Matrix3x3f::Matrix3x3f(const float& value) : SquareMatrixf(3, value) {}

    Matrix3x3f::Matrix3x3f(const SquareMatrixf& copied) : SquareMatrixf(copied) {}

    Matrix3x3f::~Matrix3x3f() {}


                                                               /** UTILITIES **/
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

    void Matrix3x3f::setColumnValues(size_t column, Point2Df values) {
        float* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
    }

    void Matrix3x3f::setColumnValues(size_t column, Point3Df values) {
        float* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
        float* row2Values = m_data[2] ;
        row2Values[column] = values.getZ() ;
    }

    void Matrix3x3f::setRowValues(size_t row, Point2Df values) {
        float* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
    }

    void Matrix3x3f::setRowValues(size_t row, Point3Df values) {
        float* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
        columnValues[2] = values.getZ() ;
    }


                                                             /*** OPERATORS ***/
    Matrix3x3f& Matrix3x3f::operator=(const Matrix3x3f& other) {
        memcpy(m_data, other.m_data, sizeof(m_data)) ;
        return *this ;
    }

} ;
