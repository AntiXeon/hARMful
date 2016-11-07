#ifndef __MIND_GEOMETRY_DIMENSION2DF__
#define __MIND_GEOMETRY_DIMENSION2DF__


#include <iostream>

#include <MINDTypes.h>
#include <geometry/points/Point2Df.h>
#include <geometry/dimensions/Dimension3Df.h>


namespace Mind {

    class Point2Df ;
    class Dimension3Df ;

    /**
    * @brief   A Dimension is used to get the size of an element, and so get the
    *          area of the element as a rectangle bounding shape.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Dimension2Df {
        private:
            /** @brief  Width of the Dimension2Di. */
            Scalar m_width ;

            /** @brief  Height of the Dimension2Di. */
            Scalar m_height ;


        public:
            /** @brief  Create a Dimension of zero by zero. */
            Dimension2Df() ;

            /**
            * @brief   Copy a Dimension object.
            * @param   copied  The Dimension to copy.
            */
            Dimension2Df(const Dimension2Df& copied) ;

            /**
            * @brief   Create a Dimension with the given sizes.
            * @param   width   Width to set the size of the element.
            * @param   height  Height to set the size of the element.
            */
            Dimension2Df(const Scalar& width, const Scalar& height) ;

            /** @brief  Destroy the Dimension. */
            virtual ~Dimension2Df() ;


            /** @brief  Set the Dimension as absolute values. */
            void absolute() ;



                                                               /*** GETTERS ***/
            /**
            * @brief   Get the width of the dimension.
            * @return  The width.
            */
            Scalar getWidth() const ;

            /**
            * @brief   Get the height of the dimension.
            * @return  The height.
            */
            Scalar getHeight() const ;


                                                               /*** SETTERS ***/
            /**
            * @brief   Set the width of the dimension.
            * @param   width   Width of the dimension.
            */
            void setWidth(const Scalar& width) ;

            /**
            * @brief   Set the height of the dimension.
            * @param   height  Height of the dimension.
            */
            void setHeight(const Scalar& height) ;

            /**
            * @brief   Set the height of the dimension.
            * @param   width   Width of the dimension.
            * @param   height  Height of the dimension.
            */
            void set(const Scalar& width, const Scalar& height) ;


                                                             /*** OPERATORS ***/
            /** @brief  Conversion from Dimension2D to Point2D. */
            operator Point2Df() ;

            /** @brief  Conversion from Dimension2D to Dimension3D. */
            operator Dimension3Df() ;


            /**
            * @brief   Add a Dimension and affect the result.
            * @param   other   The other Dimension to add.
            * @return  The sum of the two Dimension.
            */
            Dimension2Df& operator+=(Dimension2Df& other) ;

            /**
            * @brief   Substract a Dimension and affect the result.
            * @param   other   The other Dimension to substract.
            * @return  The substract of the two Dimension.
            */
            Dimension2Df& operator-=(Dimension2Df& other) ;

            /**
            * @brief    Multiply a Dimension by a scalar value and affect the
            *           result.
            * @param    coeff   The coeff to multiply the Dimension coordinates
            *                   by.
            * @return   The result of the multiplication.
            */
            Dimension2Df& operator*=(const Scalar& coeff) ;

            /**
            * @brief   Divide a Dimension by a scalar value and affect the result.
            * @param   coeff   The coeff to divide the Dimension coordinates by.
            * @return  The result of the division.
            */
            Dimension2Df& operator/=(const Scalar& coeff) ;


            /**
            * @brief   Assignment operator to copy a Dimension.
            * @return  The current Dimension with the copied values.
            */
            Dimension2Df& operator=(const Dimension2Df& other) ;

            /**
            * @brief   Test if two Dimension have the same size.
            * @param   other   An other Dimension to compare to the current one.
            * @return  TRUE if the Dimension have the same size, FALSE else.
            */
            bool operator==(const Dimension2Df& other) const ;

            /**
            * @brief   Test if two Dimension have not the same size.
            * @param   other   An other Dimension to compare to the current one.
            * @return  TRUE if the Dimension have two different size, FALSE else.
            */
            bool operator!=(const Dimension2Df& other) const ;



            /**
            * @brief   Add a Dimension to another one.
            * @param   a   First Dimension.
            * @param   b   Second Dimension.
            * @return  Dimension of (a.w + b.w, a.h + b.h).
            */
            friend Dimension2Df operator+(const Dimension2Df& a, const Dimension2Df& b) ;


            /**
            * @brief   Substract a Dimension to another one.
            * @param   a   First Dimension.
            * @param   b   Second Dimension.
            * @return  Dimension of (a.w - b.w, a.h - b.h).
            */
            friend Dimension2Df operator-(const Dimension2Df& a, const Dimension2Df& b) ;


            /**
            * @brief   Multiply a Dimension coordinates by a scalar value (scale).
            * @param   d       Dimension to be multiplied.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Dimension at (d.w * coeff, d.w * coeff).
            */
            friend Dimension2Df operator*(const Dimension2Df& d, const Scalar& coeff) ;


            /**
            * @brief   Divide a Dimension coordinates by a scalar value (scale).
            * @param   d       Dimension to be divided.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Dimension of (d.w / coeff, d.h / coeff).
            */
            friend Dimension2Df operator/(const Dimension2Df& d, const Scalar& coeff) ;


            /**
            * @brief   Echo the Dimension size on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   d   The Dimension to print.
            * @return  The stream with the printed Dimension size.
            */
            friend std::ostream& operator<<(std::ostream& s, const Dimension2Df& d) ;
    } ;

} ;

#endif
