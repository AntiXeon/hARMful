#ifndef __MIND_GEOMETRY_POINT2DI__
#define __MIND_GEOMETRY_POINT2DI__

#include <iostream>

#include <MINDTypes.h>
#include <simd/SIMDVector.h>
#include <geometry/points/Point3Di.h>
#include <geometry/dimensions/Dimension2Di.h>


namespace Mind {

    class Dimension2Di ;
    class Point3Di ;

    /**
    * @brief   A Point is a very simple element that can be used in a space to
    *          place elements, get distances between elements, etc.
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Point2Di {
        private:
            /** @brief  Individual value of coordinate X. */
            int m_x ;

            /** @brief  Individual value of coordinate Y. */
            int m_y ;

                                              /** CONSTRUCTION / DESTRUCTION **/


        public:
            /** @brief  Create a Point at the origin. */
            Point2Di() ;

            /**
            * @brief   Copy a Point.
            * @param   copied  The Point to copy.
            */
            Point2Di(const Point2Di& copied) ;

            /**
            * @brief   Create a Point at the given position.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            */
            Point2Di(const int& x, const int& y) ;

            /** @brief  Destroy the Point. */
            virtual ~Point2Di() ;


                                                             /*** UTILITIES ***/
            /**
            * @brief   Translate a point of the given offsets.
            * @param   x   Offset on X axis.
            * @param   y   Offset on Y axis.
            */
            void translate(const int& x, const int& y) ;

            /**
            * @brief   Translate a point of the given offsets.
            * @param   offset  Offset on the two axes.
            */
            void translate(const Point2Di& offset) ;

            /**
            * @brief   Dot product between the current Point and another one.
            * @param   other   Another Point to compute the dot product.
            * @return  The result of the dot product.
            */
            int dot(const Point2Di& other) const ;


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
            static Point2Di merge(const Point2Di& a, const Point2Di& b) ;


            /**
            * @brief   Get the distance between two points on X axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the X axis.
            */
            static int distanceX(const Point2Di& a, const Point2Di& b) ;

            /**
            * @brief   Get the distance between two points on Y axis.
            * @param a First point.
            * @param b Second point.
            * @return  The distance between the points on the Y axis.
            */
            static int distanceY(const Point2Di& a, const Point2Di& b) ;


            /**
            * @brief   Give the distance between two points.
            * @param a First point.
            * @param b Second point.
            * @return  Distance between A and B.
            */
            static Scalar distance(const Point2Di& a, const Point2Di& b) ;

            /**
             * @brief   Compute the length of a vector.
             * @return  The length of the vector.
             */
            Scalar length() ;

            /**
            * @brief   Compute the angle at the center of three points.
            *          Use the cosinus law:<br/>
            *          Angle at C = arccos((A² + B² - C²) / (2AB))
            * @param b First point of the angle.
            * @param c Center oint where is computed the angle.
            * @param d Third point of the angle.
            * @return  The angle in degrees at point C.
            */
            static Scalar angle(
                                const Point2Di& b,
                                const Point2Di& c,
                                const Point2Di& d
                               ) ;


            /**
            * @brief   Get the orientation of the angle at the center of three
            *          points.
            * @param b First point of the angle.
            * @param c Center oint where is computed the angle.
            * @param d Third point of the angle.
            * @return  The orientation of the angle at point B.
            */
            static int angleOrientation(
                                        const Point2Di& a,
                                        const Point2Di& b,
                                        const Point2Di& c
                                       ) ;



                                                               /*** GETTERS ***/
            /** @brief  Get the X coordinate. */
            int getX() const ;

            /** @brief  Get the Y coordinate. */
            int getY() const ;

            /**
             * @brief   Get the coordinates of the Vector3f in an
             *          AlignedArray4f. The last indices are set to zero.
             * @param   output  Output parameter that will contain the values.
             * @return  The @a output parameter for convenient use.
             */
            AlignedArray4f& getCoordinates(AlignedArray4f& output) const ;

