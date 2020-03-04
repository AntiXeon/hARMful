#ifndef __HOPE__GL_CAPABILITY_DEPTH_MASK__
#define __HOPE__GL_CAPABILITY_DEPTH_MASK__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Enable depth mask GL capability.
     */
    class DepthMask final : public Capability {
        private:
            /**
             * To know if the depth mask is used or not for rendering.
             */
            GLboolean m_isEnabled = GL_TRUE ;

            /**
             * Store the depth mask state for restore.
             */
            GLboolean m_oldIsEnabled = GL_TRUE ;

        public:
            /**
             * Create a new DepthMask instance.
             */
            exported DepthMask() : Capability(CapabilityType::DepthMask) {}

            /**
             * Enable depth mask.
             */
            exported void enable() {
                m_isEnabled = true ;
            }

            /**
             * Disable depth mask.
             */
            exported void disable() {
                m_isEnabled = false ;
            }

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
