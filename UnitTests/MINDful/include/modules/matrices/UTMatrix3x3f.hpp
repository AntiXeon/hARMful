#ifndef __UNIT_TEST__MIND__MATRIX3X3F__
#define __UNIT_TEST__MIND__MATRIX3X3F__

#include <modules/matrices/UTMatrix.hpp>

namespace UTMind {
    /**
     * For testing Matrix3x3f.
     */
    class UTMatrix3x3f: public UTMatrix {
        public:
            /**
             * Instantation of the unit tests for Matrix3x3f.
             */
            UTMatrix3x3f() ;

            /**
             * Destruction of the unit tests for Matrix3x3f.
             */
            virtual ~UTMatrix3x3f() ;

        protected:
            /**
             * Test allocation of Matrix3x3f.
             */
            virtual void allocation() ;

            /**
             * Test utilities on Matrix3x3f.
             */
            virtual void utilities() ;

            /**
             * Test operators on Matrix3x3f.
             */
            virtual void operators() ;
    } ;
}

#endif
