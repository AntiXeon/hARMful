#ifndef __UNIT_TEST__MIND__DIMENSION2DI_EXTENSION__
#define __UNIT_TEST__MIND__DIMENSION2DI_EXTENSION__

#include <modules/UTDimension.hpp>

namespace UTMind {
    /**
     * For testing Dimension2Di.
     */
    class UTDimension2Di final: public UTDimension {
        public:
            /**
             * Instantation of the unit tests for Dimension2Di.
             */
            UTDimension2Di() ;

            /**
             * Destruction of the unit tests for Dimension2Di.
             */
            virtual ~UTDimension2Di() ;

        protected:
            /**
             * Test allocation of Dimension2Di objects.
             */
            virtual void allocation() final ;

            /**
             * Test scalar operations on Dimension2Di objects.
             */
            virtual void scalarOperations() final ;

            /**
             * Test operations involving different Dimension2Di objects.
             */
            virtual void dimensionsOperations() final ;

            /**
             * Test equality between different Dimension2Di objects.
             */
            virtual void equality() final ;

            /**
             * Test inequality between different Dimension2Di objects.
             */
            virtual void inequality() final ;

            /**
             * Test setting values in Dimension2Di.
             */
            virtual void setter() final ;

            /**
             * Test conversion to other types.
             */
            virtual void cast() final ;
    } ;
}

#endif
