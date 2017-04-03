#include <matrices/Matrix4x4f.hpp>
#include <iomanip>

#ifdef USE_NO_SIMD

namespace Mind {
    Matrix4x4f::Matrix4x4f(const Scalar value) : SquareMatrixf(4, value) {}

    void Matrix4x4f::multiply(const Matrix4x4f& other) {
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

    void Matrix4x4f::setColumnValues(
        const size_t column,
        const Point2Df& values
    ) {
        m_data[0][column] = values.get(Point2Df::Axis::X) ;
        m_data[1][column] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setColumnValues(
        const size_t column,
        const Point3Df& values
    ) {
        m_data[0][column] = values.get(Point3Df::Axis::X) ;
        m_data[1][column] = values.get(Point3Df::Axis::Y) ;
        m_data[2][column] = values.get(Point3Df::Axis::Z) ;
    }

    void Matrix4x4f::setRowValues(
        const size_t row,
        const Point2Df& values
    ) {
        m_data[row][0] = values.get(Point2Df::Axis::X) ;
        m_data[row][1] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setRowValues(
        const size_t row,
        const Point3Df& values
    ) {
        m_data[row][0] = values.get(Point3Df::Axis::X) ;
        m_data[row][1] = values.get(Point3Df::Axis::Y) ;
        m_data[row][2] = values.get(Point3Df::Axis::Z) ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(const Scalar scalar) {
        unsigned int length = size() ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; ++rowIndex) {
            for (unsigned int colIndex = 0 ; colIndex < length ; ++colIndex) {
                m_data[rowIndex][colIndex] *= scalar ;
            }
        }
        return *this ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(Matrix4x4f& other) {
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

    Matrix4x4f& Matrix4x4f::operator+=(Matrix4x4f& other) {
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
