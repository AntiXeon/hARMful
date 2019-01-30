#ifndef __HOPE__GL_CAPABILITY__
#define __HOPE__GL_CAPABILITY__

#include <GL/glew.h>

namespace Hope::GL {
    /**
     * Encapsulate a GL capability.
     */
    class Capability {
        private:
            /**
             * To know if the capability is active or not before activating it.
             * It is used to restore the state after the rendering.
             */
            boolean m_wasEnabled = false ;

        protected:
            /**
             * Apply the capability.
             */
            virtual void apply() {}

            /**
             * Remove the capability.
             */
            virtual void remove() {}

            /**
             * Enable the capability if needed.
             */
            void enable(const GLEnum capability) {
                m_wasEnabled = glIsEnabled(capability) ;

                if (!m_wasEnabled) {
                    glEnable(capability) ;
                }
            }

            /**
             * Disable the capability if needed.
             */
            void disable(const GLEnum capability) {
                if (!m_wasEnabled) {
                    glDisable(capability) ;
                }
            }
    } ;
}

#endif
