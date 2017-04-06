#ifndef __MIND__MATRIX_4X4F__
#define __MIND__MATRIX_4X4F__

#include <matrices/SquareMatrixf.hpp>

namespace Mind {
    /**
     * 4x4 square matrix.
     */
    class Matrix4x4f final : public SquareMatrixf {
        public:
            /**
             * Create a square matrix of size equal to 4.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            exported Matrix4x4f(const Scalar value = 0.f) ;

            /**
             * Multiplay the current Matrix4x4 by another one.
             *          The result is set in the current Matrix4x4.
             * @param   other   The other Matrix4x4 used in the product.
             */
            exported void multiply(const Matrix4x4f& other) ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point2Df& values
            ) final ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setColumnValues(
                const unsigned int column,
                const Point3Df& values
            ) final ;

            /**
             * Set the values of a row from a Point2D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point2Df& values
            ) final ;

            /**
             * Set the values of a row from a Point3D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            exported virtual void setRowValues(
                const unsigned int row,
                const Point3Df& values
            ) final ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into the current matrix.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f& operator*=(const Scalar scalar) ;

            /**
             * Multiply the current matrix by a scalar value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   scalar  The scalar value to multiply each component of
             *                  the matrix with.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f operator*(const Scalar scalar) ;

            /**
             * Multiply the current matrix by another matrix.
             * The result is put into the current matrix.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f& operator*=(Matrix4x4f& other) ;

            /**
             * Multiply the current matrix by another value.
             * The result is put into a new matrix.
             * @param   mat     The matrix to multiply.
             * @param   other   The other matrix to multiply with the current
             *                  one.
             * @return  The result of the multiplication.
             */
            exported Matrix4x4f operator*(Matrix4x4f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into the current matrix.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix4x4f& operator+=(Matrix4x4f& other) ;

            /**
             * Addition of the current matrix with another one.
             * The result is put into a new matrix.
             * @param   mat     The matrix to add.
             * @param   other   The other matrix to add to the current one.
             * @return  The result of the addition.
             */
            exported Matrix4x4f operator+(Matrix4x4f& other) ;
    } ;

    inline Matrix4x4f Matrix4x4f::operator*(const Scalar scalar) {
        Matrix4x4f mat(*this) ;
        mat *= scalar ;
        return mat ;
    }

    inline Matrix4x4f Matrix4x4f::operator*(Matrix4x4f& other) {
        Matrix4x4f mat(*this) ;
        mat *= other ;
        return mat ;
    }

    inline Matrix4x4f Matrix4x4f::operator+(Matrix4x4f& other) {
        Matrix4x4f mat(*this) ;
        mat += other ;
        return mat ;
    }
} ;

#endif
