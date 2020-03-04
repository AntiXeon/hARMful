#ifndef __HOPE__DISPLAY_DEFERRED_RENDER_MATERIAL_COMPONENT__
#define __HOPE__DISPLAY_DEFERRED_RENDER_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    /**
     * Material used on a quad having taking the whole viewport area to display
     * the result of the deferred rendering.
     */
    class DisplayDeferredRenderMaterialComponent final : public MaterialComponent {
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
             * Create a DisplayDeferredRenderMaterialComponent.
             * @param framebufferNode   Node bearing the framebuffer containing
             *                          the result of deferred rendering.
             */
            exported DisplayDeferredRenderMaterialComponent(const FramebufferRenderNode* framebufferNode) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues() override ;

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
