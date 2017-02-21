#ifndef __UNIT_TEST__MIND__DIMENSION2DF__
#define __UNIT_TEST__MIND__DIMENSION2DF__

#include <modules/dimensions/UTDimension.hpp>

namespace UTMind {
    /**
     * For testing Dimension2Df.
     */
    class UTDimension2Df final: public UTDimension {
        public:
            /**
             * Instantation of the unit tests for Dimension2Df.
             */
            UTDimension2Df() ;

            /**
             * Destruction of the unit tests for Dimension2Df.
             */
            virtual ~UTDimension2Df() ;

        protected:
            /**
             * Test allocation of Dimension2Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test scalar operations on Dimension2Df objects.
             */
            virtual void scalarOperations() final ;

            /**
             * Test operations involving different Dimension2Df objects.
             */
            virtual void dimensionsOperations() final ;

            /**
             * Test equality between different Dimension2Df objects.
             */
            virtual void equality() final ;

            /**
             * Test inequality between different Dimension2Df objects.
             */
            virtual void inequality() final ;

            /**
             * Test setting values in Dimension2Df.
             */
            virtual void setter() final ;

            /**
             * Test conversion to other types.
             */
            virtual void cast() final ;
    } ;
}

#endif
