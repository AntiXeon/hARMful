#ifndef __MIND__GEOMETRY_DIMENSION2DF__
#define __MIND__GEOMETRY_DIMENSION2DF__

#include <iostream>

#include <MINDTypes.hpp>
#include <geometry/points/Point2Df.hpp>
#include <geometry/dimensions/Dimension3Df.hpp>

namespace Mind {
    class Point2Df ;
    class Dimension3Df ;

    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension2Df final {
        private:
            /** Width of the Dimension2Di. */
            Scalar m_width ;

            /** Height of the Dimension2Di. */
            Scalar m_height ;


        public:
            /** Create a Dimension of zero by zero. */
            Dimension2Df() ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             */
            Dimension2Df(Scalar width, Scalar height) ;

            /** Set the Dimension as absolute values. */
            void absolute() ;

            /**
             * Get the width of the dimension.
             * @return  The width.
             */
            Scalar getWidth() const ;

            /**
             * Get the height of the dimension.
             * @return  The height.
             */
            Scalar getHeight() const ;

            /**
             * Set the width of the dimension.
             * @param   width   Width of the dimension.
             */
            void setWidth(Scalar width) ;

            /**
             * Set the height of the dimension.
             * @param   height  Height of the dimension.
             */
            void setHeight(Scalar height) ;

            /**
             * Set the height of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             */
            void set(Scalar width, Scalar height) ;

            /** Conversion from Dimension2D to Point2D. */
            operator Point2Df() ;

            /** Conversion from Dimension2D to Dimension3D. */
            operator Dimension3Df() ;


            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimension.
             */
            Dimension2Df& operator+=(Dimension2Df& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimension.
             */
            Dimension2Df& operator-=(Dimension2Df& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the result.
             * @param    coeff   The coeff to multiply the Dimension coordinates
             *                   by.
             * @return   The result of the multiplication.
             */
            Dimension2Df& operator*=(Scalar coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            Dimension2Df& operator/=(Scalar coeff) ;


            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            bool operator==(const Dimension2Df& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            bool operator!=(const Dimension2Df& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w + b.w, a.h + b.h).
             */
            friend Dimension2Df operator+(const Dimension2Df& a, const Dimension2Df& b) ;


            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w - b.w, a.h - b.h).
             */
            friend Dimension2Df operator-(const Dimension2Df& a, const Dimension2Df& b) ;


            /**
             * Multiply a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension at (d.w * coeff, d.w * coeff).
             */
            friend Dimension2Df operator*(const Dimension2Df& d, Scalar coeff) ;


            /**
             * Divide a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension of (d.w / coeff, d.h / coeff).
             */
            friend Dimension2Df operator/(const Dimension2Df& d, Scalar coeff) ;


            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   d   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            friend std::ostream& operator<<(std::ostream& s, const Dimension2Df& d) ;
    } ;
} ;

#endif
