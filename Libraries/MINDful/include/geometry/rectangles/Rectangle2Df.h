#ifndef __MIND_GEOMETRY_RECTANGLE2DF__
#define __MIND_GEOMETRY_RECTANGLE2DF__


#include <iostream>

#include <Math.h>
#include <MINDTypes.h>
#include <geometry/points/Point2Df.h>
#include <geometry/lines/Line2Df.h>
#include <geometry/dimensions/Dimension2Df.h>


namespace Mind {

    class Line2Df ;

    /**
    * @brief   A Rectangle is an area defined by the location of its upper-left
    *          corner at (x, y) and its dimension (width, height).
    * @author  CB (c) 2014
    * @version 0.1     2014/05/27
    */
    class Rectangle2Df {
        public:
            /**
            * @brief   Bitmask that indicates that a point lies on a side of the
            *          Rectangle.
            */
            enum PointPosition {
                                PointInside    = 0,    // Point inside the rectangle
                                PointOnLeft    = 1,    // Point lies on the left
                                PointAbove     = 2,    // Point lies above
                                PointOnRight   = 4,    // Point lies on the right
                                PointBelow     = 8     // Point lies below
                               } ;


        private:
            /**
            *  @brief   To know if the boundaries of the Rectangle are computed
            *           relatively to its center.
            */
            bool m_isCentered ;

            /** @brief  Test if the size of the Rectangle has changed. */
            bool m_hasChanged ;

            /** @brief  Location of the bottom-left corner of the Rectangle. */
            Point2Df m_bottomLeftCorner ;

            /** @brief  Size of the rectangle. */
            Dimension2Df m_size ;

            /**
            * @brief   Location of the up right corner, cached to accelerate
            *          some computations.
            */
            Point2Df m_upRightCorner ;


        public:
            /** @brief  Create an empty Rectangle. */
            Rectangle2Df() ;

            /**
            * @brief   Copy a Rectangle.
            * @param   copied      The Rectangle to be copied.
            */
            Rectangle2Df(const Rectangle2Df& copied) ;

            /**
            * @brief   Create a Rectangle at the given position and with the given
            *          size.
            * @param   location    Location of the Rectangle.
            * @param   size        Size of the Rectangle.
            * @param   centered    If TRUE, the given location correspond to the
            *                      center of the Rectangle.
            *                      FALSE by default, so that the bottom-left
            *                      corner is set to the given location.
            */
            Rectangle2Df(
                         const Point2Df& location,
                         const Dimension2Df& size,
                         bool centered
                        ) ;

            /**
            * @brief   Create a Rectangle at the given position and with the given
            *          size.
            * @param   x           Coordinate on X axis.
            * @param   y           Coordinate on Y axis.
            * @param   w           Width.
            * @param   h           Height.
            * @param   centered    If TRUE, the given location correspond to the
            *                      center of the Rectangle.
            *                      If FALSE, the bottom-left corner is set to
            *                      the given location.
            */
            Rectangle2Df(
                         const Scalar& x,
                         const Scalar& y,
                         const Scalar& w,
                         const Scalar& h,
                         bool centered
                        ) ;

            /**
            * @brief   Create a Rectangle whose boundaries correspond to the
            *          given points.
            * @param   p1          First point of the boundaries.
            * @param   p2          Second point of the boundaries.
            */
            Rectangle2Df(const Point2Df& p1, const Point2Df& p2) ;

            /**
            * @brief   Create a Rectangle from the given boundaries.
            * @param   x1          Coordinate on X axis on first Point.
            * @param   y1          Coordinate on Y axis on first Point
            * @param   x2          Coordinate on X axis on second Point
            * @param   y2          Coordinate on Y axis on second Point
            */
            Rectangle2Df(
                         const Scalar& x1,
                         const Scalar& y1,
                         const Scalar& x2,
                         const Scalar& y2
                        ) ;

            /** @brief  Destroy the Rectangle. */
            virtual ~Rectangle2Df() ;


                                                             /*** UTILITIES ***/
            /**
            * @brief   Translate the rectangle on the X and the Y axis.
            * @param   x    Horizontal shift.
            * @param   y    Vertical shift.
            */
            void translate(const Scalar& x, const Scalar& y) ;

