#ifndef __MIND_MATRIX_4X4F__
#define __MIND_MATRIX_4X4F__

#include <matrices/SquareMatrixf.h>


namespace Mind {

    /**
    * @brief   4x4 square matrix.
    * @author  CB (c) 2014
    * @version 0.1 2015/02/08
    */
	class Matrix4x4f : public SquareMatrixf {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a square matrix of size equal to 4.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            Matrix4x4f(const Scalar& value = 0) ;

	    	/**
	    	 * @brief	Create a SquareMatrix containing values from another
             *          one.
	    	 * @param	copied  SquareMatrix to copy into the new one.
	    	 */
	    	Matrix4x4f(const SquareMatrixf& copied) ;

            /**
             * @brief   Destruction of the matrix.
             */
            virtual ~Matrix4x4f() ;


                                                               /** UTILITIES **/
            /**
             * @brief   Multiplay the current Matrix4x4 by another one.
             *          The result is set in the current Matrix4x4.
             * @param   other   The other Matrix4x4 used in the product.
             */
            void multiply(const Matrix4x4f& other) ;

            /**
             * @brief   Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(size_t column, Point2Df values) ;

            /**
             * @brief   Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(size_t column, Point3Df values) ;

            /**
             * @brief   Set the values of a row from a Point2D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(size_t row, Point2Df values) ;

            /**
             * @brief   Set the values of a row from a Point3D.
             * @param   row     Index of the row in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(size_t row, Point3Df values) ;


                                                             /*** OPERATORS ***/
           /**
            * @brief   Assignment operator to copy a Matrix4x4.
            * @return  The current Matrix4x4 with the copied values.
            */
            Matrix4x4f& operator=(const Matrix4x4f& other) ;
	} ;

} ;


#endif
