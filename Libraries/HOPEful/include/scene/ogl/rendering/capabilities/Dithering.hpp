#ifndef __HOPE__GL_CAPABILITY_DITHERING__
#define __HOPE__GL_CAPABILITY_DITHERING__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable dithering.
     */
    class Dithering final : public Capability {
        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_DITHER) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                disable(GL_DITHER) ;
            }
    } ;
}

#endif