                                                                /** CONTAINS **/
            /**
            * @brief   Test if the given coordinate is inside the Line boundaries.
            * @param   x           oordinate on X axis.
            * @param   y           Coordinate on Y axis.
            * @return  FALSE because a line has no area.
            */
            bool contains(const Scalar& x, const Scalar& y) ;

            /**
            * @brief   Test if the given coordinate is inside the Rectangle
            *          boundaries.
            * @param   point       Point to test.
            * @return  FALSE because a line has no area.
            */
            bool contains(const Point2Df& point) ;

            /**
            * @brief   Test if the given shape is entirely inside the Rectangle
            *          boundaries.
            * @param   x           Coordinate on X axis.
            * @param   y           Coordinate on Y axis.
            * @param   w           Width.
            * @param   h           Height.
            * @return  FALSE because a line has no area.
            */
            bool contains(
                          const Scalar& x,
                          const Scalar& y,
                          const Scalar& w,
                          const Scalar& h
                         ) ;

            /**
            * @brief   Test if the given shape is entirely inside the Rectangle
            *          boundaries.
            * @param   boundaries  Boundaries of the shape to test.
            * @return  FALSE because a line has no area.
            */
            bool contains(Rectangle2Df& boundaries) ;


                                                              /** INTERSECTS **/
            /**
            * @brief   Test if the Rectangle intersects another one.
            * @param   x           Coordinate on X axis.
            * @param   y           Coordinate on Y axis.
            * @param   w           Width.
            * @param   h           Height.
            * @return  TRUE if the two Rectangles intersect, FALSE otherwise.
            */
            bool intersects(
                            const Scalar& x,
                            const Scalar& y,
                            const Scalar& w,
                            const Scalar& h
                           ) ;

            /**
            * @brief    Test if the Rectangle intersects a Line.
            * @param    line        The other Line to test.
            * @return   TRUE if the Rectangle and Line intersect, FALSE
            *           otherwise.
            */
            bool intersects(const Line2Df& line) ;

            /**
            * @brief    Test if the Rectangle intersects a shape throught its
            *           boundaries.
            * @param    boundaries  Boundaries to test.
            * @return   TRUE if the two shapes intersect, FALSE otherwise.
            */
            bool intersects(const Rectangle2Df& boundaries) ;



                                                        /** POINT COMPARISON **/
            /**
            * @brief   Determine where the given Point lies in respect of the
            *          Rectangle boundaries.
            * @param   x       X coordinate of the Point.
            * @param   y       Y coordinate of the Point.
            * @return  Bitmask of the positions where the Point is relatively to
            *          the Rectangle boundaries.
            */
            char position(const Scalar& x, const Scalar& y) ;

            /**
            * @brief   Determine where the given Point lies in respect of the
            *          Rectangle boundaries.
            * @param   p       The Point to test.
            * @return  Bitmask of the positions where the Point is relatively to
            *          the Rectangle boundaries.
            */
            char position(const Point2Df& p) ;



                                                               /*** GETTERS ***/
            /**
             * @brief   Get the X coordinate of the upper-left corner.
             * @return  Up left corner coordinate X.
             */
            Scalar getUpLeftCornerX() ;

            /**
             * @brief   Get the Y coordinate of the upper-left corner.
             * @return  Up left corner coordinate Y.
             */
            Scalar getUpLeftCornerY() ;

            /**
             * @brief   Get the X coordinate of the upper-right corner.
             * @return  Up right corner coordinate X.
             */
            Scalar getUpRightCornerX() ;

            /**
             * @brief   Get the Y coordinate of the upper-right corner.
             * @return  Up right corner coordinate Y.
             */
            Scalar getUpRightCornerY() ;

            /**
             * @brief   Get the X coordinate of the bottom-left corner.
             * @return  Bottom left corner coordinate X.
             */
            Scalar getBottomLeftCornerX() const ;

            /**
             * @brief   Get the Y coordinate of the bottom-left corner.
             * @return  Bottom left corner coordinate Y.
             */
            Scalar getBottomLeftCornerY() const ;

