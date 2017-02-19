#ifndef __MIND__GEOMETRY_RECTANGLE2DI__
#define __MIND__GEOMETRY_RECTANGLE2DI__

#include <iostream>

#include <Math.hpp>
#include <MINDTypes.hpp>
#include <geometry/points/Point2Di.hpp>
#include <geometry/lines/Line2Di.hpp>
#include <geometry/dimensions/Dimension2Di.hpp>

namespace Mind {
    class Line2Di ;

    /**
     * A Rectangle is an area defined by the location of its upper-left corner
     * at (x, y) and its dimension (width, height).
     */
    class Rectangle2Di {
        public:
            /**
             * Bitmask that indicates that a point lies on a side of the
             * Rectangle.
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
             *  To know if the boundaries of the Rectangle are computed
             *  relatively to its center.
             */
            bool m_isCentered ;

            /** Test if the size of the Rectangle has changed. */
            bool m_hasChanged ;

            /** Location of the bottom-left corner of the Rectangle. */
            Point2Di m_bottomLeftCorner ;

            /** Size of the rectangle. */
            Dimension2Di m_size ;

            /**
             * Location of the up right corner, cached to accelerate some
             * computations.
             */
            Point2Di m_upRightCorner ;


        public:
            /** Create an empty Rectangle. */
            Rectangle2Di() ;

            /**
             * Copy a Rectangle.
             * @param   copied      The Rectangle to be copied.
             */
            Rectangle2Di(const Rectangle2Di& copied) ;

            /**
             * Create a Rectangle at the given position and with the given size.
             * @param   location    Location of the Rectangle.
             * @param   size        Size of the Rectangle.
             * @param   centered    If TRUE, the given location correspond to the
             *                      center of the Rectangle.
             *                      FALSE by default, so that the bottom-left
             *                      corner is set to the given location.
             */
            Rectangle2Di(
                const Point2Di& location,
                const Dimension2Di& size,
                bool centered
            ) ;

            /**
             * Create a Rectangle at the given position and with the given size.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @param   centered    If TRUE, the given location correspond to
             *                      the center of the Rectangle.
             *                      If FALSE, the bottom-left corner is set to
             *                      the given location.
             */
            Rectangle2Di(
                const int& x,
                const int& y,
                const int& w,
                const int& h,
                bool centered
            ) ;

            /**
             * Create a Rectangle whose boundaries correspond to the
             *          given points.
             * @param   p1          First point of the boundaries.
             * @param   p2          Second point of the boundaries.
             */
            Rectangle2Di(const Point2Di& p1, const Point2Di& p2) ;

            /**
             * Create a Rectangle from the given boundaries.
             * @param   x1          Coordinate on X axis on first Point.
             * @param   y1          Coordinate on Y axis on first Point
             * @param   x2          Coordinate on X axis on second Point
             * @param   y2          Coordinate on Y axis on second Point
             */
            Rectangle2Di(
                const int& x1,
                const int& y1,
                const int& x2,
                const int& y2
            ) ;

            /** Destroy the Rectangle. */
            virtual ~Rectangle2Di() ;

            /**
             * Translate the rectangle on the X and the Y axis.
             * @param   x    Horizontal shift.
             * @param   y    Vertical shift.
             */
            void translate(const int& x, const int& y) ;

            /**
             * Test if the given coordinate is inside the Line boundaries.
             * @param   x           oordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @return  FALSE because a line has no area.
             */
            bool contains(const int& x, const int& y) ;

            /**
             * Test if the given coordinate is inside the Rectangle
             *          boundaries.
             * @param   point       Point to test.
             * @return  FALSE because a line has no area.
             */
            bool contains(const Point2Di& point) ;

            /**
             * Test if the given shape is entirely inside the Rectangle
             *          boundaries.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @return  FALSE because a line has no area.
             */
            bool contains(
                const int& x,
                const int& y,
                const int& w,
                const int& h
            ) ;

            /**
             * Test if the given shape is entirely inside the Rectangle
             *          boundaries.
             * @param   boundaries  Boundaries of the shape to test.
             * @return  FALSE because a line has no area.
             */
            bool contains(Rectangle2Di& boundaries) ;

            /**
             * Test if the Rectangle intersects another one.
             * @param   x           Coordinate on X axis.
             * @param   y           Coordinate on Y axis.
             * @param   w           Width.
             * @param   h           Height.
             * @return  TRUE if the two Rectangles intersect, FALSE otherwise.
             */
            bool intersects(
                const int& x,
                const int& y,
                const int& w,
                const int& h
            ) ;

            /**
             *  Test if the Rectangle intersects a Line.
             * @param    line        The other Line to test.
             * @return   TRUE if the Rectangle and Line intersect, FALSE
             *           otherwise.
             */
            bool intersects(const Line2Di& line) ;

