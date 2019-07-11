#ifndef __HOPE__GL_SSAO_DATA__
#define __HOPE__GL_SSAO_DATA__

#include <scene/ogl/rendering/effects/AdditionalEffectsData.hpp>
#include <scene/framegraph/deferred/effects/ao/SSAORenderNode.hpp>
#include <scene/components/materials/external/SSAOUniformSetter.hpp>

namespace Hope::GL {
    /**
     * Aggregation of data required for screen-space ambient occlusion.
     */
    class SSAOData final : public AdditionalEffectsData {
        friend class OpenGLRenderer ;

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
            void updateUniforms() override {
                m_ssaoSetter.updateUniforms() ;
            }

        protected:
            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const override {
                return m_ssaoSetter.shaderUniforms() ;
            }
    } ;
}

#endif
