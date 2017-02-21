#ifndef __UNIT_TEST__MIND__LINE2DF__
#define __UNIT_TEST__MIND__LINE2DF__

#include <UnitTest.hpp>
#include <modules/lines/UTLine.hpp>
#include <geometry/lines/Line2Df.hpp>
#include <geometry/points/Point2Df.hpp>

namespace UTMind {
    /**
     * For testing Line2Df.
     */
    class UTLine2Df final: public UTLine {
        public:
            /**
             * Instantation of the unit tests for Line2Df.
             */
            UTLine2Df() ;

            /**
             * Destruction of the unit tests for Line2Df.
             */
            virtual ~UTLine2Df() ;

        protected:
            /**
             * Test allocation of Line2Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Line2Df objects.
             */
            virtual void utilities() final ;

            /**
             * Test intersections on Line2Df objects.
             */
            virtual void intersections() final ;

            /**
             * Test distances between different Line2Df objects.
             */
            virtual void distance() final ;

            /**
             * Get the equation of a @a line from its points.
             * @param  line The line for which the equation is wanted.
             * @return      The linear equation of the @a line.
             */
            LinearEquation getEquation(const Mind::Line2Df& line) ;

            /**
             * Compute the distance between a @a line and a @a point.
             * @param  line  The provided line.
             * @param  point The point to know its distance from the @a line.
             * @return       The distance between the @a line and the @a point.
             */
            float pointDistance(const Mind::Line2Df& line, const Mind::Point2Df& point) ;
    } ;
}

#endif
