#ifndef __UNIT_TEST__MIND__RECTANGLE2DF__
#define __UNIT_TEST__MIND__RECTANGLE2DF__

#include <UnitTest.hpp>
#include <modules/rectangles/UTRectangle.hpp>

namespace UTMind {
    /**
     * For testing Rectangle2Df.
     */
    class UTRectangle2Df final: public UTRectangle {
        public:
            /**
             * Instantation of the unit tests for Rectangle2Df.
             */
            UTRectangle2Df() ;

            /**
             * Destruction of the unit tests for Rectangle2Df.
             */
            virtual ~UTRectangle2Df() ;

        protected:
            /**
             * Test allocation of Rectangle2Df objects.
             */
            virtual void allocation() final ;

            /**
             * Test translation of Rectangle2Df objects.
             */
            virtual void translation() final ;

            /**
             * Test if a Rectangle2Df contains other objects.
             */
            virtual void contain() final ;

            /**
             * Test if a Rectangle2Df intersects other objects.
             */
            virtual void intersect() final ;

            /**
             * Test position of Rectangle2Df objects.
             */
            virtual void position() final ;

            /**
             * Test operators of Rectangle2Df objects.
             */
            virtual void operators() final ;
    } ;
}

#endif
