#ifndef __MIND_SQUARE_MATRIXF__
#define __MIND_SQUARE_MATRIXF__


#include <stddef.h>
#include <iostream>
#include <iomanip>

#include <simd/SIMDVector.h>
#include <geometry/points/Point2Df.h>
#include <geometry/points/Point3Df.h>


namespace Mind {

    // Pre-declare operator overloadings
    class SquareMatrixf ;
    std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) ;


    /**
     * @brief   Square matrix base class with a fixed size.
     *          The maximal size of the matrix is four elements on row and
     *          columns.
     * @author  CB (c) 2014
     * @version 0.1 2015/02/05
     */
    class SquareMatrixf {
    	protected:
            /**
             * @brief   Maximal amount of data in a direction.
             */
            static const int MaximalDataSize ;

    		/**
    		 * @brief	Size of the SquareMatrix (one side).
    		 */
    		int m_size ;

            /**
             * @brief   Default value of the cleared SquareMatrix.
             */
            float m_defaultValue ;

    		/**
    		 * @brief	SquareMatrix content values.
    		 */
    		SIMD::Vector4f m_data[4] ;


	    public:
                                              /** CONSTRUCTION / DESTRUCTION **/
	    	/**
	    	 * @brief	Create a SquareMatrix with its size.
	    	 * @param	size 	Size of the SquareMatrix. This will produce a
	    	 *					"size x size" matrix.
	    	 * @param	value 	Initial value in the SquareMatrix.
	    	 */
	    	SquareMatrixf(const unsigned int& size, const float& value = 0) ;

	    	/**
	    	 * @brief	Create a SquareMatrix containing values from another
             *          one.
	    	 * @param	copied  SquareMatrix to copy into the new one.
	    	 */
	    	SquareMatrixf(const SquareMatrixf& copied) ;

	    	/**
	    	 * @brief	Destruction of the SquareMatrix.
	    	 */
	    	virtual ~SquareMatrixf() ;


                                                               /** UTILITIES **/
            /**
             * @brief	Fill the SquareMatrix with its default value.
             */
            void clear() ;

            /**
             * @brief   Fill the SquareMatrix with zero values and put one on
             *          matrix diagonal (left to right, top to bottom).
             */
            void identity() ;

            /**
             * @brief   Set the values of a column from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(size_t column, Point2Df values) = 0 ;

            /**
             * @brief   Set the values of a column from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setColumnValues(size_t column, Point3Df values) = 0 ;

            /**
             * @brief   Set the values of a row from a Point2D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(size_t row, Point2Df values) = 0 ;

            /**
             * @brief   Set the values of a row from a Point3D.
             * @param   column  Index of the column in the SquareMatrix.
             * @param   values  Values to set.
             */
            virtual void setRowValues(size_t row, Point3Df values) = 0 ;

            /**
             * @brief   Copy a SquareMatrix into the current one.
             * @param   copied  SquareMatrix to copy into the new one.
             */
            void copy(const SquareMatrixf& copied) ;



                                                       /** GETTERS / SETTERS **/
            /**
             * @brief	Get the element a the specified position.
             * @param   col     Index of the wanted column.
             * @param   row     Index of the wanted row.
             * @return	Reference to the element at the wanted column and row
             *			indices.
             */
            float& at(
                      const unsigned int& col,
                      const unsigned int& row
                     ) const ;

            /**
             * @brief   Set the element a the specified position.
             * @param   row     Index of the wanted row.
             * @param   col     Index of the wanted column.
             * @param   value   Value to set at the given position.
             */
            void at(
                    const unsigned int& col,
                    const unsigned int& row,
                    const float& value
                   ) ;

            /**
             * @brief   Set or get the element a the specified position.
             * @param   index   Index of the wanted row.
             */
            float* operator[](int index) ;

            /**
             * @brief	Get the size of the SquareMatrix.
             * @return	Size of the SquareMatrix (amount of both columns and
             *			rows).
             */
            unsigned int size() const ;

            /**
            * @brief   Echo the SquareMatrix values on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The SquareMatrix to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(std::ostream& s, const SquareMatrixf& p) ;

        protected:
            /**
             * @brief   Get the total size of the SquareMatrix.
             * @return  Total amount of elements in the SquareMatrix.
             */
            unsigned int totalSize() const ;

            /**
             * @brief   Clear the matrix with the given value.
             * @param   value   Value to fill the matrix with.
             */
            void clearWith(const float& value) ;

            /**
             * @brief   Get the inner data of the SquareMatrix.
             * @param   output  Storage of the inner data.
             * @warning Output must have the right size as a single array.
             */
            void getData(float* output) ;

    } ;

} ;


#endif
