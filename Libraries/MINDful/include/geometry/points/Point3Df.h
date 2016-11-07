#ifndef __MIND_GEOMETRY_POINT3DF__
#define __MIND_GEOMETRY_POINT3DF__

#include <iostream>

#include <MINDTypes.h>
#include <simd/SIMDVector.h>
#include <geometry/points/Point2Df.h>
#include <geometry/dimensions/Dimension3Df.h>


namespace Mind {

    class Point2Df ;
    class Dimension3Df ;

    /**
    * @brief   A Point is a very simple element that can be used in a space to
    *          place elements, get distances between elements, etc.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Point3Df {
        private:
            #ifdef USE_NO_SIMD
                /** @brief  Individual value of coordinate X. */
                Scalar m_x ;

                /** @brief  Individual value of coordinate Y. */
                Scalar m_y ;

                /** @brief  Individual value of coordinate Z. */
                Scalar m_z ;
            #else
                /** @brief  Values of the Point3Df. */
                SIMD::Vector4f m_values ;

                                              /** CONSTRUCTION / DESTRUCTION **/
                /**
                 * @brief   Create a Point3Df from a Vector4f.
                 */
                Point3Df(const SIMD::Vector4f& values) ;
            #endif

        public:
            /** @brief  Create a Point at the origin. */
            Point3Df() ;

            /**
            * @brief   Copy a Point.
            * @param   copied  The Point to copy.
            */
            Point3Df(const Point3Df& copied) ;

            /**
            * @brief   Create a Point at the given position.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            * @param   z   Coordinate on Z axis.
            */
            Point3Df(const Scalar& x, const Scalar& y, const Scalar& z) ;

            /** @brief  Destroy the Point. */
            virtual ~Point3Df() ;


                                                             /*** UTILITIES ***/
            /**
            * @brief   Translate a point of the given offsets.
            * @param   x   Offset on X axis.
            * @param   y   Offset on Y axis.
            * @param   z   Offset on Z axis.
            */
            void translate(const Scalar& x, const Scalar& y, const Scalar& z) ;

            /**
            * @brief   Translate a point of the given offsets.
            * @param   offset  Offset on the three axes.
            */
            void translate(const Point3Df& offset) ;

            /**
            * @brief   Dot product between the current Point and another one.
            * @param   other   Another Point to compute the dot product.
            * @return  The result of the dot product.
            */
            Scalar dot(const Point3Df& other) const ;

            /**
            * @brief   Cross product between the current Point and another one.
            *          The result is put in the current Point.
            * @param   other   Another Point to compute the cross product.
            */
            Point3Df cross(const Point3Df& other) const ;

            /**
            * @brief   Normalize the coordinates of the Point so that they are
            *          defined in [0, 1].
            */
            void normalize() ;

            /**
            * @brief   Merge two points at a middle point.
            * @param a The first point to merge.
            * @param b The second point to merge.
            * @return  The merged point at the center between both given points.
            */
            static Point3Df merge(const Point3Df& a, const Point3Df& b) ;


            /**
            * @brief   Get the distance between two points on X axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the X axis.
            */
            static Scalar distanceX(const Point3Df& a, const Point3Df& b) ;

            /**
            * @brief   Get the distance between two points on Y axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the Y axis.
            */
            static Scalar distanceY(const Point3Df& a, const Point3Df& b) ;

            /**
            * @brief   Get the distance between two points on Z axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the Z axis.
            */
            static Scalar distanceZ(const Point3Df& a, const Point3Df& b) ;

            /**
            * @brief   Give the distance between two points.
            * @param a First point.
            * @param b Second point.
            * @return  Distance between A and B.
            */
            static Scalar distance(const Point3Df& a, const Point3Df& b) ;

            /**
             * @brief   Compute the length of a vector.
             * @return  The length of the vector.
             */
            Scalar length() ;



                                                               /*** GETTERS ***/
            /** @brief  Get the X coordinate. */
            Scalar getX() const ;

            /** @brief  Get the Y coordinate. */
            Scalar getY() const ;

