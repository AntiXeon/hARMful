#ifndef __HOPE__GL_CAPABILITY_ANTIALIASING__
#define __HOPE__GL_CAPABILITY_ANTIALIASING__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable multisampling GL capability.
     */
    class AntiAliasing final : public Capability {
        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_MULTISAMPLE) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                disable(GL_MULTISAMPLE) ;
            }
    } ;
}

#endif
