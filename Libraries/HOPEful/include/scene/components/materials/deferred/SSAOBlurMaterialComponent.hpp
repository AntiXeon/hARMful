#ifndef __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_BLUR_MATERIAL_COMPONENT__
#define __HOPE__SCREEN_SPACE_AMBIENT_OCCLUSION_BLUR_MATERIAL_COMPONENT__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/textures/TextureImage2D.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/components/materials/MaterialComponent.hpp>
#include <scene/framegraph/deferred/framebuffers/base/AbstractFramebufferRenderNode.hpp>
#include <scene/framegraph/deferred/framebuffers/GBufferRenderNode.hpp>

namespace Hope {
    /**
     * Material used on a quad to copy and blur the ambient occlusion.
     */
    class SSAOBlurMaterialComponent final : public MaterialComponent {
        public:
            /**
             * Component class type.
             */
            static const ComponentType ClassType = MaterialComponentType ;

        private:
            /**
             * Buffer containing the ambient occlusion data to copy.
             */
            const AbstractFramebufferRenderNode* m_aoBuffer = nullptr ;

        public:
            /**
             * Create a SSAOBlurMaterialComponent.
             * @param   aoBuffer    Buffer containing the ambient occlusion data
             *                      to copy.
             */
            SSAOBlurMaterialComponent(const AbstractFramebufferRenderNode* aoBuffer) ;

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
} ;

#endif
