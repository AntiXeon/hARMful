#ifndef __HOPE__GL_CAPABILITY_FACE_CULLING__
#define __HOPE__GL_CAPABILITY_FACE_CULLING__

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
            enum class CullMode : GLenum {
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
             * Set the used culling mode.
             */
            void setCullMode(const CullMode mode) {
                m_mode = mode ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                if (m_mode == CullMode::None) {
                    m_wasEnabled = glIsEnabled() ;
                    if (m_wasEnabled) {
                        glDisable(GL_CULL_FACE) ;
                    }
                }
                else {
                    enable(GL_CULL_FACE) ;
                    glCullFace(m_mode) ;
                }
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                if (m_mode == CullMode::None) {
                    if (m_wasEnabled) {
                        glEnable(GL_CULL_FACE) ;
                    }
                }
                else {
                    disable(GL_CULL_FACE) ;
                }
            }
    } ;
}

#endif
