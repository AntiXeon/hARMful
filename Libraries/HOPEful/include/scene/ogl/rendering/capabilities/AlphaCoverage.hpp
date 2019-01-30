#ifndef __HOPE__GL_CAPABILITY_ALPHA_COVERAGE__
#define __HOPE__GL_CAPABILITY_ALPHA_COVERAGE__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable alpha-to-coverage multisampling mode.
     */
    class AlphaCoverage final : public Capability {
        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE) ;
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                glDisable(GL_SAMPLE_ALPHA_TO_COVERAGE) ;
            }
    } ;
}

#endif
