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
    } ;
}

#endif
