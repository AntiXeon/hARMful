#include <matrices/Matrix4x4f.hpp>
#include <matrices/Matrix3x3f.hpp>
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

    void Matrix4x4f::compose(
        const Vector3f& translation,
        const Quaternion& rotation,
        const Vector3f& scale
    ) {
        // Compose the matrix in this order: scale, rotation and translation.
        // First, convert the quaternion to a 3x3 rotation matrix.
        Matrix3x3f rotationMatrix ;
        rotation.to(rotationMatrix) ;

        // Then multiply scale by rotation matrix values and put it in the
        // current transformation matrix.
        m_data[0][0] = scale[Point3Df::X] * rotationMatrix[0][0] ;
        m_data[0][1] = scale[Point3Df::Y] * rotationMatrix[0][1] ;
        m_data[0][2] = scale[Point3Df::Z] * rotationMatrix[0][2] ;

        m_data[1][0] = scale[Point3Df::X] * rotationMatrix[1][0] ;
        m_data[1][1] = scale[Point3Df::Y] * rotationMatrix[1][1] ;
        m_data[1][2] = scale[Point3Df::Z] * rotationMatrix[1][2] ;

        m_data[2][0] = scale[Point3Df::X] * rotationMatrix[2][0] ;
        m_data[2][1] = scale[Point3Df::Y] * rotationMatrix[2][1] ;
        m_data[2][2] = scale[Point3Df::Z] * rotationMatrix[2][2] ;

        // Put the translation value in the last column.
        setColumnValues(3, translation) ;

        // No projection.
        Point4Df noProjection(0.f, 0.f, 0.f, 1.f) ;
        setRowValues(3, noProjection) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point2Df& values
    ) {
        m_data[0][column] = values.get(Point2Df::Axis::X) ;
        m_data[1][column] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point3Df& values
    ) {
        m_data[0][column] = values.get(Point3Df::Axis::X) ;
        m_data[1][column] = values.get(Point3Df::Axis::Y) ;
        m_data[2][column] = values.get(Point3Df::Axis::Z) ;
    }

    void Matrix4x4f::setColumnValues(
        const unsigned int column,
        const Point4Df& values
    ) {
        m_data[0][column] = values.get(Point4Df::Axis::X) ;
        m_data[1][column] = values.get(Point4Df::Axis::Y) ;
        m_data[2][column] = values.get(Point4Df::Axis::Z) ;
        m_data[3][column] = values.get(Point4Df::Axis::W) ;
    }

    Point4Df Matrix4x4f::getColumnValues(const unsigned int column) {
        Point4Df tmp ;
        tmp.set(
            m_data[0][column],
            m_data[1][column],
            m_data[2][column],
            m_data[3][column]
        );
        return tmp;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point2Df& values
    ) {
        m_data[row][0] = values.get(Point2Df::Axis::X) ;
        m_data[row][1] = values.get(Point2Df::Axis::Y) ;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point3Df& values
    ) {
        m_data[row][0] = values.get(Point3Df::Axis::X) ;
        m_data[row][1] = values.get(Point3Df::Axis::Y) ;
        m_data[row][2] = values.get(Point3Df::Axis::Z) ;
    }

    void Matrix4x4f::setRowValues(
        const unsigned int row,
        const Point4Df& values
    ) {
        m_data[row][0] = values.get(Point4Df::Axis::X) ;
        m_data[row][1] = values.get(Point4Df::Axis::Y) ;
        m_data[row][2] = values.get(Point4Df::Axis::Z) ;
        m_data[row][3] = values.get(Point4Df::Axis::W) ;
    }

    Point4Df Matrix4x4f::getRowValues(const unsigned int row) {
        Point4Df tmp ;
        tmp.set(
            m_data[row][0],
            m_data[row][1],
            m_data[row][2],
            m_data[row][3]
        );
        return tmp;
    }

    Matrix4x4f& Matrix4x4f::operator*=(const Scalar scalar) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; ++rowIndex) {
            for (unsigned int colIndex = 0 ; colIndex < length ; ++colIndex) {
                m_data[rowIndex][colIndex] *= scalar ;
            }
        }
        return *this ;
    }

    Matrix4x4f& Matrix4x4f::operator*=(Matrix4x4f& other) {
        std::array<std::array<float, 4>, 4> result ;

        unsigned int dimension = static_cast<unsigned int>(size()) ;
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
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int colIndex = 0 ; colIndex < length ; colIndex++) {
            for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
                m_data[rowIndex][colIndex] += other[rowIndex][colIndex] ;
            }
        }
        return *this ;
    }

    Vector3f Matrix4x4f::extractTranslation(Matrix4x4f& matrix) {
        // Translation vector is stored in the last column.
        const int TranslationVectorColumnIndex = 3;
        Vector3f translation = static_cast<Vector3f>(matrix.getColumnValues(TranslationVectorColumnIndex)) ;

        // Clear values in the matrix (with w = 1).
        matrix.setColumnValues(TranslationVectorColumnIndex, Vector4f(0, 0, 0, 1)) ;

        return translation ;
    }

    Vector3f Matrix4x4f::extractScale(Matrix4x4f& matrix) {
        const int Vector3Size = 3;

        Vector3f scale ;

        // Take the length of the (remaining) column vectors.
        // This will be the scale vector.
        for (int columnIndex = 0; columnIndex < Vector3Size; ++columnIndex)
        {
            Vector3f tmpVector = static_cast<Vector3f>(matrix.getColumnValues(columnIndex)) ;
            scale[columnIndex] = tmpVector.length() ;
        }

        return scale ;
    }

    Quaternion Matrix4x4f::extractRotation(
        Matrix4x4f& matrix,
        const Vector3f& scale
    ) {
        const int Vector3Size = 3;

        // Divide the matrix columns with the previously computed scale vector
        // components.
        // This will give the rotation matrix that can be converted to quaternion.
        for (int columnIndex = 0; columnIndex < Vector3Size; ++columnIndex)
        {
            Vector3f tmpVector = static_cast<Vector3f>(matrix.getColumnValues(columnIndex)) ;
            tmpVector = tmpVector / scale[columnIndex];
            matrix.setColumnValues(columnIndex, tmpVector);
        }

        Matrix3x3f rotationMatrix;
        rotationMatrix.setRowValues(0, static_cast<Vector3f>(matrix.getRowValues(0))) ;
        rotationMatrix.setRowValues(1, static_cast<Vector3f>(matrix.getRowValues(1))) ;
        rotationMatrix.setRowValues(2, static_cast<Vector3f>(matrix.getRowValues(2))) ;
        return Quaternion(rotationMatrix);
    }
} ;

#endif
