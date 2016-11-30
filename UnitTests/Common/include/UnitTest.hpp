#ifndef __UNIT_TEST_ABSTRACT__
#define __UNIT_TEST_ABSTRACT__

/**
 * Interface to create classes for unit tests.
 */
class UnitTest {
    private:
        /**
         * Common value to all the unit tests that are run.
         * If at least one test fails, the whole session is a fail.
         */
        static int ValidatedUnitTestSession ;

        /**
         * Precision for floats comparison.
         */
        float m_epsilon ;

    public:
        /**
         * Instantiate a new UnitTest.
         * @param epsilon   Precision for floats comparison.
         */
        UnitTest(float epsilon = 1e-4f) ;

        /**
         * Destruction of the UnitTest instance.
         */
        virtual ~UnitTest() ;

        /**
         * Run the different tests.
         */
        virtual void runTests() = 0 ;

        /**
         * To know if the tests are successful.
         * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure.
         */
        static int Success() ;

    protected:
        /**
         * Test if the @a condition is TRUE.
         * @param   condition     The condition to check.
         * @warning Contrary to the assert macro from the C API, this method does not immediately stop the
         */
        void assert(bool condition) ;

        /**
         * Compare two float values and check if their difference is lower than
         * the epsilon of the test.
         * @param  a First value.
         * @param  b Second value.
         * @return   TRUE if the two float values are lower than the epsilon of
         *           the unit test. FALSE if the difference is higher.
         */
        bool compare(float a, float b) ;
} ;

#endif
