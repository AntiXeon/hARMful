#ifndef __HOPE__GL_ADDITIONAL_EFFECTS_DATA_CONTAINER__
#define __HOPE__GL_ADDITIONAL_EFFECTS_DATA_CONTAINER__

#include <scene/ogl/rendering/effects/DirectionalLightShadowData.hpp>
#include <scene/ogl/rendering/effects/SSAOData.hpp>

namespace Hope::GL {
    /**
     * Contains the data of the different available effects
     */
    class AdditionalEffectsContainer final {
        friend class OpenGLRenderer ;

        public:
            /**
             * Amount of effects.
             */
            static const int AmountEffects = 2 ;

        private:
            /**
             * Shadow data.
             */
            DirectionalLightShadowData m_directionalShadow ;

            /**
             * SSAO data.
             */
            SSAOData m_ssao ;

            /**
             * Array of the effects.
             */
            std::array<AdditionalEffectsData*, AmountEffects> m_effects ;

        public:
            /**
             * Create a new AdditionalEffectsData instance.
             */
            AdditionalEffectsContainer() {
                m_effects = {
                    &m_directionalShadow,
                    &m_ssao
                } ;
            }

            /**
             * Update the uniforms of every effect.
             */
            void updateUniforms() {
                for (auto* effectsData : m_effects) {
                    effectsData -> updateUniforms() ;
                }
            }

            /**
             * Set the frame graph node that contains all required data for
             * computing directional light shadows.
             */
            void setDirectionalLightShadowData(Hope::DirectionalLightShadowNode* dirLightShadow) {
                m_directionalShadow.setDirectionalLightShadow(dirLightShadow) ;
            }

            /**
             * Set the frame graph node for computing SSAO.
             */
            void setSSAOData(Hope::SSAORenderNode* ssaoNode) {
                m_ssao.setSSAO(ssaoNode) ;
            }

        private:
            /**
             * Get shadow data.
             */
            const DirectionalLightShadowData& shadow() const {
                return m_directionalShadow ;
            }

            /**
             * Get SSAO data.
             */
            const SSAOData& ssao() const {
                return m_ssao ;
            }

            /**
             * Get the effects as an array of AdditionalEffectsData.
             */
            const std::array<AdditionalEffectsData*, AmountEffects>& toArray() const {
                return m_effects ;
            }
    } ;
}

#endif
