#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_RENDER__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/Framebuffer.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/deferred/OffScreenRenderNode.hpp>
#include <scene/FrameGraphNode.hpp>
#include <scene/SceneTypes.hpp>

namespace Hope {
    class ClearBuffersNode ;
    class OffScreenRenderNode ;
    class RenderPassSelectorNode ;
    class OrthographicCameraComponent ;

    /**
     * Perform an off-screen render pass using a framebuffer to display light
     * shadows on the final render.
     */
    class DirectionalLightShadowNode final : public FrameGraphNode {
        private:
            /**
             * Amount of cascade shadow maps.
             */
            static const uint8_t AmountCascadeShadowMaps = 3 ;

            /**
             * Structure grouping the nodes of the subtree that is generated
             * just below the current DirectionalLightShadowNode to render the
             * light depth map, used to render shadows on a second render pass.
             */
            struct Subtree {
                /**
                 * Camera used to render the depth map that is then used to compute
                 * shadows in the next render pass.
                 * This node is the root of the generated branch from the current
                 * DirectionalLightShadowNode. That means that the
                 * DirectionalLightShadowNode generates several nodes for processing
                 * the depth map with common framegraph nodes. This is "hidden" to
                 * make shadows easier at use.
                 */
                ActiveCameraNode* lightSpaceCamera = nullptr ;

                /**
                 * This selector is useful to only draw the depth map from the
                 * light point-of-view with the previous orthographic camera.
                 */
                RenderPassSelectorNode* depthMapPassSelector = nullptr ;

                /**
                 * This node is used to clear the depth map in between two frame
                 * renders.
                 */
                ClearBuffersNode* clearBuffers = nullptr ;

                /**
                 * Contains the framebuffer to render the depth map in.
                 */
                OffScreenRenderNode* offscreenBuffer = nullptr ;
            } ;

            /**
             * Rendering camera. The shadows are computed inside the frustum of
             * this camera only.
             */
            ActiveCameraNode* m_renderingCamera = nullptr ;

            /**
             * Light from which shadows are generated.
             */
            DirectionalLightComponent* m_light = nullptr ;

            /**
             * Maximal distance from the active camera to generate shadows.
             */
            float m_maxDistance ;

            /**
             * If true, the maximal distance is the far plane distance of the
             * rendering camera.
             */
            bool m_useCameraFarPlaneDistance = true ;

            /**
             * Resolution of the shadow map.
             * Size of the framebuffer and viewport to render the scene from the
             * light point of view.
             */
            Mind::Dimension2Di m_resolution ;

            /**
             * The subtree is as follows:
             * - ActiveCameraNode for the orthographic camera that renders the
             *   depth map.
             * - RenderPassSelectorNode to only draw the depth map from the
             *   light point-of-view with the previous orthographic camera.
             * - ClearBuffersNode to clear the depth map in between two frame
             *   renders.
             * - OffScreenRenderNode to render the depth map in a dedicated
             *   framebuffer.
             */
            Subtree m_subtree ;

            /**
             * Direct access to the light camera component.
             */
            OrthographicCameraComponent* m_lightCameraComponent = nullptr ;

        public:
            /**
             * Create a new DirectionalLightShadowNode.
             * @param   light       Light from which shadows are generated.
             * @param   renderingCamera The camera of which the frustum is used
             *                          to limit the computations of the
             *                          shadows.
             * @param   resolution  Resolution of the shadow map.
             * @param   maxDistance Maximal distance from the active camera to
             *                      generate shadows.
             *                      A negative value is used to take the far
             *                      plane distance of the rendering camera as
             *                      the maximal distance of shadows.
             */
            DirectionalLightShadowNode(
                DirectionalLightComponent* light,
                ActiveCameraNode* renderingCamera,
                const Mind::Dimension2Di& resolution,
                const float maxDistance = -1.f,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Compute the frustum of the shadow camera so that is is a bounding
             * box of the rendering camera frustum.
             * In other words, we want the shadow map covers the entire frustum
             * of the rendering camera (with the limited "maxDistance" value).
             * @param   aspectRatio Aspect ratio of the rendering camera.
             */
            void computeShadowCamFrustum(const float aspectRatio) ;

            /**
             * Get the source light.
             */
            const DirectionalLightComponent* light() const {
                return m_light ;
            }

            /**
             * Get the maximal distance from the active camera to generate
             * shadows.
             */
            float maxDistance() const {
                return m_maxDistance ;
            }

            /**
             * Get the resolution of the shadow map.
             */
            const Mind::Dimension2Di& resolution() const {
                return m_resolution ;
            }

            /**
             * Get the camera for which the shadows are computed.
             */
            CameraComponent* renderingCamera() const {
                return m_renderingCamera -> camera() ;
            }

            /**
             * Get the framebuffer containing the depth map from the directional
             * light.
             */
            const API::Framebuffer& depthFramebuffer() const {
                return m_subtree.offscreenBuffer -> framebuffer() ;
            }

        protected:
            /**
             * Accept the visitor.
             */
            void specificAccept(IFrameGraphVisitor* visitor) override ;

        private:
            /**
             * Generate the framegraph subtree that is used to render the depth
             * map. This depth map is then used by shaders on the next render
             * pass to draw shadows.
             */
            void generateSubtree() ;
    } ;
}

#endif