            /** @brief  Get the Z coordinate. */
            Scalar getZ() const ;

            /**
             * @brief   Get the coordinates of the Vector3f in an
             *          AlignedArray4f. The last index is set to zero.
             * @param   output  Output parameter that will contain the values.
             * @return  The @a output parameter for convenient use.
             */
            AlignedArray4f& getCoordinates(AlignedArray4f& output) const ;

                                                               /*** SETTERS ***/
            /** @brief  Set the X coordinate. */
            void setX(const Scalar& x) ;

            /** @brief  Set the Y coordinate. */
            void setY(const Scalar& y) ;

            /** @brief  Set the Z coordinate. */
            void setZ(const Scalar& z) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            * @param   z   Coordinate on Z axis.
            */
            void set(const Scalar& x, const Scalar& y, const Scalar& z) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   position    Position at which the point should be set.
            */
            void set(const Point3Df& position) ;


                                                             /*** OPERATORS ***/
            /** @brief  Conversion from Point3D to Dimension3D. */
            operator Dimension3Df() ;

            /** @brief  Conversion from Point3D to Point2D. */
            operator Point2Df() ;

            /**
            * @brief   Add a Point and affect the result.
            * @param   other   The other Point to add.
            * @return  The sum of the two Points.
            */
            Point3Df& operator+=(Point3Df& other) ;

            /**
            * @brief   Substract a Point and affect the result.
            * @param   other   The other Point to substract.
            * @return  The substract of the two Points.
            */
            Point3Df& operator-=(Point3Df& other) ;

            /**
            * @brief   Multiply a Point by a scalar value and affect the result.
            * @param   coeff   The coeff to multiply the Point coordinates by.
            * @return  The result of the multiplication.
            */
            Point3Df& operator*=(const Scalar& coeff) ;

            /**
            * @brief   Divide a Point by a scalar value and affect the result.
            * @param   coeff   The coeff to divide the Point coordinates by.
            * @return  The result of the division.
            */
            Point3Df& operator/=(const Scalar& coeff) ;


            /**
            * @brief   Assignment operator to copy a Point.
            * @return  The current Point with the copied values.
            */
            Point3Df& operator=(const Point3Df& other) ;

            /**
            * @brief   Test if two Points are at the same position.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at the same position, FALSE else.
            */
            bool operator==(const Point3Df& other) const ;

            /**
            * @brief   Test if two Points are at two different positions.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at two different positions, FALSE
            *          else.
            */
            bool operator!=(const Point3Df& other) const ;


            /**
             * @brief   Negate the coordinates of the point.
             * @param   p   The point to negate.
             * @return  The negate version of the point @a p.
             */
            friend Point3Df operator-(const Point3Df& p) ;

            /**
            * @brief   Add a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x + b.x, a.y + b.y).
            */
            friend Point3Df operator+(const Point3Df& a, const Point3Df& b) ;


            /**
            * @brief   Substract a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x - b.x, a.y - b.y).
            */
            friend Point3Df operator-(const Point3Df& a, const Point3Df& b) ;


            /**
            * @brief   Dot product of two Points (A.B).
            * @param   a   Point whose coordinates must be multiplied.
            * @param   b   Another Point to compute the dot product.
            * @return  Result of the dot product A.B.
            */
            friend Scalar operator*(const Point3Df& a, const Point3Df& b) ;

            /**
            * @brief   Multiply a Point coordinates by a scalar value (scale).
            * @param   p       Point whose coordinates must be multiplied.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x * coeff, a.y * coeff).
            */
            friend Point3Df operator*(const Point3Df& p, const Scalar& coeff) ;


            /**
            * @brief   Divide a Point coordinates by a scalar value (scale).
            * @param   a       Point whose coordinates must be divided.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x / coeff, a.y / coeff).
            */
            friend Point3Df operator/(const Point3Df& p, const Scalar& coeff) ;


            /**
            * @brief   Echo the Point coordinates on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The Point to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(std::ostream& s, const Point3Df& p) ;
    } ;

    typedef Point3Df Vector3f ;

} ;


#endif
