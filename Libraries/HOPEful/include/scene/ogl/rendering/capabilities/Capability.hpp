#ifndef __HOPE__GL_CAPABILITY__
#define __HOPE__GL_CAPABILITY__

#include <GL/glew.h>

namespace Hope {
    class FrameGraphBranchState ;
}

namespace Hope::GL {
    /**
     * Encapsulate a GL capability.
     */
    class Capability {
        friend class Hope::FrameGraphBranchState ;
        friend class OpenGLRenderer ;

        private:
            /**
             * To know if the capability is active or not before activating it.
             * It is used to restore the state after the rendering.
             */
            bool m_wasEnabled = false ;

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() = 0 ;

            /**
             * Remove the capability.
             */
            virtual void remove() = 0 ;

            /**
             * Enable the capability if needed.
             */
            void enable(const GLenum capability) {
                m_wasEnabled = glIsEnabled(capability) ;

                if (!m_wasEnabled) {
                    glEnable(capability) ;
                }
            }

            /**
             * Disable the capability if needed.
             */
            void disable(const GLenum capability) {
                if (!m_wasEnabled) {
                    glDisable(capability) ;
                }
            }
    } ;
}

#endif
