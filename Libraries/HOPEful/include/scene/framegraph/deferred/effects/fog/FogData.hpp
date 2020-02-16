#ifndef __HOPE__FOG_DATA__
#define __HOPE__FOG_DATA__

#include <scene/framegraph/deferred/effects/EffectData.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/glsl/ubo/FogDataBlock.hpp>
    namespace API = Hope::GL ;
#endif

namespace Hope {
    /**
     * Data required for rendering fog.
     */
    class FogData final : public EffectData {
        private:
            /**
             * Data of fog for its rendering.
             */
            API::FogDataBlock m_fogData ;

        public:
            /**
             * Set the color value.
             */
            void setColor(const Color& color) {
                m_fogData.setColor(color) ;
            }

            /**
             * Set the minimal distance value.
             */
            void setMinimalDistance(const float min) {
                m_fogData.setMinimalDistance(min) ;
            }

            /**
             * Set the maximal distance value.
             */
            void setMaximalDistance(const float max) {
                m_fogData.setMaximalDistance(max) ;
            }

            /**
             * Update the fog related uniform values.
             */
            void updateUniformValues() override {
                m_fogData.update() ;
            }

            /**
             * Check if the effect has additional uniform to be send to shaders.
             */
            bool hasAdditionalUniforms() const override {
                return false ;
            }

            /**
             * Get the shader uniforms.
             */
            std::vector<Hope::ShaderUniform*> uniforms() const override {
                return std::vector<Hope::ShaderUniform*>() ;
            }
    } ;
}

#endif
