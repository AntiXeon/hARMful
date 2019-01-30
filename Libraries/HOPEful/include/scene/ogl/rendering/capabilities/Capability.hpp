#ifndef __HOPE__GL_CAPABILITY__
#define __HOPE__GL_CAPABILITY__

#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Encapsulate a GL capability.
     */
    class Capability {
        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {}

            /**
             * Remove the capability.
             */
            virtual void remove() {}
    } ;
}

#endif
