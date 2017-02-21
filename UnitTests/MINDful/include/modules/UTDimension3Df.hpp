#ifndef __UNIT_TEST__MIND__DIMENSION3DF_EXTENSION__
#define __UNIT_TEST__MIND__DIMENSION3DF_EXTENSION__

#include <modules/UTDimension.hpp>

namespace UTMind {
    /**
     * For testing Dimension3Df.
     */
    class UTDimension3Df final: public UTDimension {
        public:
            /**
             * Instantation of the unit tests for Dimension3Df.
             */
            UTDimension3Df() ;

            /**
             * Destruction of the unit tests for Dimension3Df.
             */
            virtual ~UTDimension3Df() ;

        protected:
            /**
             * Test allocation of Dimension3Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test scalar operations on Dimension3Df objects.
             */
            virtual void scalarOperations() final ;

            /**
             * Test operations involving different Dimension3Df objects.
             */
            virtual void dimensionsOperations() final ;

            /**
             * Test equality between different Dimension3Df objects.
             */
            virtual void equality() final ;

            /**
             * Test inequality between different Dimension3Df objects.
             */
            virtual void inequality() final ;

            /**
             * Test setting values in Dimension3Df.
             */
            virtual void setter() final ;

            /**
             * Test conversion to other types.
             */
            virtual void cast() final ;
    } ;
}

#endif
