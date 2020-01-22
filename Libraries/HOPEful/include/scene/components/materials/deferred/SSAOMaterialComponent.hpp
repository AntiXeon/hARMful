#ifndef __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_MATERIAL_COMPONENT__
#define __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_MATERIAL_COMPONENT__

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/AbstractFramebufferRenderNode.hpp>

namespace Hope {
    /**
     * Material used on a quad to render the ambient occlusion contribution.
     */
    class SSAOMaterialComponent final : public MaterialComponent {
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
            const AbstractFramebufferRenderNode* m_gBuffer = nullptr ;

        public:
            /**
             * Create a SSAOMaterialComponent.
             * @param   gBuffer G-Buffer contening all the required data to
             *                  perform the deferred shading step.
             */
            SSAOMaterialComponent(const AbstractFramebufferRenderNode* gBuffer) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            void updateUniformValues() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            void setupUniforms() {}

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
} ;

#endif
