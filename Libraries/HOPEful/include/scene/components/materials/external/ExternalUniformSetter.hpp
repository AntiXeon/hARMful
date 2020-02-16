#ifndef __HOPE__EXTERNAL_UNIFORM_SETTER__
#define __HOPE__EXTERNAL_UNIFORM_SETTER__

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <scene/components/materials/UniformCache.hpp>

namespace Hope {
    /**
     * Setter of uniform values that are external to the materials.
     * These uniform values are used in shaders but are not intrinsic properties
     * of the materials. By the way, they are common to every material.
     */
    class ExternalUniformSetter {
        private:
            /**
             * Uniforms cache.
             */
            UniformCache m_uniforms ;

        public:
            /**
             * Update the uniforms.
             */
            virtual void updateUniforms() = 0 ;

            /**
             * Get the shader uniforms.
             */
            const std::vector<Hope::ShaderUniform*>& shaderUniforms() const {
                return m_uniforms.pointers() ;
            }

        protected:
            /**
             * Get the unoforms of the material.
             */
            UniformCache& uniforms() {
                return m_uniforms ;
            }
    } ;
}

#endif
