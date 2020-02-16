#ifndef __HOPE__SSAO_DATA__
#define __HOPE__SSAO_DATA__

#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/external/SSAOUniformSetter.hpp>

namespace Hope {
    /**
     * Data required for screen-space ambient occlusion.
     */
    class SSAOData final : public EffectData {
        private:
            /**
             * Send SSAO data to shaders.
             */
            SSAOUniformSetter m_ssaoSetter ;

        public:
            /**
             * Set the node containing SSAO data.
             */
            void setSSAO(Hope::SSAORenderNode* node) {
                m_ssaoSetter.setSSAONode(node) ;
            }

            /**
             * Update the uniform values for directional light shadow mapping.
             */
            void updateUniformValues() override {
                m_ssaoSetter.updateUniforms() ;
            }

            /**
             * Get the shader uniforms.
             */
            std::vector<Hope::ShaderUniform*> uniforms() const override {
                return m_ssaoSetter.shaderUniforms() ;
            }
    } ;
}

#endif
