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
    } ;
}

#endif
