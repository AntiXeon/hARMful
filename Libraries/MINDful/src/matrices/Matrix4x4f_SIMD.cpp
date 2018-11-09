#include <matrices/Matrix4x4f.hpp>
#include <iomanip>

#ifdef USE_SIMD // for compilations where SSE or NEON are available

namespace Mind {
    Matrix4x4f::Matrix4x4f(const Scalar value) : SquareMatrixf(4, value) {}

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
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] *= scalar ;
        }
        return *this ;
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
        unsigned int length = static_cast<unsigned int>(size()) ;
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

    Matrix4x4f& Matrix4x4f::operator+=(Matrix4x4f& other) {
        unsigned int length = static_cast<unsigned int>(size()) ;
        for (unsigned int rowIndex = 0 ; rowIndex < length ; rowIndex++) {
            m_data[rowIndex] += other[rowIndex] ;
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
