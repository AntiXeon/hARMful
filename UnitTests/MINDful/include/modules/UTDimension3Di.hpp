#ifndef __UNIT_TEST__MIND__DIMENSION3DI_EXTENSION__
#define __UNIT_TEST__MIND__DIMENSION3DI_EXTENSION__

#include <modules/UTDimension.hpp>

namespace UTMind {
    /**
     * For testing Dimension3Di.
     */
    class UTDimension3Di final: public UTDimension {
        public:
            /**
             * Instantation of the unit tests for Dimension3Di.
             */
            UTDimension3Di() ;

            /**
             * Destruction of the unit tests for Dimension3Di.
             */
            virtual ~UTDimension3Di() ;

        protected:
            /**
             * Test allocation of Dimension3Di objects.
             */
            virtual void allocation() final ;

            /**
             * Test scalar operations on Dimension3Di objects.
             */
            virtual void scalarOperations() final ;

            /**
             * Test operations involving different Dimension3Di objects.
             */
            virtual void dimensionsOperations() final ;

            /**
             * Test equality between different Dimension3Di objects.
             */
            virtual void equality() final ;

            /**
             * Test inequality between different Dimension3Di objects.
             */
            virtual void inequality() final ;

            /**
             * Test setting values in Dimension3Di.
             */
            virtual void setter() final ;

            /**
             * Test conversion to other types.
             */
            virtual void cast() final ;
    } ;
}

#endif
