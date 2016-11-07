#ifndef __MIND_MATRIX2D__
#define __MIND_MATRIX2D__


#include <iostream>
#include <vector>
#include <stddef.h>

#include <MINDTypes.h>


namespace Mind {

    /**
    * @brief   Resizable matrix to store data with an unknown final size.
    * @author  CB (c) 2014
    * @version 0.1 2014/06/02
    */
    template<class T>
    class Matrix2D {
        private:
            /** @brief  Dynamic matrix itself, handled through vectors. */
            std::vector< std::vector<T> > m_data ;


        public:
            /**
            * @brief   Create a dynamically resizable Matrix with initial sizes.
            * @param   cols    Amount of columns in the Matrix.
            * @param   rows    Amount of rows in the Matrix.
            * @param   value   Initial value in the Matrix.
            */
            Matrix2D(size_t cols = 1, size_t rows = 1, const T& value = 0) ;

            /** @brief  Destroy the matrix. */
            virtual ~Matrix2D() ;


            /** @brief  Clear the matrix. */
            void clear() ;

            /**
            * @brief   Resize the matrix. Use 0 to leave a dimension with the
            *          current size.
            * @param   cols    Amount of columns in the Matrix.
            * @param   rows    Amount of rows in the Matrix.
            * @param   value   Initial value in the Matrix.
            */
            void resize(size_t cols, size_t rows, const T& value = 0) ;

            /**
            * @brief   Reserve space in the matrix.
            * @param
            */
            void reserve(size_t cols, size_t rows) ;

            /** @brief  Get the element a the specified position. */
            T& at(size_t col, size_t row) ;


            /** @brief	Get the number of rows in the matrix. */
            size_t rows() const ;

            /** @brief	Get the number of cols in the matrix. */
            size_t cols() const ;


            /** @brief  Get a row from the matrix. */
            std::vector<T>& operator[] (size_t iIndex) ;
    } ;

    /** @brief  Echo the matrix on console. */
    template<class T>
    std::ostream& operator<<(std::ostream& s, Matrix2D<T>& mat) ;




    ///****************************** IMPLEMENTATION *******************************/
    template <class T>
    Matrix2D<T>::Matrix2D(size_t rows, size_t cols, const T& value) {
        m_data = std::vector< std::vector<T> >(rows, std::vector<T>(cols, value)) ;
    }

    template <class T>
    Matrix2D<T>::~Matrix2D() {
        clear() ;
    }


    template <class T>
    void Matrix2D<T>::clear() {
        for (size_t row = 0 ; row < m_data.size() ; row++)
            m_data[row].clear() ;
        m_data.clear() ;
    }

    template <class T>
    void Matrix2D<T>::resize(size_t rows, size_t cols, const T& value) {
        m_data.resize(rows) ;
        for (size_t row = 0 ; row < m_data.size() ; row++) {
            m_data[row].resize(cols, value) ;
        }
    }

    template <class T>
    void Matrix2D<T>::reserve(size_t rows, size_t cols) {
        m_data.reserve(rows) ;
        for (size_t row = 0 ; row < m_data.size() ; row++)
            m_data[row].reserve(cols) ;
    }

    template <class T>
    T& Matrix2D<T>::at(size_t row, size_t col) {
        return m_data[row][col] ;
    }

    template <class T>
    size_t Matrix2D<T>::rows() const {
        return m_data.size() ;
    }

    template <class T>
    size_t Matrix2D<T>::cols() const {
        return m_data[0].size() ;
    }

    template <class T>
    std::vector<T>& Matrix2D<T>::operator[] (size_t iIndex) {
        return m_data[iIndex] ;
    }

    template<class T>
    std::ostream& operator<<(std::ostream& s, Matrix2D<T>& mat) {
        size_t cols = mat.cols() ;
        size_t rows = mat.rows() ;
        size_t lastRow = rows - 1 ;

        for (size_t col = 0 ; col < cols ; col++) {
            s << "[" ;
                for (size_t row = 0 ; row < rows ; row++) {
                    s << mat.at(row, col) ;
                    if (row < lastRow)
                        s << "," ;
                }
            s << "]" << std::endl ;
        }

        return s ;
    }

} ;

#endif
