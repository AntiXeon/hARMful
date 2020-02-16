#ifndef __HOPE__EXTERNAL_UNIFORM_SETTER__
#define __HOPE__EXTERNAL_UNIFORM_SETTER__

#include <scene/framegraph/shading/ShaderValue.hpp>
#include <map>
#include <vector>
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
            std::map<std::string, std::unique_ptr<Hope::ShaderUniform>> m_shaderUniforms ;

            /**
             * Cache of uniform pointers for sharing without ownership.
             */
            std::vector<Hope::ShaderUniform*> m_uniformCache ;

        public:
            /**
             * Update the uniforms.
             */
            virtual void updateUniforms() = 0 ;

            /**
             * Get the shader uniforms.
             */
            const std::vector<Hope::ShaderUniform*>& shaderUniforms() const {
                return m_uniformCache ;
            }

        protected:
            /**
             * Add a shader uniform value.
             * It is sent to the shader as a uniform value.
             * Some usual values are already sent to the shaders.
             */
            void addShaderUniform(std::unique_ptr<Hope::ShaderUniform> uniform) {
                m_uniformCache.push_back(uniform.get()) ;
                m_shaderUniforms.insert(std::make_pair(uniform -> name(), std::move(uniform))) ;
            }

            /**
             * Get the uniform with the given name.
             */
            Hope::ShaderUniform* uniform(const std::string& name) {
                if (m_shaderUniforms.count(name) == 1) {
                    return m_shaderUniforms[name].get() ;
                }
                return nullptr ;
            }
    } ;
}

#endif
