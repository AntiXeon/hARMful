#ifndef __HOPE__GL_CAPABILITY_ALPHA_COVERAGE__
#define __HOPE__GL_CAPABILITY_ALPHA_COVERAGE__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable alpha-to-coverage multisampling mode.
     */
    class AlphaCoverage final : public Capability {
        public:
            /**
             * Create a new AlphaCoverage instance.
             */
            exported AlphaCoverage() : Capability(CapabilityType::AlphaCoverage) {}

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
