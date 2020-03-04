#ifndef __HOPE__GL_CAPABILITY_ANTIALIASING__
#define __HOPE__GL_CAPABILITY_ANTIALIASING__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable multisampling GL capability.
     */
    class AntiAliasing final : public Capability {
        public:
            /**
             * Create a new AntiAliasing instance.
             */
            exported AntiAliasing() : Capability(CapabilityType::AntiAliasing) {}

        protected:
            /**
             * Apply the capability.
             */
            void apply() override ;

            /**
             * Remove the capability.
             */
            void remove() override ;
    } ;
}

#endif
