#ifndef __HOPE__GL_CAPABILITY_FACE_CULLING__
#define __HOPE__GL_CAPABILITY_FACE_CULLING__

#include <utils/Platform.hpp>

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the face culling GL capability.
     * Default is back face culling.
     */
    class FaceCulling final : public Capability {
        public:
            /**
             * Possible cull modes.
             */
            enum CullMode : GLenum {
                None = 0x0,
                Front =  GL_FRONT,
                Back = GL_BACK,
                FrontAndBack = GL_FRONT_AND_BACK
            } ;

        private:
            /**
             * Used culling mode.
             */
            CullMode m_mode = CullMode::Back ;

            /**
             * When no culling is set for the current state, store if the face
             * culling was previously activated.
             */
            GLboolean m_wasEnabled = GL_FALSE ;

        public:
            /**
             * Create a new FaceCulling instance.
             */
            exported FaceCulling() : Capability(CapabilityType::FaceCulling) {}

            /**
             * Set the used culling mode.
             */
            exported void setCullMode(const CullMode mode) {
                m_mode = mode ;
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