                                                               /*** SETTERS ***/
            /** @brief  Set the X coordinate. */
            void setX(const int& x) ;

            /** @brief  Set the Y coordinate. */
            void setY(const int& y) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   x   Coordinate on X axis.
            * @param   y   Coordinate on Y axis.
            */
            void set(const int& x, const int& y) ;

            /**
            * @brief   Move the point to the specified coordinates.
            * @param   position    Position at which the point should be set.
            */
            void set(const Point2Di& position) ;


                                                             /*** OPERATORS ***/
            /** @brief  Conversion from Point2D to Dimension2D. */
            operator Dimension2Di() ;

            /** @brief  Conversion from Point2D to Point3D. */
            operator Point3Di() ;



            /**
            * @brief   Add a Point and affect the result.
            * @param   other   The other Point to add.
            * @return  The sum of the two Points.
            */
            Point2Di& operator+=(Point2Di& other) ;

            /**
            * @brief   Substract a Point and affect the result.
            * @param   other   The other Point to substract.
            * @return  The substract of the two Points.
            */
            Point2Di& operator-=(Point2Di& other) ;

            /**
            * @brief   Multiply a Point by a int value and affect the result.
            * @param   coeff   The coeff to multiply the Point coordinates by.
            * @return  The result of the multiplication.
            */
            Point2Di& operator*=(const int& coeff) ;

            /**
            * @brief   Divide a Point by a int value and affect the result.
            * @param   coeff   The coeff to divide the Point coordinates by.
            * @return  The result of the division.
            */
            Point2Di& operator/=(const int& coeff) ;


            /**
            * @brief   Assignment operator to copy a Point.
            * @return  The current Point with the copied values.
            */
            Point2Di& operator=(const Point2Di& other) ;

            /**
            * @brief   Test if two Points are at the same position.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at the same position, FALSE else.
            */
            bool operator==(const Point2Di& other) const ;

            /**
            * @brief   Test if two Points are at two different positions.
            * @param   other   An other Point to compare to the current one.
            * @return  TRUE if the Points are at two different positions, FALSE
            *          else.
            */
            bool operator!=(const Point2Di& other) const ;



            /**
             * @brief   Negate a Point2Di.
             * @param   a   The Point2Di to negate.
             * @return  Negated value of the @a a parameter.
             */
            friend Point2Di operator-(const Point2Di& a) ;

            /**
            * @brief   Add a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x + b.x, a.y + b.y).
            */
            friend Point2Di operator+(const Point2Di& a, const Point2Di& b) ;

            /**
            * @brief   Substract a Point coordinates to another ones.
            * @param   a   First Point.
            * @param   b   Second Point.
            * @return  Point at (a.x - b.x, a.y - b.y).
            */
            friend Point2Di operator-(const Point2Di& a, const Point2Di& b) ;

            /**
            * @brief   Dot product of two Points (A.B).
            * @param   a   Point whose coordinates must be multiplied.
            * @param   b   Another Point to compute the dot product.
            * @return  Result of the dot product A.B.
            */
            friend int operator*(const Point2Di& a, const Point2Di& b) ;

            /**
            * @brief   Multiply a Point coordinates by a int value (scale).
            * @param   p       Point whose coordinates must be multiplied.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x * coeff, a.y * coeff).
            */
            friend Point2Di operator*(const Point2Di& p, const int& coeff) ;

            /**
            * @brief   Divide a Point coordinates by a int value (scale).
            * @param   a       Point whose coordinates must be divided.
            * @param   coeff   Factor to scale the coordinates.
            * @return  Point at (a.x / coeff, a.y / coeff).
            */
            friend Point2Di operator/(const Point2Di& p, const int& coeff) ;

            /**
            * @brief   Echo the Point coordinates on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   p   The Point to print.
            * @return  The stream with the printed Point coordinates.
            */
            friend std::ostream& operator<<(std::ostream& s, const Point2Di& p) ;
    } ;

    typedef Point2Di Vector2i ;

} ;

#endif
