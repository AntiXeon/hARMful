#include <matrices/Matrix4x4f.h>
#include <iomanip>

namespace Mind {

                                              /** CONSTRUCTION / DESTRUCTION **/
    Matrix4x4f::Matrix4x4f(const Scalar& value) : SquareMatrixf(4, value) {}

    Matrix4x4f::Matrix4x4f(const SquareMatrixf& copied) : SquareMatrixf(copied) {}

    Matrix4x4f::~Matrix4x4f() {}


                                                               /** UTILITIES **/
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

    void Matrix4x4f::setColumnValues(size_t column, Point2Df values) {
        float* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
    }

    void Matrix4x4f::setColumnValues(size_t column, Point3Df values) {
        float* row0Values = m_data[0] ;
        row0Values[column] = values.getX() ;
        float* row1Values = m_data[1] ;
        row1Values[column] = values.getY() ;
        float* row2Values = m_data[2] ;
        row2Values[column] = values.getZ() ;
    }

    void Matrix4x4f::setRowValues(size_t row, Point2Df values) {
        float* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
    }

    void Matrix4x4f::setRowValues(size_t row, Point3Df values) {
        float* columnValues = m_data[row] ;
        columnValues[0] = values.getX() ;
        columnValues[1] = values.getY() ;
        columnValues[2] = values.getZ() ;
    }

                                                             /*** OPERATORS ***/

    Matrix4x4f& Matrix4x4f::operator=(const Matrix4x4f& other) {
        memcpy(m_data, other.m_data, sizeof(m_data)) ;
        return *this ;
    }

} ;
