#ifndef __MIND_GEOMETRY_POINT3DI__
#define __MIND_GEOMETRY_POINT3DI__

#include <iostream>

#include <MINDTypes.h>
#include <simd/SIMDVector.h>
#include <geometry/points/Point2Di.h>
#include <geometry/dimensions/Dimension3Di.h>


namespace Mind {

    class Point2Di ;
    class Dimension3Di ;

    /**
    * @brief   A Point is a very simple element that can be used in a space to
    *          place elements, get distances between elements, etc.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Point3Di {
        private:
            /** @brief  Individual value of coordinate X. */
            int m_x ;

            /** @brief  Individual value of coordinate Y. */
            int m_y ;

            /** @brief  Individual value of coordinate Z. */
            int m_z ;

                                              /** CONSTRUCTION / DESTRUCTION **/
            /**
             * @brief   Create a Point3Di from a Vector4f.
             */
            Point3Di(const SIMD::Vector4i& values) ;

        public:
            /** @brief  Create a Point at the origin. */
            Point3Di() ;

            /**
            * @brief   Copy a Point.
            * @param   copied  The Point to copy.
            */
            Point3Di(const Point3Di& copied) ;

            /**
            * @brief   Create a Point at the given position.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            * @param   z   Coordinate on Z axis.
            */
            Point3Di(const int& x, const int& y, const int& z) ;

            /** @brief  Destroy the Point. */
            virtual ~Point3Di() ;


                                                             /*** UTILITIES ***/
            /**
            * @brief   Translate a point of the given offsets.
            * @param   x   Offset on X axis.
            * @param   y   Offset on Y axis.
            * @param   z   Offset on Z axis.
            */
            void translate(const int& x, const int& y, const int& z) ;

            /**
            * @brief   Translate a point of the given offsets.
            * @param   offset  Offset on the three axes.
            */
            void translate(const Point3Di& offset) ;

            /**
            * @brief   Dot product between the current Point and another one.
            * @param   other   Another Point to compute the dot product.
            * @return  The result of the dot product.
            */
            Scalar dot(const Point3Di& other) const ;

            /**
            * @brief   Cross product between the current Point and another one.
            *          The result is put in the current Point.
            * @param   other   Another Point to compute the cross product.
            */
            Point3Di cross(const Point3Di& other) const ;

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
            static Point3Di merge(const Point3Di& a, const Point3Di& b) ;


            /**
            * @brief   Get the distance between two points on X axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the X axis.
            */
            static int distanceX(const Point3Di& a, const Point3Di& b) ;

            /**
            * @brief   Get the distance between two points on Y axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the Y axis.
            */
            static int distanceY(const Point3Di& a, const Point3Di& b) ;

            /**
            * @brief   Get the distance between two points on Z axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the Z axis.
            */
            static int distanceZ(const Point3Di& a, const Point3Di& b) ;

            /**
            * @brief   Give the distance between two points.
            * @param a First point.
            * @param b Second point.
            * @return  Distance between A and B.
            */
            static Scalar distance(const Point3Di& a, const Point3Di& b) ;

            /**
             * @brief   Compute the length of a vector.
             * @return  The length of the vector.
             */
            Scalar length() ;



                                                               /*** GETTERS ***/
            /** @brief  Get the X coordinate. */
            int getX() const ;

            /** @brief  Get the Y coordinate. */
            int getY() const ;

            /** @brief  Get the Z coordinate. */
            int getZ() const ;

            /**
             * @brief   Get the coordinates of the Vector3f in an
             *          AlignedArray4f. The last index is set to zero.
             * @param   output  Output parameter that will contain the values.
             * @return  The @a output parameter for convenient use.
             */
            AlignedArray4i& getCoordinates(AlignedArray4i& output) const ;


                                                               /*** SETTERS ***/
            /** @brief  Set the X coordinate. */
            void setX(const int& x) ;

            /** @brief  Set the Y coordinate. */
            void setY(const int& y) ;

            /** @brief  Set the Z coordinate. */
            void setZ(const int& z) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            * @param   z   Coordinate on Z axis.
            */
            void set(const int& x, const int& y, const int& z) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   position    Position at which the point should be set.
            */
            void set(const Point3Di& position) ;


                                                             /*** OPERATORS ***/
            /** @brief  Conversion from Point3D to Dimension3D. */
            operator Dimension3Di() ;

            /** @brief  Conversion from Point3D to Point2D. */
            operator Point2Di() ;

            /**
            * @brief   Add a Point and affect the result.
            * @param   other   The other Point to add.
            * @return  The sum of the two Points.
            */
            Point3Di& operator+=(Point3Di& other) ;

            /**
            * @brief   Substract a Point and affect the result.
            * @param   other   The other Point to substract.
            * @return  The substract of the two Points.
            */
            Point3Di& operator-=(Point3Di& other) ;

            /**
            * @brief   Multiply a Point by a scalar value and affect the result.
            * @param   coeff   The coeff to multiply the Point coordinates by.
            * @return  The result of the multiplication.
            */
            Point3Di& operator*=(const int& coeff) ;

            /**
            * @brief   Divide a Point by a scalar value and affect the result.
            * @param   coeff   The coeff to divide the Point coordinates by.
            * @return  The result of the division.
            */
            Point3Di& operator/=(const int& coeff) ;


            /**
            * @brief   Assignment operator to copy a Point.
            * @return  The current Point with the copied values.
            */
            Point3Di& operator=(const Point3Di& other) ;

            /**
            * @brief   Test if two Points are at the same position.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at the same position, FALSE else.
            */
            bool operator==(const Point3Di& other) const ;

            /**
            * @brief   Test if two Points are at two different positions.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at two different positions, FALSE
            *          else.
            */
            bool operator!=(const Point3Di& other) const ;


            /**
             * @brief   Negate a Point3Di.
             * @param   a   The Point3Di to negate.
             * @return  Negated value of the @a a parameter.
             */
            friend Point3Di operator-(const Point3Di& a) ;

            /**
            * @brief   Add a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x + b.x, a.y + b.y).
            */
            friend Point3Di operator+(const Point3Di& a, const Point3Di& b) ;


            /**
            * @brief   Substract a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x - b.x, a.y - b.y).
            */
            friend Point3Di operator-(const Point3Di& a, const Point3Di& b) ;


            /**
            * @brief   Dot product of two Points (A.B).
            * @param   a   Point whose coordinates must be multiplied.
            * @param   b   Another Point to compute the dot product.
            * @return  Result of the dot product A.B.
            */
            friend int operator*(const Point3Di& a, const Point3Di& b) ;

            /**
            * @brief   Multiply a Point coordinates by a scalar value (scale).
            * @param   p       Point whose coordinates must be multiplied.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x * coeff, a.y * coeff).
            */
            friend Point3Di operator*(const Point3Di& p, const int& coeff) ;


            /**
            * @brief   Divide a Point coordinates by a scalar value (scale).
            * @param   a       Point whose coordinates must be divided.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x / coeff, a.y / coeff).
            */
            friend Point3Di operator/(const Point3Di& p, const int& coeff) ;


            /**
            * @brief   Echo the Point coordinates on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The Point to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(std::ostream& s, const Point3Di& p) ;
    } ;

    typedef Point3Di Vector3i ;

} ;


#endif
