#ifndef __UNIT_TEST__MIND__MATRIX2D__
#define __UNIT_TEST__MIND__MATRIX2D__

#include <modules/matrices/UTMatrix.hpp>

namespace UTMind {
    /**
     * For testing Matrix2D.
     */
    class UTMatrix2D: public UTMatrix {
        public:
            /**
             * Instantation of the unit tests for Matrix2D.
             */
            UTMatrix2D() ;

            /**
             * Destruction of the unit tests for Matrix2D.
             */
            virtual ~UTMatrix2D() ;

        protected:
            /**
             * Test allocation of Matrix2D objects.
             */
            virtual void allocation() ;

            /**
             * Test utilities on Matrix2D objects.
             */
            virtual void utilities() ;
    } ;
}

 #endif
