#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_DATA__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_DATA__

#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <scene/framegraph/deferred/effects/shadows/DirectionalLightShadowNode.hpp>
#include <scene/components/materials/external/DirectionalShadowUniformSetter.hpp>

namespace Hope {
    /**
     * Data required for shadow calculation of a directional light.
     */
    class DirectionalLightShadowData final : public EffectData {
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
            void updateUniformValues() override {
                m_dirShadowSetter.updateUniforms() ;
            }

            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const override {
                return m_dirShadowSetter.shaderUniforms() ;
            }
    } ;
}

#endif
