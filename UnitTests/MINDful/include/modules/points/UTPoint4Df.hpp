#ifndef __UNIT_TEST__MIND__POINT4DF__
#define __UNIT_TEST__MIND__POINT4DF__

#include <UnitTest.hpp>
#include <modules/points/UTPoint.hpp>

namespace UTMind {
    /**
     * For testing Point4Df.
     */
    class UTPoint4Df final: public UTPoint {
        protected:
            /**
             * Test allocation of Point4Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test utilities on Point4Df objects.
             */
            virtual void utilities() final ;
    } ;
}

#endif
