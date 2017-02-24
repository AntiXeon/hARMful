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
            Matrix4x4f(const Scalar& value = 0.f) ;

            /**
             * Copy a Matrix4x4f.
             */
            Matrix4x4f(const Matrix4x4f& mat) ;

            /**
             * Destruction of the matrix.
             */
            virtual ~Matrix4x4f() ;

            /**
             * Multiplay the current Matrix4x4 by another one.
             *          The result is set in the current Matrix4x4.
             * @param   other   The other Matrix4x4 used in the product.
             */
            void multiply(const Matrix4x4f& other) ;

            /**
             * Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(const size_t& column, const Point2Df& values) final ;

            /**
             * Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(const size_t& column, const Point3Df& values) final ;

            /**
             * Set the values of a row from a Point2D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(const size_t& row, const Point2Df& values) final ;

            /**
             * Set the values of a row from a Point3D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(const size_t& row, const Point3Df& values) final ;

           /**
            * Assignment operator to copy a Matrix4x4.
            * @return  The current Matrix4x4 with the copied values.
            */
            Matrix4x4f& operator=(const Matrix4x4f& other) ;
    } ;
} ;

#endif
