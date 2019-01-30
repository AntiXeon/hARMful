#ifndef __HOPE__GL_CAPABILITY_ALPHA_TEST__
#define __HOPE__GL_CAPABILITY_ALPHA_TEST__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the alpha test GL capability.
     */
    class AlphaTest final : public Capability {
        public:
            /**
             * Possible alpha test function to apply.
             */
            enum class AlphaFunction : GLenum {
                Never = GL_NEVER,
                Less = GL_LESS,
                Equal = GL_EQUAL,
                LessOrEqual = GL_LEQUAL,
                Greater = GL_GREATER,
                GreaterOrEqual = GL_GEQUAL,
                NotEqual = GL_NOTEQUAL,
                Always = GL_ALWAYS
            } ;

        private:
            /**
             * Alpha test function to apply.
             */
            AlphaFunction m_function = AlphaFunction::Always ;

            /**
             * Hold the old function to restore it.
             */
            GLint m_oldFunction ;

            /**
             * Reference value for the alpha test function.
             */
            GLclampf m_reference ;

            /**
             * Hold the old reference to restore it.
             */
            GLclampf m_oldReference ;

        public:
            /**
             * Set the applied alpha test function.
             */
            void setFunction(const AlphaFunction func) {
                m_function = func ;
            }

            /**
             * Set the reference value for the alpha test function.
             */
            void setReference(const GLclampf ref) {
                m_reference = ref ;
            }

        protected:
            /**
             * Apply the capability.
             */
            void apply() override {
                enable(GL_ALPHA_TEST) ;
                glGetIntegerv(GL_ALPHA_TEST_FUNC, &m_oldFunction) ;
                glGetIntegerv(GL_ALPHA_TEST_REF, &m_oldReference) ;

                if ((m_function != m_oldFunction) && (m_reference != m_oldReference)) {
                    glAlphaFunc(m_function, m_reference) ;
                }
            }

            /**
             * Remove the capability.
             */
            void remove() override {
                if ((m_function != m_oldFunction) && (m_reference != m_oldReference)) {
                    glAlphaFunc(m_oldFunction, m_oldReference) ;
                }

                disable(GL_ALPHA_TEST) ;
            }
    } ;
}

#endif
