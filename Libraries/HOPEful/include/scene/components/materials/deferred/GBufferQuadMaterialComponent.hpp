#ifndef __HOPE__DEFERRED_RENDERING_SCREEN_QUAD_MATERIAL_COMPONENT__
#define __HOPE__DEFERRED_RENDERING_SCREEN_QUAD_MATERIAL_COMPONENT__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/OffScreenRenderNode.hpp>

namespace Hope {
    /**
     * Material used on a quad having taking the whole viewport area to display
     * the content of the G-Buffer (deferred rendering).
     */
    class GBufferQuadMaterialComponent final : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * G-Buffer contening all the required data to perform the deferred
             * shading step.
             */
            const OffScreenRenderNode* m_gBuffer = nullptr ;

        public:
            /**
             * Create a GBufferQuadMaterialComponent.
             * @param gBuffer   G-Buffer contening all the required data to
             *                  perform the deferred shading step.
             */
            GBufferQuadMaterialComponent(const OffScreenRenderNode* gBuffer) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() ;

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             * No deferred shading here!
             */
            void setupDeferredShader() override {}
    } ;
}

#endif
