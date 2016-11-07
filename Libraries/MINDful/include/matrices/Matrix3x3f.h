#ifndef __MIND_MATRIX_3X3F__
#define __MIND_MATRIX_3X3F__

#include <matrices/SquareMatrixf.h>


namespace Mind {

    /**
    * @brief   3x3 square matrix.
    * @author  CB (c) 2014
    * @version 0.1 2015/02/08
    */
    class Matrix3x3f : public SquareMatrixf {
        public:
                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a square matrix of size equal to 3.
             * @param   value   Value of the matrix when created or cleared.
             *                  The default value is zero.
             */
            Matrix3x3f(const float& value = 0) ;

	    	/**
	    	 * @brief	Create a SquareMatrix containing values from another
             *          one.
	    	 * @param	copied  SquareMatrix to copy into the new one.
	    	 */
	    	Matrix3x3f(const SquareMatrixf& copied) ;

            /**
             * @brief   Destruction of the matrix.
             */
            virtual ~Matrix3x3f() ;


                                                               /** UTILITIES **/
            /**
             * @brief   Multiplay the current Matrix3x3 by another one.
             *          The result is set in the current Matrix3x3.
             * @param   other   The other Matrix3x3 used in the product.
             */
            void multiply(const Matrix3x3f& other) ;

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
            * @brief   Assignment operator to copy a Matrix3x3.
            * @return  The current Matrix3x3 with the copied values.
            */
            Matrix3x3f& operator=(const Matrix3x3f& other) ;
    } ;

} ;


#endif