            /**
             *  Test if the Rectangle intersects a shape throught its
             *           boundaries.
             * @param    boundaries  Boundaries to test.
             * @return   TRUE if the two shapes intersect, FALSE otherwise.
             */
            bool intersects(const Rectangle2Di& boundaries) ;

            /**
             * Determine where the given Point lies in respect of the
             *          Rectangle boundaries.
             * @param   x       X coordinate of the Point.
             * @param   y       Y coordinate of the Point.
             * @return  Bitmask of the positions where the Point is relatively
             *          to the Rectangle boundaries.
             */
            char position(const int& x, const int& y) ;

            /**
             * Determine where the given Point lies in respect of the
             *          Rectangle boundaries.
             * @param   p       The Point to test.
             * @return  Bitmask of the positions where the Point is relatively
             *          to the Rectangle boundaries.
             */
            char position(const Point2Di& p) ;

            /** Get the X coordinate of the upper-left corner. */
            int getUpLeftCornerX() ;

            /** Get the Y coordinate of the upper-left corner. */
            int getUpLeftCornerY() ;

            /** Get the X coordinate of the upper-right corner. */
            int getUpRightCornerX() ;

            /** Get the Y coordinate of the upper-right corner. */
            int getUpRightCornerY() ;

            /** Get the X coordinate of the bottom-left corner. */
            int getBottomLeftCornerX() const ;

            /** Get the Y coordinate of the bottom-left corner. */
            int getBottomLeftCornerY() const ;

            /** Get the X coordinate of the bottom-right corner. */
            int getBottomRightCornerX() ;

            /** Get the Y coordinate of the bottom-right corner. */
            int getBottomRightCornerY() ;

            /** Get the dimension of the Rectangle. */
            const Dimension2Di& getSize() const ;

            /** Get the width of the Rectangle. */
            int getWidth() const ;

            /** Get the height of the Rectangle. */
            int getHeight() const ;

            /** Test if the Rectangle is empty. */
            bool isEmpty() const ;

            /** Set the X location of the upper-left corner. */
            void setX(const int& x) ;

            /** Set the Y location of the upper-left corner. */
            void setY(const int& y) ;

            /** Set the location of the upper-left corner. */
            void setAt(const int& x, const int& y) ;

            /** Set the width of the Rectangle. */
            void setWidth(const int& width) ;

            /** Set the height of the Rectangle. */
            void setHeight(const int& height) ;

        protected:
            /** Compute the bottom right corner that is cached. */
            void computeMaxPoint() ;

        public:
            /**
             * Assignment operator to copy a Rectangle.
             * @return  The current Rectangle with the copied values.
             */
            Rectangle2Di& operator=(const Rectangle2Di& other) ;

            /**
             * Add a Point and affect the result.
             * @param   other   The Point to add.
             * @return  The smallest Rectangle including both the original
             *          Rectangle and the Point.
             */
            Rectangle2Di& operator+=(Point2Di& other) ;

            /**
             * Merge two Rectangles and affect the result.
             * @param   other   The Rectangle to add.
             * @return  The smallest Rectangle including the two Rectangles.
             */
            Rectangle2Di& operator+=(Rectangle2Di& other) ;

            /**
             * Test if two Rectangles are at the same position.
             * @param   other   An other Rectangle to compare to the current
             *                  one.
             * @return  TRUE if the Rectangles are at the same position, FALSE
             *          else.
             */
            bool operator==(const Rectangle2Di& other) const ;

            /**
             * Test if two Rectangles are at two different positions.
             * @param   other   An other Rectangle to compare to the current one.
             * @return  TRUE if the Rectangles are at two different positions,
             *          FALSE else.
             */
            bool operator!=(const Rectangle2Di& other) const ;

            /**
             * Add a Point to the Rectangle.
             * @param   r   Rectangle to include a new Point.
             * @param   p   Point to insert into the Rectangle.
             * @return  The smallest Rectangle including both the original
             *          Rectangle and the added Point. If p was inside the
             *          previous Rectangle, the original Rectangle is returned.
             */
            friend Rectangle2Di operator+(Rectangle2Di& r, Point2Di& p) ;

            /**
             * Merge two Rectangles
             * @param   r1  First rectangle.
             * @param   r2  Second Rectangle.
             * @return  The smallest Rectangle including the two Rectangles.
             */
            friend Rectangle2Di operator+(Rectangle2Di& r1, Rectangle2Di& r2) ;

            /**
             * Echo the Rectangle2D coordinates on console.
             * @param   s   The stream in which print the formatted coordinates.
             * @param   r   The Rectangle2D to print.
             * @return  The stream with the printed Line coordinates.
             */
            friend std::ostream& operator<<(std::ostream& s, const Rectangle2Di& r) ;
    } ;
} ;

#endif
