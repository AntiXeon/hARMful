#ifndef __HOPE__GL_CAPABILITY_SEAMLESS_CUBEMAP__
#define __HOPE__GL_CAPABILITY_SEAMLESS_CUBEMAP__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Cubemap textures are sampled such that when linearly sampling from the
     * border between two adjacent faces, texels from both faces are used to
     * generate the final sample value.
     */
    class SeamlessCubemap final : public Capability {
        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_TEXTURE_CUBE_MAP_SEAMLESS) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                disable(GL_TEXTURE_CUBE_MAP_SEAMLESS) ;
            }
    } ;
}

#endif
