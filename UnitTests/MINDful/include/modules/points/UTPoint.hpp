#ifndef __UNIT_TEST__MIND__POINT__
#define __UNIT_TEST__MIND__POINT__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing Point2Df and Point2Di.
     */
    class UTPoint: public UnitTest {
        public:
            /**
             * Instantation of the unit tests for PointNDx.
             */
            UTPoint() ;

            /**
             * Destruction of the unit tests for PointNDx.
             */
            virtual ~UTPoint() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of PointNDx objects.
             */
            virtual void allocation() = 0 ;

            /**
             * Test utilities on PointNDx objects.
             */
            virtual void utilities() = 0 ;
    } ;
}

#endif
