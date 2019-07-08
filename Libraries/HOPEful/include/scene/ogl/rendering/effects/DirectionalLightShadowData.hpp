#ifndef __HOPE__GL_DIRECTIONAL_LIGHT_SHADOW_DATA__
#define __HOPE__GL_DIRECTIONAL_LIGHT_SHADOW_DATA__

#include <scene/ogl/rendering/effects/AdditionalEffectsData.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/components/materials/external/DirectionalShadowUniformSetter.hpp>

namespace Hope::GL {
    /**
     * Aggregation of data required for shadow calculation of a directional
     * light.
     */
    class DirectionalLightShadowData final : public AdditionalEffectsData {
        friend class OpenGLRenderer ;

        private:
            /**
             * Send shadow data to shaders.
             */
            DirectionalShadowUniformSetter m_dirShadowSetter ;

        public:
            /**
             * Set the node containing directional light shadow data.
             */
            void setDirectionalLightShadow(Hope::DirectionalLightShadowNode* node) {
                m_dirShadowSetter.setLightShadowNode(node) ;
            }

            /**
             * Update the uniform values for directional light shadow mapping.
             */
            void updateUniforms() override {
                m_dirShadowSetter.updateUniforms() ;
            }

        protected:
            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const override {
                return m_dirShadowSetter.shaderUniforms() ;
            }
    } ;
}

#endif
