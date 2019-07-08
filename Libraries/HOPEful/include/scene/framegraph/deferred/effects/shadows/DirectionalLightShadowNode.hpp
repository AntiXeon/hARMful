#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_RENDER__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_RENDER__

#include <HopeAPI.hpp>

#ifdef OGL
    #include <scene/ogl/rendering/framebuffers/Framebuffer2DStack.hpp>
    #include <scene/components/materials/shaders/GLSL/includes/TextureUnits.hpp>
    namespace API = Hope::GL ;
#endif

#include <scene/framegraph/deferred/effects/EffectFramegraphNode.hpp>
#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/components/lights/DirectionalLightComponent.hpp>
#include <scene/framegraph/deferred/effects/shadows/cascade/CSMParameters.hpp>
#include <scene/framegraph/deferred/effects/shadows/cascade/ShadowCascade.hpp>
#include <scene/SceneTypes.hpp>
#include <vector>

namespace Hope {
    class ClearBuffersNode ;
    class FramebufferRenderNode ;
    class RenderPassSelectorNode ;
    class OrthographicCameraComponent ;

    /**
     * Perform an off-screen render pass using a framebuffer to display light
     * shadows on the final render.
     *
     * This node implements cascade shadow mapping. This is performed through
     * the framegraph to render each shadow map as a single framegraph branch.
     * The framegraph tree is built below the current DirectionalLightShadowNode
     * with all the required nodes to render it as usual rendering steps
     * (cameras, etc).
     *
     * The scene graph is modified as well by creating a cascade shadow mapping
     * entity just below the root entity of the scene graph. All the required
     * cameras are stored below this "CSM root entity".
     */
    class DirectionalLightShadowNode final : public EffectFrameGraphNode {
        private:
            /**
             * Steps for splitting the total render frustum.
             */
            static const float CascadeSplitStep ;

            /**
             * Parameters of the cascade shadow mapping.
             */
            CSMParameters m_parameters ;

            /**
             * Rendering camera. The shadows are computed inside the frustum of
             * this camera only.
             */
            ActiveCameraNode* m_renderingCamera = nullptr ;

            /**
             * Root node for cascade related cameras.
             */
            Entity* m_cascadeRoot = nullptr ;

            /**
             * Framebuffer that is shared among the different
             * LayerFramebufferRenderNodes.
             */
            API::Framebuffer2DStack* m_framebuffer = nullptr ;

            /**
             * Shadow cascade objects.
             */
            std::vector<ShadowCascade> m_cascades ;

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
                const uint32_t resolution,
                const float maxDistance = -1.f,
                const uint8_t amountCascades = 3,
                FrameGraphNode* parent = nullptr
            ) ;

            /**
             * Compute the cascades shadow maps.
             * @param   aspectRatio Aspect ratio of the rendering camera.
             */
            void computeCascadeShadowMaps(const float aspectRatio) ;

            /**
             * Get the source light.
             */
            const DirectionalLightComponent* light() const {
                return m_parameters.light ;
            }

            /**
             * Get the maximal distance from the active camera to generate
             * shadows.
             */
            float maxDistance() const {
                return m_parameters.maxDistance ;
            }

            /**
             * Get the resolution of the shadow map.
             */
            uint32_t resolution() const {
                return m_parameters.resolution ;
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
            const API::Framebuffer2DStack* depthFramebuffer() const {
                return m_framebuffer ;
            }

            /**
             * Get a shadow cascade.
             */
            const ShadowCascade& cascade(uint8_t index) const {
                return m_cascades[index] ;
            }

            /**
             * Amount of cascades.
             */
            int amountCascades() const {
                return m_parameters.amountCascades ;
            }

            /**
             * Get the type of the effect.
             */
            EffectNodeType effectType() const {
                return ShadowsEffectType ;
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
