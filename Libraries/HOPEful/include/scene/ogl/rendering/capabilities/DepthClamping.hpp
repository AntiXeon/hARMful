#ifndef __HOPE__GL_CAPABILITY_DEPTH_CLAMPING__
#define __HOPE__GL_CAPABILITY_DEPTH_CLAMPING__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the depth clamp GL capability.
     */
    class DepthClamping final : public Capability {
        public:
            /**
             * Create a new DepthClamping instance.
             */
            exported DepthClamping() : Capability(CapabilityType::DepthClamping) {}

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
