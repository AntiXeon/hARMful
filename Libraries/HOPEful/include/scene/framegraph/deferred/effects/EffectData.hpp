#ifndef __HOPE__EFFECT_DATA__
#define __HOPE__EFFECT_DATA__

#include <utils/Platform.hpp>

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
            exported virtual void updateUniformValues() = 0 ;

            /**
             * Check if the effect has additional uniform to be send to shaders.
             */
            exported virtual bool hasAdditionalUniforms() const {
                return true ;
            }

            /**
             * Get the shader uniforms.
             */
            exported virtual std::vector<Hope::ShaderUniform*> uniforms() const = 0 ;
    } ;
}

#endif
