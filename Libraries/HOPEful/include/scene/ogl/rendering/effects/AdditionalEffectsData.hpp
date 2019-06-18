#ifndef __HOPE__GL_ADDITIONAL_EFFECTS_DATA__
#define __HOPE__GL_ADDITIONAL_EFFECTS_DATA__

#include <scene/components/materials/external/ExternalUniformSetter.hpp>

namespace Hope::GL {
    /**
     * Aggregation of data required for applying a render effect.
     */
    class AdditionalEffectsData {
        friend class OpenGLRenderer ;
        
        public:
            /**
             * Update the uniform values.
             */
            virtual void updateUniforms() = 0 ;

        protected:
            /**
             * Get the shader uniforms.
             */
            virtual std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const = 0 ;
    } ;
}

#endif
