#ifndef __UNIT_TEST__MIND__DIMENSION3DF__
#define __UNIT_TEST__MIND__DIMENSION3DF__

#include <modules/dimensions/UTDimension.hpp>

namespace UTMind {
    /**
     * For testing Dimension3Df.
     */
    class UTDimension3Df final: public UTDimension {
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
