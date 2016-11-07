#ifndef __MIND_GEOMETRY_DIMENSION3DF__
#define __MIND_GEOMETRY_DIMENSION3DF__

#include <iostream>

#include <MINDTypes.h>
#include <geometry/points/Point3Df.h>
#include <geometry/dimensions/Dimension2Df.h>


namespace Mind {

    class Dimension2Df ;
    class Point3Df ;

    /**
    * @brief   A Dimension is used to get the size of an element, and so get the
    *          area of the element as a rectangle bounding shape.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Dimension3Df {
        private:
            /** @brief  Width of the Dimension2Df. */
            Scalar m_width ;

            /** @brief  Height of the Dimension2Df. */
            Scalar m_height ;

            /** @brief  Depth of the Dimension2Df. */
            Scalar m_depth ;


        public:
            /** @brief  Create a Dimension of zero by zero. */
            Dimension3Df() ;

            /**
            * @brief   Copy a Dimension object.
            * @param   copied  The Dimension to copy.
            */
            Dimension3Df(const Dimension3Df& copied) ;

            /**
            * @brief   Create a Dimension with the given sizes.
            * @param   width   Width to set the size of the element.
            * @param   height  Height to set the size of the element.
            * @param   depth   Depth to set the size of the element.
            */
            Dimension3Df(const Scalar& width, const Scalar& height, const Scalar& depth) ;

            /** @brief  Destroy the Dimension. */
            virtual ~Dimension3Df() ;


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

            /**
            * @brief   Get the depth of the dimension.
            * @return  The depth.
            */
            Scalar getDepth() const ;

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
            * @brief   Set the depth of the dimension.
            * @param   depth   Depth of the dimension.
            */
            void setDepth(const Scalar& depth) ;

            /**
            * @brief   Set the depth of the dimension.
            * @param   width   Width of the dimension.
            * @param   height  Height of the dimension.
            * @param   depth   Depth of the dimension.
            */
            void set(const Scalar& width, const Scalar& height, const Scalar& depth) ;


                                                             /*** OPERATORS ***/
            /** @brief  Conversion from Dimension3D to Point3D. */
            operator Point3Df() ;

            /** @brief  Conversion from Dimension3D to Dimension2D. */
            operator Dimension2Df() ;


            /**
            * @brief   Add a Dimension and affect the result.
            * @param   other   The other Dimension to add.
            * @return  The sum of the two Dimensions.
            */
            Dimension3Df& operator+=(Dimension3Df& other) ;

            /**
            * @brief   Substract a Dimension and affect the result.
            * @param   other   The other Dimension to substract.
            * @return  The substract of the two Dimensions.
            */
            Dimension3Df& operator-=(Dimension3Df& other) ;

            /**
            * @brief   Multiply a Dimension by a scalar value and affect the result.
            * @param   coeff   The coeff to multiply the Dimension coordinates by.
            * @return  The result of the multiplication.
            */
            Dimension3Df& operator*=(const Scalar& coeff) ;

            /**
            * @brief   Divide a Dimension by a scalar value and affect the result.
            * @param   coeff   The coeff to divide the Dimension coordinates by.
            * @return  The result of the division.
            */
            Dimension3Df& operator/=(const Scalar& coeff) ;


            /**
            * @brief   Assignment operator to copy a Dimension.
            * @return  The current Dimension with the copied values.
            */
            Dimension3Df& operator=(const Dimension3Df& other) ;

            /**
            * @brief   Test if two Dimension have the same size.
            * @param   other   An other Dimension to compare to the current one.
            * @return  TRUE if the Dimension have the same size, FALSE else.
            */
            bool operator==(const Dimension3Df& other) const ;

            /**
            * @brief   Test if two Dimension have not the same size.
            * @param   other   An other Dimension to compare to the current one.
            * @return  TRUE if the Dimension have two different size, FALSE else.
            */
            bool operator!=(const Dimension3Df& other) const ;



            /**
            * @brief   Add a Dimension to another one.
            * @param   a   First Dimension.
            * @param   b   Second Dimension.
            * @return  Point at (a.w + b.w, a.h + b.h).
            */
            friend Dimension3Df operator+(const Dimension3Df& a, const Dimension3Df& b) ;


            /**
            * @brief   Substract a Dimension to another one.
            * @param   a   First Dimension.
            * @param   b   Second Dimension.
            * @return  Point at (a.w - b.w, a.h - b.h).
            */
            friend Dimension3Df operator-(const Dimension3Df& a, const Dimension3Df& b) ;


            /**
            * @brief   Multiply a Dimension by a scalar value (scale).
            * @param   p       Dimension to be multiplied.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (d.w * coeff, d.h * coeff).
            */
            friend Dimension3Df operator*(const Dimension3Df& d, const Scalar& coeff) ;


            /**
            * @brief   Divide a Dimension by a scalar value (scale).
            * @param   a       Dimension to be divided.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (d.w / coeff, d.h / coeff).
            */
            friend Dimension3Df operator/(const Dimension3Df& d, const Scalar& coeff) ;


            /**
            * @brief   Echo the Dimension size on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The Dimension to print.
            * @return  The stream with the printed Dimension size.
            */
            friend std::ostream& operator<<(std::ostream& s, const Dimension3Df& p) ;
    } ;

} ;

#endif
