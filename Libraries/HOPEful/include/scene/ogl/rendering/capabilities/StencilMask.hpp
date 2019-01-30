#ifndef __HOPE__GL_CAPABILITY_STENCIL_MASK__
#define __HOPE__GL_CAPABILITY_STENCIL_MASK__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Control the front and/or back writing of individual bits in the stencil
     * planes.
     */
    class StencilMask final : public Capability {
        private:
            /**
             * Bit mask to enable and disable writing of individual bits in the
             * stencil planes.
             */
            GLuint m_front = 1 ;

            /**
             * Store the old value for restore.
             */
            GLuint m_oldFront ;

            /**
             * Bit mask to enable and disable writing of individual bits in the
             * stencil planes.
             */
            GLuint m_back = 1 ;

            /**
             * Store the old value for restore.
             */
            GLuint m_oldBack ;

        public:
            /**
             * Set the bit mask to enable and disable writing of individual bits
             * in the stencil planes.
             */
            void setFrontMask(const uint32_t mask) {
                m_front = mask ;
            }

            /**
             * Set the bit mask to enable and disable writing of individual bits
             * in the stencil planes.
             */
            void setBackMask(const uint32_t mask) {
                m_back = mask ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_STENCIL_TEST) ;

                glGetIntegerv( GL_STENCIL_WRITEMASK, &m_oldFront) ;
                glGetIntegerv( GL_STENCIL_BACK_WRITEMASK, &m_oldBack) ;

                if (m_front != m_oldFront) {
                    glStencilMaskSeparate(GL_FRONT, m_front) ;
                }

                if (m_back != m_oldBack) {
                    glStencilMaskSeparate(GL_BACK, m_back) ;
                }
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                if (m_front != m_oldFront) {
                    glStencilMaskSeparate(GL_FRONT, m_oldFront) ;
                }

                if (m_back != m_oldBack) {
                    glStencilMaskSeparate(GL_BACK, m_oldBack) ;
                }

                disable(GL_STENCIL_TEST) ;
            }
    } ;
}

#endif