            /**
             * @brief   Get the X coordinate of the bottom-right corner.
             * @return  Bottom right corner coordinate X.
             */
            Scalar getBottomRightCornerX() ;

            /**
             * @brief   Get the Y coordinate of the bottom-right corner.
             * @return  Bottom right corner coordinate Y.
             */
            Scalar getBottomRightCornerY() ;

            /**
             * @brief   Get the dimension of the Rectangle.
             * @return  Dimension of the Rectangle2D.
             */
            const Dimension2Df& getSize() const ;

            /**
             * @brief   Get the width of the Rectangle.
             * @return  Width of the Rectangle2D.
             */
            Scalar getWidth() const ;

            /**
             * @brief   Get the height of the Rectangle.
             * @return  Height of the Rectangle2D.
             */
            Scalar getHeight() const ;

            /**
             * @brief   Test if the Rectangle is empty.
             * @return  TRUE if the Rectangle is empty (no width or height),
             *          FALSE otherwise.
             */
            bool isEmpty() const ;


                                                               /*** SETTERS ***/
            /** @brief  Set the X location of the upper-left corner. */
            void setX(const Scalar& x) ;

            /** @brief  Set the Y location of the upper-left corner. */
            void setY(const Scalar& y) ;

            /** @brief  Set the location of the upper-left corner. */
            void setAt(const Scalar& x, const Scalar& y) ;

            /** @brief  Set the width of the Rectangle. */
            void setWidth(const Scalar& width) ;

            /** @brief  Set the height of the Rectangle. */
            void setHeight(const Scalar& height) ;


        protected:
            /** @brief  Compute the bottom right corner that is cached. */
            void computeMaxPoint() ;


                                                             /*** OPERATORS ***/
        public:
            /**
            * @brief   Assignment operator to copy a Rectangle.
            * @return  The current Rectangle with the copied values.
            */
            Rectangle2Df& operator=(const Rectangle2Df& other) ;

            /**
            * @brief   Add a Point and affect the result.
            * @param   other   The Point to add.
            * @return  The smallest Rectangle including both the original Rectangle
            *          and the Point.
            */
            Rectangle2Df& operator+=(Point2Df& other) ;

            /**
            * @brief   Merge two Rectangles and affect the result.
            * @param   other   The Rectangle to add.
            * @return  The smallest Rectangle including the two Rectangles.
            */
            Rectangle2Df& operator+=(Rectangle2Df& other) ;

            /**
            * @brief   Test if two Rectangles are at the same position.
            * @param   other   An other Rectangle to compare to the current one.
            * @return  TRUE if the Rectangles are at the same position, FALSE else.
            */
            bool operator==(const Rectangle2Df& other) const ;

            /**
            * @brief   Test if two Rectangles are at two different positions.
            * @param   other   An other Rectangle to compare to the current one.
            * @return  TRUE if the Rectangles are at two different positions, FALSE
            *          else.
            */
            bool operator!=(const Rectangle2Df& other) const ;



            /**
            * @brief   Add a Point to the Rectangle.
            * @param   r   Rectangle to include a new Point.
            * @param   p   Point to insert into the Rectangle.
            * @return  The smallest Rectangle including both the original Rectangle and the
            *          added Point. If p was inside the previous Rectangle, the original
            *          Rectangle is returned.
            */
            friend Rectangle2Df operator+(Rectangle2Df& r, Point2Df& p) ;

            /**
            * @brief   Merge two Rectangles
            * @param   r1  First rectangle.
            * @param   r2  Second Rectangle.
            * @return  The smallest Rectangle including the two Rectangles.
            */
            friend Rectangle2Df operator+(Rectangle2Df& r1, Rectangle2Df& r2) ;

            /**
            * @brief   Echo the Rectangle2D coordinates on console.
            * @param   s   The stream in which print the formatted coordinates.
            * @param   r   The Rectangle2D to print.
            * @return  The stream with the printed Line coordinates.
            */
            friend std::ostream& operator<<(std::ostream& s, const Rectangle2Df& r) ;
    } ;

} ;

#endif
