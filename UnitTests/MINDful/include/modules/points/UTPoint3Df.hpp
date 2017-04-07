#ifndef __UNIT_TEST__MIND__POINT3DF__
#define __UNIT_TEST__MIND__POINT3DF__

#include <UnitTest.hpp>
#include <modules/points/UTPoint.hpp>

namespace UTMind {
    /**
     * For testing Point3Df.
     */
    class UTPoint3Df final: public UTPoint {
        protected:
            /**
             * Test allocation of Point3Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Point3Df objects.
             */
            virtual void utilities() final ;
    } ;
}

#endif
