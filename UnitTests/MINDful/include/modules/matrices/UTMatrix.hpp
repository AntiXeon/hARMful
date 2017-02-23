#ifndef __UNIT_TEST__MIND__MATRIX__
#define __UNIT_TEST__MIND__MATRIX__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing matrices.
     */
    class UTMatrix: public UnitTest {
        public:
            /**
             * Instantation of the unit tests for matrices.
             */
            UTMatrix() ;

            /**
             * Destruction of the unit tests for matrices.
             */
            virtual ~UTMatrix() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of matrices objects.
             */
            virtual void allocation() = 0 ;

            /**
             * Test utilities on matrices objects.
             */
            virtual void utilities() = 0 ;
    } ;
}

#endif
