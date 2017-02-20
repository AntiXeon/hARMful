#ifndef __UNIT_TEST__MIND__DIMENSION_EXTENSION__
#define __UNIT_TEST__MIND__DIMENSION_EXTENSION__

#include <UnitTest.hpp>

namespace UTMind {
    /**
     * For testing Dimension2Df, Dimension2Di, Dimension3Df and Dimension3Di.
     */
    class UTDimension: public UnitTest {
        public:
            /**
             * Instantation of the unit tests for DimensionNDx.
             */
            UTDimension() ;

            /**
             * Destruction of the unit tests for DimensionNDx.
             */
            virtual ~UTDimension() ;

            /**
             * Run the different tests.
             */
            void runTests() final ;

        protected:
            /**
             * Test allocation of DimensionNDx objects.
             */
            virtual void allocation() = 0 ;

            /**
             * Test scalar operations on DimensionNDx objects.
             */
            virtual void scalarOperations() = 0 ;

            /**
             * Test operations involving different DimensionNDx objects.
             */
            virtual void dimensionsOperations() = 0 ;

            /**
             * Test equality between different DimensionNDx objects.
             */
            virtual void equality() = 0 ;

            /**
             * Test inequality between different DimensionNDx objects.
             */
            virtual void inequality() = 0 ;

            /**
             * Test setting values in DimensionNDx.
             */
            virtual void setter() = 0 ;

            /**
             * Test conversion to other types.
             */
            virtual void cast() = 0 ;
    } ;
}

#endif
