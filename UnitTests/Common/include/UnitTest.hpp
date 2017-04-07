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
         * Amount of tests that have run.
         */
        static unsigned int AmountRunTests ;

        /**
         * Amount of tests that have been successful.
         */
        static unsigned int AmountSuccessfulTests ;

    public:
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
         * Check if the @a condition is TRUE.
         * @param condition The condition to check.
         * @param file      File that is calling the assert method.
         * @param function  Function that is calling the assert method.
         * @param line      Line at which the assert method is called.
         */
        void checkCondition(
            const bool condition,
            const char* file,
            const char* function,
            const int line
        ) ;

        /**
         * Compare two float values and check if their difference is lower than
         * the epsilon of the test.
         * @param  a        First value.
         * @param  b        Second value.
         * @param  epsilon  Maximal distance between the two values.
         * @return   TRUE if the two float values are lower than the epsilon of
         *           the unit test. FALSE if the difference is higher.
         */
        bool compare(
            const float a,
            const float b,
            const float epsilon = 1e-6f
        ) ;
} ;

/**
 * This macro is to be used into an inherited class.
 * @param  condition The condition to check.
 */
#define check(condition) checkCondition(condition, __FILE__, __func__, __LINE__)

#endif
