#include <matrices/Matrix3x3f.hpp>

#ifdef USE_NO_SIMD

namespace Mind {
    Matrix3x3f::Matrix3x3f(const Scalar value) : SquareMatrixf(3, value) {}

    void Matrix3x3f::multiply(const Matrix3x3f& other) {
        std::array<std::array<float, 4>, 4> result ;

        unsigned int dimension = size() ;
        for (unsigned int col = 0 ; col < dimension ; ++col) {
            for (unsigned int row = 0 ; row < dimension ; ++row) {
                result[row][col] = 0.f ;
                for (unsigned int iter = 0 ; iter < dimension ; ++iter) {
                    result[row][col] += m_data[row][iter] * other.m_data[iter][col] ;
                }
            }
        }

        m_data = result ;
    }

    void Matrix3x3f::setColumnValues(
        const size_t column,
        const Point2Df& values
    ) {
        m_data[0][column] = values.get(Vector2f::Axis::X) ;
        m_data[1][column] = values.get(Vector2f::Axis::Y) ;
    }

    void Matrix3x3f::setColumnValues(
        const size_t column,
        const Point3Df& values
    ) {
        m_data[0][column] = values.get(Vector3f::Axis::X) ;
        m_data[1][column] = values.get(Vector3f::Axis::Y) ;
        m_data[2][column] = values.get(Vector3f::Axis::Z) ;
    }

    void Matrix3x3f::setRowValues(
        const size_t row,
        const Point2Df& values
    ) {
        m_data[row][0] = values.get(Vector2f::Axis::X) ;
        m_data[row][1] = values.get(Vector2f::Axis::Y) ;
    }

    void Matrix3x3f::setRowValues(
        const size_t row,
        const Point3Df& values
    ) {
        m_data[row][0] = values.get(Vector3f::Axis::X) ;
        m_data[row][1] = values.get(Vector3f::Axis::Y) ;
        m_data[row][2] = values.get(Vector3f::Axis::Z) ;
    }

    Matrix3x3f& Matrix3x3f::operator*=(const Scalar scalar) {
        unsigned int length = size() ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; ++rowIndex) {
            for (unsigned int colIndex = 0 ; colIndex < length ; ++colIndex) {
                m_data[rowIndex][colIndex] *= scalar ;
            }
        }
        return *this ;
    }

    Matrix3x3f& Matrix3x3f::operator*=(Matrix3x3f& other) {
        std::array<std::array<float, 4>, 4> result ;

        unsigned int dimension = size() ;
        for (unsigned int col = 0 ; col < dimension ; ++col) {
            for (unsigned int row = 0 ; row < dimension ; ++row) {
                result[row][col] = 0.f ;
                for (unsigned int iter = 0 ; iter < dimension ; ++iter) {
                    result[row][col] += m_data[row][iter] * other.m_data[iter][col] ;
                }
            }
        }

        m_data = result ;

        return *this ;
    }

    Matrix3x3f& Matrix3x3f::operator+=(Matrix3x3f& other) {
        unsigned int length = size() ;
        for (unsigned int colIndex = 0 ; colIndex < length ; colIndex++) {
            for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
                m_data[rowIndex][colIndex] += other[rowIndex][colIndex] ;
            }
        }
        return *this ;
    }
} ;

#endif
