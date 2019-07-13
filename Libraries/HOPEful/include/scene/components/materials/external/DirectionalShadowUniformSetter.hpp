#ifndef __HOPE__DIRECTIONAL_SHADOW_UNIFORM_SETTER__
#define __HOPE__DIRECTIONAL_SHADOW_UNIFORM_SETTER__

#include <scene/components/materials/external/ExternalUniformSetter.hpp>
#include <scene/framegraph/shading/ShaderValue.hpp>

namespace Hope {
    class DirectionalLightShadowNode ;

    /**
     * Setter of uniform values for shadow related stuff.
     */
    class DirectionalShadowUniformSetter final : public ExternalUniformSetter {
        private:
            /**
             * To know if shadows must be computed or not.
             */
            bool m_useShadow = false ;

            /**
             * Frame graph node that contains all required data for computing
             * directional light shadows.
             */
            const Hope::DirectionalLightShadowNode* m_dirLightShadowNode = nullptr ;

        public:
            /**
             * Create a new DirectionalShadowUniformSetter instance.
             */
            DirectionalShadowUniformSetter() ;

            /**
             * Update the uniforms.
             */
            void updateUniforms() override ;

            /**
             * Set the frame graph node that contains all required data for
             * computing directional light shadows.
             */
            void setLightShadowNode(const Hope::DirectionalLightShadowNode* node) ;
    } ;
}

#endif
