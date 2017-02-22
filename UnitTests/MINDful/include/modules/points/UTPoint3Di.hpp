#ifndef __UNIT_TEST__MIND__POINT3DI__
#define __UNIT_TEST__MIND__POINT3DI__

#include <UnitTest.hpp>
#include <modules/points/UTPoint.hpp>

namespace UTMind {
    /**
     * For testing Point3Di.
     */
    class UTPoint3Di final: public UTPoint {
        public:
            /**
             * Instantation of the unit tests for Point3Di.
             */
            UTPoint3Di() ;

            /**
             * Destruction of the unit tests for Point3Di.
             */
            virtual ~UTPoint3Di() ;

        protected:
            /**
             * Test allocation of Point3Di objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Point3Di objects.
             */
            virtual void utilities() final ;
    } ;
}

#endif
