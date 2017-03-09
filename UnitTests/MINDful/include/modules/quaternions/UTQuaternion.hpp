#ifndef __UNIT_TEST__MIND__QUATERNION__
#define __UNIT_TEST__MIND__QUATERNION__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing Quaternion.
     */
    class UTQuaternion: public UnitTest {
        public:
            /**
             * Instantation of the unit tests for Quaternion.
             */
            UTQuaternion() ;

            /**
             * Destruction of the unit tests for Quaternion.
             */
            virtual ~UTQuaternion() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of Quaternion objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Quaternion objects.
             */
            virtual void utilities() final ;

            /**
             * Test operators on Quaternion objects.
             */
            virtual void operators() final ;
    } ;
}

#endif
