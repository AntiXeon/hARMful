#ifndef __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_MATERIAL_COMPONENT__
#define __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_MATERIAL_COMPONENT__

#include <utils/Platform.hpp>

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/offscreen/GBufferRenderNode.hpp>

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
             * Location of the uniform for the MSAA quality.
             */
            static const int MSAAQualityUniformLocation = 5 ;

            /**
             * G-Buffer contening all the required data to perform the deferred
             * shading step.
             */
            const GBufferRenderNode* m_gBuffer = nullptr ;

        public:
            /**
             * Create a SSAOMaterialComponent.
             * @param   gBuffer G-Buffer contening all the required data to
             *                  perform the deferred shading step.
             */
            exported SSAOMaterialComponent(const GBufferRenderNode* gBuffer) ;

            /**
             * Update the uniform values before the processing of the material
             * component.
             */
            exported void updateUniformValues() override ;

        private:
            /**
             * Set up the Uniforms of the current material.
             */
            exported void setupUniforms() {}

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
} ;

#endif
