#ifndef __HOPE__GL_RENDERER__
#define __HOPE__GL_RENDERER__

#include <utils/Platform.hpp>

#include <scene/ogl/mesh/builtin/QuadGeometry.hpp>
#include <scene/ogl/rendering/RenderPass.hpp>
#include <scene/ogl/rendering/framebuffers/Framebuffer.hpp>
#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/LightGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/framegraph/cache/GeometryData.hpp>
#include <scene/framegraph/deferred/effects/EffectData.hpp>
#include <matrices/Matrix4x4f.hpp>
#include <scene/SceneTypes.hpp>
#include <vector>

namespace Hope {
    class FrameRenderCache ;
    class MaterialComponent ;
    class ExternalUniformSetter ;
}

namespace Hope::GL {
    /**
     * Render the scene.
     */
    class OpenGLRenderer final {
        private:
            /**
             * UBO containing the base data for GLSL shaders.
             */
            BaseGLSLDataUBO m_baseUBO ;

            /**
             * UBO containing data for lighting for GLSL shaders.
             */
            LightGLSLDataUBO m_lightUBO ;

            /**
             * UBO containing data of the model.
             */
            ModelGLSLDataUBO m_modelUBO ;

            /**
             * View matrix.
             */
            Mind::Matrix4x4f m_viewMatrix ;

            /**
             * Projection matrix.
             */
            Mind::Matrix4x4f m_projectionMatrix ;

            /**
             * Quad used for deferred shading.
             */
            QuadGeometry m_deferredShadingQuad ;

            /**
             * The default framebuffer.
             */
            Framebuffer* m_defaultFramebuffer = nullptr ;

        public:
            /**
             * Render the scene in a frambuffer (the default one or not).
             * @param   renderPassID    ID of the pass to use for rendering
             *                          objects. The render pass uses its
             *                          related shader program to render the
             *                          objects.
             * @param   dataList        Geometries to be rendered.
             * @param   memoryBarrier   Memory barrier to apply while rendering
             *                          the pass.
             */
            exported void render(
                const Hope::RenderPassID renderPassID,
                std::vector<Hope::GeometryData>& dataList,
                const uint32_t memoryBarrier
            ) ;

            /**
             * Render the content of a GBuffer for applying deferred shading.
             * @param   material    Material applied on the screen quad to
             *                      render the content of the GBuffer, applying
             *                      deferred shading.
             * @param   memoryBarrier   Memory barrier to apply while rendering
             *                          the pass.
             * @param   effects     Effects to apply on rendering.
             */
            exported void deferredShading(
                Hope::MaterialComponent* material,
                const uint32_t memoryBarrier,
                std::vector<Hope::EffectData*>& effects
            ) ;

            /**
             * Run an update of the light UBO.
             */
            exported void updateLightUBO(const std::shared_ptr<Hope::FrameRenderCache> cache) ;

            /**
             * Set the view matrix.
             */
            exported void setViewMatrix(const Mind::Matrix4x4f& viewMatrix) {
                m_viewMatrix = viewMatrix ;
            }

            /**
             * Set the projection matrix.
             */
            exported void setProjectionMatrix(const Mind::Matrix4x4f& projectionMatrix) {
                m_projectionMatrix = projectionMatrix ;
            }

            /**
             * Get the base data UBO.
             */
            exported BaseGLSLDataUBO& baseUBO() {
                return m_baseUBO ;
            }

            /**
             * Set the default FBO.
             */
            exported void setDefaultFramebuffer(Framebuffer* defaultFBO) {
                m_defaultFramebuffer = defaultFBO ;
            }

            /**
             * Get the default FBO.
             */
            exported Framebuffer* defaultFramebuffer() const {
                return m_defaultFramebuffer ;
            }

        private:
            /**
             * Activate a shader to use uniforms, etc.
             * @param   renderPassID    ID of the pass to use for rendering
             *                          objects. The render pass uses its
             *                          related shader program to render the
             *                          objects.
             * @param   component       Material component to use.
             */
            exported const Hope::GL::RenderPass* activateShader(
                const Hope::RenderPassID renderPassID,
                const Hope::MaterialComponent* component
            ) ;

            /**
             * Use a material component.
             * @param   RenderPass      The pass to use for rendering objects.
             * @param   component       Material component to use.
             * @param   applyEffects    true to apply additional effects; false
             *                          otherwise.
             * @return  The capabilities of the render pass that is used in the
             *          material.
             */
            exported void useMaterial(
                const Hope::GL::RenderPass* pass,
                const std::vector<Hope::EffectData*>& effects = {}
            ) ;

            /**
             * Enable the capabilities of the render pass that is used.
             */
            exported void enableCapabilities(const RenderPass* renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for(auto const& capability : capabilities) {
                    capability -> apply() ;
                }
            }

            /**
             * Disable the capabilities of the render pass that is used.
             */
            exported void disableCapabilities(const RenderPass* renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for(auto const& capability : capabilities) {
                    capability -> remove() ;
                }
            }
    } ;
}

#endif
