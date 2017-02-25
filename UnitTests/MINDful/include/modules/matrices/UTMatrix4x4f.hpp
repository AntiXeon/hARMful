#ifndef __UNIT_TEST__MIND__MATRIX4X4F__
#define __UNIT_TEST__MIND__MATRIX4X4F__

#include <modules/matrices/UTMatrix.hpp>

namespace UTMind {
    /**
     * For testing Matrix4x4f.
     */
    class UTMatrix4x4f: public UTMatrix {
        public:
            /**
             * Instantation of the unit tests for Matrix4x4f.
             */
            UTMatrix4x4f() ;

            /**
             * Destruction of the unit tests for Matrix4x4f.
             */
            virtual ~UTMatrix4x4f() ;

        protected:
            /**
             * Test allocation of Matrix4x4f.
             */
            virtual void allocation() ;

            /**
             * Test utilities on Matrix4x4f.
             */
            virtual void utilities() ;

            /**
             * Test operators on Matrix4x4f.
             */
            virtual void operators() ;
    } ;
}

#endif
