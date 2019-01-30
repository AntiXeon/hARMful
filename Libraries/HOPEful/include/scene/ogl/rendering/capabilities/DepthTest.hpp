#ifndef __HOPE__GL_CAPABILITY_DEPTH_TEST__
#define __HOPE__GL_CAPABILITY_DEPTH_TEST__

#include <scene/ogl/rendering/capabilities/Capability.hpp>

namespace Hope::GL {
    /**
     * Encapsulate the depth test GL capability.
     */
    class DepthTest final : public Capability {
        public:
            /**
             * Possible depth test functions.
             */
             enum class DepthFunction : GLenum {
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
              * Depth test function to apply.
              */
             DepthFunction m_function = DepthFunction::Less ;

             /**
              * Old depth function.
              */
             DepthFunction m_oldFunction ;

         public:
             /**
              * Set the applied depth test function.
              */
             void setFunction(const DepthFunction func) {
                 m_function = func ;
             }

         protected:
             /**
              * Apply the capability.
              */
             void apply() override {
                 enable(GL_DEPTH_TEST) ;
                 glGetIntegerv(GL_DEPTH_FUNC, &m_oldFunction) ;

                 if (m_function != m_oldFunction) {
                     glDepthFunc(m_function) ;
                 }
             }

             /**
              * Remove the capability.
              */
             void remove() override {
                 if (m_function != m_oldFunction) {
                     glDepthFunc(m_oldFunction) ;
                 }

                 disable(GL_DEPTH_TEST) ;
             }
    } ;
}

#endif
