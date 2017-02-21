#ifndef __UNIT_TEST__MIND__LINE2DI__
#define __UNIT_TEST__MIND__LINE2DI__

#include <UnitTest.hpp>
#include <modules/lines/UTLine.hpp>
#include <geometry/lines/Line2Di.hpp>
#include <geometry/points/Point2Di.hpp>

namespace UTMind {
    /**
     * For testing Line2Di.
     */
    class UTLine2Di final: public UTLine {
        public:
            /**
             * Instantation of the unit tests for Line2Di.
             */
            UTLine2Di() ;

            /**
             * Destruction of the unit tests for Line2Di.
             */
            virtual ~UTLine2Di() ;

        protected:
            /**
             * Test allocation of Line2Di objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Line2Di objects.
             */
            virtual void utilities() final ;

            /**
             * Test intersections on Line2Di objects.
             */
            virtual void intersections() final ;

            /**
             * Test distances between different Line2Di objects.
             */
            virtual void distance() final ;

            /**
             * Get the equation of a @a line from its points.
             * @param  line The line for which the equation is wanted.
             * @return      The linear equation of the @a line.
             */
            LinearEquation getEquation(const Mind::Line2Di& line) ;

            /**
             * Compute the distance between a @a line and a @a point.
             * This computation uses a different way to get the distance from
             * the one implemented in the library. It is used to compare by both
             * that the provided results match.
             * @param  line  The provided line.
             * @param  point The point to know its distance from the @a line.
             * @return       The distance between the @a line and the @a point.
             */
            float pointDistance(const Mind::Line2Di& line, const Mind::Point2Di& point) ;
    } ;
}

#endif
