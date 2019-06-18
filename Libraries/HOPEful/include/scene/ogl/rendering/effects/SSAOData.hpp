#ifndef __HOPE__GL_SSAO_DATA__
#define __HOPE__GL_SSAO_DATA__

#include <scene/ogl/rendering/effects/AdditionalEffectsData.hpp>

namespace Hope::GL {
    /**
     * Aggregation of data required for screen-space ambient occlusion.
     */
    class SSAOData final : public AdditionalEffectsData {
        friend class OpenGLRenderer ;

        private:

        public:
            /**
             * Update the uniform values for directional light shadow mapping.
             */
            void updateUniforms() override {
            }

        protected:
            /**
             * Get the shader uniforms.
             */
            std::map<std::string, std::shared_ptr<Hope::ShaderUniform>> uniforms() const override {
                return std::map<std::string, std::shared_ptr<Hope::ShaderUniform>>() ;
            }
    } ;
}

#endif
