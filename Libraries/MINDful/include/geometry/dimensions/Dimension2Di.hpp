#ifndef __MIND__GEOMETRY_DIMENSION2DI__
#define __MIND__GEOMETRY_DIMENSION2DI__

#include <iostream>

#include <MINDTypes.hpp>
#include <geometry/points/Point2Di.hpp>
#include <geometry/dimensions/Dimension3Di.hpp>

namespace Mind {
    class Point2Di ;
    class Dimension3Di ;

    /**
    * A Dimension is used to get the size of an element, and so get the area of
    * the element as a rectangle bounding shape.
    */
    class Dimension2Di final {
        private:
            /** Width of the Dimension2Di. */
            int m_width ;

            /** Height of the Dimension2Di. */
            int m_height ;


        public:
            /** Create a Dimension of zero by zero. */
            Dimension2Di() ;

            /**
             * Copy a Dimension object.
             * @param   copied  The Dimension to copy.
             */
            Dimension2Di(const Dimension2Di& copied) ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             */
            Dimension2Di(const int& width, const int& height) ;

            /** Destroy the Dimension. */
            virtual ~Dimension2Di() ;

            /** Set the Dimension as absolute values. */
            void absolute() ;

            /**
             * Get the width of the dimension.
             * @return  The width.
             */
            int getWidth() const ;

            /**
             * Get the height of the dimension.
             * @return  The height.
             */
            int getHeight() const ;

            /**
             * Set the width of the dimension.
             * @param   width   Width of the dimension.
             */
            void setWidth(const int& width) ;

            /**
            * Set the height of the dimension.
            * @param   height  Height of the dimension.
            */
            void setHeight(const int& height) ;

            /**
            * Set the height of the dimension.
            * @param   width   Width of the dimension.
            * @param   height  Height of the dimension.
            */
            void set(const int& width, const int& height) ;

            /** Conversion from Dimension2D to Point2D. */
            operator Point2Di() ;

            /** Conversion from Dimension2D to Dimension3D. */
            operator Dimension3Di() ;

            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimension.
             */
            Dimension2Di& operator+=(Dimension2Di& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimension.
             */
            Dimension2Di& operator-=(Dimension2Di& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the
             *           result.
             * @param    coeff   The coeff to multiply the Dimension coordinates
             *                   by.
             * @return   The result of the multiplication.
             */
            Dimension2Di& operator*=(const int& coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates
             *                  by.
             * @return  The result of the division.
             */
            Dimension2Di& operator/=(const int& coeff) ;


            /**
             * Assignment operator to copy a Dimension.
             * @return  The current Dimension with the copied values.
             */
            Dimension2Di& operator=(const Dimension2Di& other) ;

            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current
             *                  one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            bool operator==(const Dimension2Di& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current
             *                  one.
             * @return  TRUE if the Dimension have two different size, FALSE
             *          else.
             */
            bool operator!=(const Dimension2Di& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w + b.w, a.h + b.h).
             */
            friend Dimension2Di operator+(const Dimension2Di& a, const Dimension2Di& b) ;


            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Dimension of (a.w - b.w, a.h - b.h).
             */
            friend Dimension2Di operator-(const Dimension2Di& a, const Dimension2Di& b) ;


            /**
             * Multiply a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension at (d.w * coeff, d.w * coeff).
             */
            friend Dimension2Di operator*(const Dimension2Di& d, const int& coeff) ;


            /**
             * Divide a Dimension coordinates by a scalar value (scale).
             * @param   d       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Dimension of (d.w / coeff, d.h / coeff).
             */
            friend Dimension2Di operator/(const Dimension2Di& d, const int& coeff) ;


            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   d   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            friend std::ostream& operator<<(std::ostream& s, const Dimension2Di& d) ;
    } ;
} ;

#endif
