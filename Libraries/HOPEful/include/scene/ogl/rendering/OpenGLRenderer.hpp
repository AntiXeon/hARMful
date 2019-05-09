#ifndef __HOPE__GL_RENDERER__
#define __HOPE__GL_RENDERER__

#include <scene/ogl/rendering/RenderPass.hpp>
#include <scene/ogl/rendering/glsl/ubo/BaseGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/LightGLSLDataUBO.hpp>
#include <scene/ogl/rendering/glsl/ubo/ModelGLSLDataUBO.hpp>
#include <scene/framegraph/cache/GeometryData.hpp>
#include <matrices/Matrix4x4f.hpp>

namespace Hope {
    class FrameRenderCache ;
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

        public:
            /**
             * Render the scene.
             */
            void render(std::vector<GeometryData>& dataList) ;

            /**
             * Run an update of the light UBO.
             */
            void updateLightUBO(const std::shared_ptr<Hope::FrameRenderCache> cache) ;

            /**
             * Set the view matrix.
             */
            void setViewMatrix(const Mind::Matrix4x4f& viewMatrix) {
                m_viewMatrix = viewMatrix ;
            }

            /**
             * Set the projection matrix.
             */
            void setProjectionMatrix(const Mind::Matrix4x4f& projectionMatrix) {
                m_projectionMatrix = projectionMatrix ;
            }

            /**
             * Get the base data UBO.
             */
            BaseGLSLDataUBO& baseUBO() {
                return m_baseUBO ;
            }

        private:
            /**
             * Use a material component.
             * @return  The capabilities of the render pass that is used in the
             *          material.
             */
            std::shared_ptr<API::RenderPass> useMaterial(const Hope::MaterialComponent* component) ;

            /**
             * Enable the capabilities of the render pass that is used.
             */
            void enableCapabilities(const std::shared_ptr<API::RenderPass>& renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                    capability -> apply() ;
                }
            }

            /**
             * Disable the capabilities of the render pass that is used.
             */
            void disableCapabilities(const std::shared_ptr<API::RenderPass>& renderPass) {
                auto capabilities = renderPass -> capabilities() ;
                for (const std::shared_ptr<Hope::GL::Capability>& capability : capabilities) {
                    capability -> remove() ;
                }
            }
    } ;
}

#endif
