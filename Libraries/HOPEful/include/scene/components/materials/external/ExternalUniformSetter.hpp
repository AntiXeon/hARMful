#ifndef __HOPE__EXTERNAL_UNIFORM_SETTER__
#define __HOPE__EXTERNAL_UNIFORM_SETTER__

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <map>
#include <string>
#include <memory>

namespace Hope {
    /**
     * Setter of uniform values that are external to the materials.
     * These uniform values are used in shaders but are not intrinsic properties
     * of the materials. By the way, they are common to every material.
     */
    class ExternalUniformSetter {
        private:
            /**
             * List of shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> m_shaderUniforms ;

        public:
            /**
             * Update the uniforms.
             */
            virtual void updateUniforms() = 0 ;

        protected:
            /**
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderUniform(const std::shared_ptr<Hope::ShaderUniform> uniform) {
                m_shaderUniforms[uniform -> name()] = uniform ;
            }

            /**
             * Get the uniform with the given name.
             */
            std::shared_ptr<Hope::ShaderUniform> uniform(const std::string& name) {
                return m_shaderUniforms[name] ;
            }
    } ;
}

#endif
