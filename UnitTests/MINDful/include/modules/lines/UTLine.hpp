#ifndef __UNIT_TEST__MIND__LINE__
#define __UNIT_TEST__MIND__LINE__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing Line2Df and Line2Di.
     */
    class UTLine: public UnitTest {
        protected:
            /**
             * Represents a linear equation y = ax + b, with a being the slope
             * and b the y-intercept.
             */
            struct LinearEquation final {
                /**
                 * Slope or gradient of the line.
                 */
                float m_gradient ;

                /**
                 * Point at which the line crosses the y-axis.
                 */
                float m_yIntercept ;
            } ;

        public:
            /**
             * Instantation of the unit tests for Line2Dx.
             */
            UTLine() ;

            /**
             * Destruction of the unit tests for Line2Dx.
             */
            virtual ~UTLine() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of Line2Dx objects.
             */
            virtual void allocation() = 0 ;

            /**
             * Test utilities on Line2Dx objects.
             */
            virtual void utilities() = 0 ;

            /**
             * Test intersections on Line2Dx objects.
             */
            virtual void intersections() = 0 ;

            /**
             * Test distances between different Line2Dx objects.
             */
            virtual void distance() = 0 ;
    } ;
}

#endif
