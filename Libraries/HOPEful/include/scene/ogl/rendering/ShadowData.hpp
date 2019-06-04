#ifndef __HOPE__GL_SHADOW_DATA__
#define __HOPE__GL_SHADOW_DATA__

#include <scene/framegraph/DirectionalLightShadowNode.hpp>
#include <scene/components/materials/external/DirectionalShadowUniformSetter.hpp>

namespace Hope::GL {
    /**
     * Aggregation of data required for shadow calculation.
     */
    class ShadowData final {
        private:
            /**
             * Send shadow data to shaders.
             */
            DirectionalShadowUniformSetter m_dirShadowSetter ;

            // Put here shadow data for point lights.

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
            void updateDirectionalShadowUniforms() {
                m_dirShadowSetter.updateUniforms() ;
            }
    } ;
}

#endif
