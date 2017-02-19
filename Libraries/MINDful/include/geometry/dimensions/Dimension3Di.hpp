#ifndef __MIND__GEOMETRY_DIMENSION3DI__
#define __MIND__GEOMETRY_DIMENSION3DI__

#include <iostream>

#include <MINDTypes.hpp>
#include <geometry/points/Point3Di.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>

namespace Mind {
    class Dimension2Di ;
    class Point3Di ;

    /**
     * A Dimension is used to get the size of an element, and so get the area of
     * the element as a rectangle bounding shape.
     */
    class Dimension3Di final {
        private:
            /** Width of the Dimension2Df. */
            int m_width ;

            /** Height of the Dimension2Df. */
            int m_height ;

            /** Depth of the Dimension2Df. */
            int m_depth ;


        public:
            /** Create a Dimension of zero by zero. */
            Dimension3Di() ;

            /**
             * Copy a Dimension object.
             * @param   copied  The Dimension to copy.
             */
            Dimension3Di(const Dimension3Di& copied) ;

            /**
             * Create a Dimension with the given sizes.
             * @param   width   Width to set the size of the element.
             * @param   height  Height to set the size of the element.
             * @param   depth   Depth to set the size of the element.
             */
            Dimension3Di(const int& width, const int& height, const int& depth) ;

            /** Destroy the Dimension. */
            virtual ~Dimension3Di() ;

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
             * Get the depth of the dimension.
             * @return  The depth.
             */
            int getDepth() const ;

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
             * Set the depth of the dimension.
             * @param   depth   Depth of the dimension.
             */
            void setDepth(const int& depth) ;

            /**
             * Set the depth of the dimension.
             * @param   width   Width of the dimension.
             * @param   height  Height of the dimension.
             * @param   depth   Depth of the dimension.
             */
            void set(const int& width, const int& height, const int& depth) ;

            /** Conversion from Dimension3D to Point3D. */
            operator Point3Di() ;

            /** Conversion from Dimension3D to Dimension2D. */
            operator Dimension2Di() ;

            /**
             * Add a Dimension and affect the result.
             * @param   other   The other Dimension to add.
             * @return  The sum of the two Dimensions.
             */
            Dimension3Di& operator+=(Dimension3Di& other) ;

            /**
             * Substract a Dimension and affect the result.
             * @param   other   The other Dimension to substract.
             * @return  The substract of the two Dimensions.
             */
            Dimension3Di& operator-=(Dimension3Di& other) ;

            /**
             * Multiply a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to multiply the Dimension coordinates by.
             * @return  The result of the multiplication.
             */
            Dimension3Di& operator*=(const int& coeff) ;

            /**
             * Divide a Dimension by a scalar value and affect the result.
             * @param   coeff   The coeff to divide the Dimension coordinates by.
             * @return  The result of the division.
             */
            Dimension3Di& operator/=(const int& coeff) ;

            /**
             * Assignment operator to copy a Dimension.
             * @return  The current Dimension with the copied values.
             */
            Dimension3Di& operator=(const Dimension3Di& other) ;

            /**
             * Test if two Dimension have the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have the same size, FALSE else.
             */
            bool operator==(const Dimension3Di& other) const ;

            /**
             * Test if two Dimension have not the same size.
             * @param   other   An other Dimension to compare to the current one.
             * @return  TRUE if the Dimension have two different size, FALSE else.
             */
            bool operator!=(const Dimension3Di& other) const ;

            /**
             * Add a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w + b.w, a.h + b.h).
             */
            friend Dimension3Di operator+(const Dimension3Di& a, const Dimension3Di& b) ;

            /**
             * Substract a Dimension to another one.
             * @param   a   First Dimension.
             * @param   b   Second Dimension.
             * @return  Point at (a.w - b.w, a.h - b.h).
             */
            friend Dimension3Di operator-(const Dimension3Di& a, const Dimension3Di& b) ;

            /**
             * Multiply a Dimension by a scalar value (scale).
             * @param   p       Dimension to be multiplied.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w * coeff, d.h * coeff).
             */
            friend Dimension3Di operator*(const Dimension3Di& d, const int& coeff) ;

            /**
             * Divide a Dimension by a scalar value (scale).
             * @param   a       Dimension to be divided.
             * @param   coeff   Factor to scale the coordinates.
             * @return  Point at (d.w / coeff, d.h / coeff).
             */
            friend Dimension3Di operator/(const Dimension3Di& d, const int& coeff) ;

            /**
             * Echo the Dimension size on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   p   The Dimension to print.
             * @return  The stream with the printed Dimension size.
             */
            friend std::ostream& operator<<(std::ostream& s, const Dimension3Di& p) ;
    } ;
} ;

#endif
