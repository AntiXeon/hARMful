#ifndef __UNIT_TEST__MIND__POINT2DF__
#define __UNIT_TEST__MIND__POINT2DF__

#include <UnitTest.hpp>
#include <modules/points/UTPoint.hpp>

namespace UTMind {
    /**
     * For testing Point2Df.
     */
    class UTPoint2Df final: public UTPoint {
        protected:
            /**
             * Test allocation of Point2Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Point2Df objects.
             */
            virtual void utilities() final ;
    } ;
}

#endif
