#ifndef __HOPE__EFFECT_DATA__
#define __HOPE__EFFECT_DATA__

#include <scene/components/materials/external/ExternalUniformSetter.hpp>

namespace Hope {
    /**
     * Data required for applying a render effect.
     */
    class EffectData {
        friend class OpenGLRenderer ;

        public:
            /**
             * Update the uniform values.
             */
            virtual void updateUniformValues() = 0 ;

            /**
             * Get the shader uniforms.
             */
            virtual std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const = 0 ;
    } ;
}

#endif
