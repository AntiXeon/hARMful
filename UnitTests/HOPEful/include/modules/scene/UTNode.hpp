#ifndef __UNIT_TEST__HOPE__NODE__
#define __UNIT_TEST__HOPE__NODE__

#include <UnitTest.hpp>

namespace UTHope {
    /**
     * For testing Node.
     */
    class UTNode: public UnitTest {
        public:
            /**
             * Run the different tests.
             */
            void runTests() final ;

        private:
            /**
             * Test the relationship between nodes.
             */
            void relationship() ;
    } ;
}

#endif
