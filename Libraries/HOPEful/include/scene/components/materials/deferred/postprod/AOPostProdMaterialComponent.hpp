#ifndef __HOPE__AO_POST_PROD_MATERIAL_COMPONENT__
#define __HOPE__AO_POST_PROD_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    class AOApplyEffectNode ;

    /**
     * Material used on a quad to apply ambient occlusion on an already computed
     * shading.
     */
    class AOPostProdMaterialComponent final : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Node bearing the framebuffer containing the result of deferred
             * rendering.
             */
            const FramebufferRenderNode* m_framebufferNode = nullptr ;

        public:
            /**
             * Create a AOPostProdMaterialComponent.
             * @param framebufferNode   Node bearing the framebuffer containing
             *                          the result of deferred rendering.
             */
            exported AOPostProdMaterialComponent(const FramebufferRenderNode* framebufferNode) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues(const Hope::RenderPassID pass) override ;

        protected:
            /**
             * Setup the shader for the forward rendering pass.
             */
            exported void setupForwardShader() override ;

            /**
             * Setup the shader for the deferred rendering pass.
             * No deferred shading here!
             */
            exported void setupDeferredShader() override {}
    } ;
}

#endif
