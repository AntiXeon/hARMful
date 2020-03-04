#ifndef __HOPE__GL_CAPABILITY_SEAMLESS_CUBEMAP__
#define __HOPE__GL_CAPABILITY_SEAMLESS_CUBEMAP__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Cubemap textures are sampled such that when linearly sampling from the
     * border between two adjacent faces, texels from both faces are used to
     * generate the final sample value.
     */
    class SeamlessCubemap final : public Capability {
        public:
            /**
             * Create a new SeamlessCubemap instance.
             */
            exported SeamlessCubemap() : Capability(CapabilityType::SeamlessCubemap) {}

        protected:
            /**
             * Apply the capability.
             */
            exported void apply() override ;

            /**
             * Remove the capability.
             */
            exported void remove() override ;
    } ;
}

#endif
