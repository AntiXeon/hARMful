#ifndef __HOPE__GL_CAPABILITY_DEPTH_TEST__
#define __HOPE__GL_CAPABILITY_DEPTH_TEST__

#include <utils/Platform.hpp>

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
             enum DepthFunction : GLenum {
                 Never = GL_NEVER,
                 Less = GL_LESS,
                 Equal = GL_EQUAL,
                 LessOrEqual = GL_LEQUAL,
                 Greater = GL_GREATER,
                 GreaterOrEqual = GL_GEQUAL,
                 NotEqual = GL_NOTEQUAL,
                 Always = GL_ALWAYS
             } ;

             /**
              * Create a new DepthTest instance.
              */
             exported DepthTest() : Capability(CapabilityType::DepthTest) {}

         private:
             /**
              * To know if the depth test is to be enabled.
              */
             GLboolean m_depthTestEnabled = GL_TRUE ;

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
             exported void setFunction(const DepthFunction func) {
                 m_function = func ;
             }

         protected:
             /**
              * Apply the capability.
              */
             exported void apply() override ;

             /**
              * Remove the capability.
              */
             exported void remove() override ;
    } ;
}

#endif
