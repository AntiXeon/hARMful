#ifndef __UNIT_TEST__MIND__POINT2DI__
#define __UNIT_TEST__MIND__POINT2DI__

#include <UnitTest.hpp>
#include <modules/points/UTPoint.hpp>

namespace UTMind {
    /**
     * For testing Point2Di.
     */
    class UTPoint2Di final: public UTPoint {
        public:
            /**
             * Instantation of the unit tests for Point2Di.
             */
            UTPoint2Di() ;

            /**
             * Destruction of the unit tests for Point2Di.
             */
            virtual ~UTPoint2Di() ;

        protected:
            /**
             * Test allocation of Point2Di objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Point2Di objects.
             */
            virtual void utilities() final ;
    } ;
}

#endif
