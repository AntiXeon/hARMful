#ifndef __UNIT_TEST__MIND__RECTANGLE__
#define __UNIT_TEST__MIND__RECTANGLE__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing RectangleNDx.
     */
    class UTRectangle: public UnitTest {
        public:
            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of RectangleNDx objects.
             */
            virtual void allocation() = 0 ;

            /**
             * Test translation of RectangleNDx objects.
             */
            virtual void translation() = 0 ;

            /**
             * Test if a RectangleNDx contains other objects.
             */
            virtual void contain() = 0 ;

            /**
             * Test if a RectangleNDx intersects other objects.
             */
            virtual void intersect() = 0 ;

            /**
             * Test position of RectangleNDx objects.
             */
            virtual void position() = 0 ;

            /**
             * Test operators of RectangleNDx objects.
             */
            virtual void operators() = 0 ;
    } ;
}

#endif
