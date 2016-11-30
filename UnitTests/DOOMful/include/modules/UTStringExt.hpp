#ifndef __UNIT_TEST__DOOM__STRING_EXTENSION__
#define __UNIT_TEST__DOOM__STRING_EXTENSION__

#include <UnitTest.hpp>

namespace UTDoom {
    /**
     * For testing StringExt.
     */
    class UTStringExt final: public UnitTest {
        public:
            /**
             * Instantation of the unit tests for StringExt.
             */
            UTStringExt() ;

            /**
             * Destruction of the unit tests for StringExt.
             */
            virtual ~UTStringExt() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        private:
            /**
             * Test the change of letter case in strings.
             */
            void changeCase() ;

            /**
             * Test splitting strings.
             */
            void split() ;

            /**
             * Test the conversion from a number to a string.
             */
            void numberToString() ;

            /**
             * Test the generation of random strings.
             */
            void random() ;
    } ;
}

#endif
