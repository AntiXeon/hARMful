#ifndef __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE_FRAMEGRAPH_SUBTREE__
#define __HOPE__DIRECTIONAL_LIGHT_SHADOW_CASCADE_FRAMEGRAPH_SUBTREE__

#include <scene/framegraph/ActiveCameraNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/LayerFramebufferRenderNode.hpp>
#include <memory>

namespace Hope {
    /**
     * Structure grouping the nodes of the subtree that is generated
     * just below the current DirectionalLightShadowNode to render the
     * light depth map, used to render shadows on a second render pass.
     */
    struct CSMFramegraphSubtree {
        /**
         * Camera used to render the depth map that is then used to compute
         * shadows in the next render pass.
         * This node is the root of the generated branch from the current
         * DirectionalLightShadowNode. That means that the
         * DirectionalLightShadowNode generates several nodes for processing
         * the depth map with common framegraph nodes. This is "hidden" to
         * make shadows easier at use.
         */
        std::unique_ptr<ActiveCameraNode> lightSpaceCamera = nullptr ;

        /**
         * This selector is useful to only draw the depth map from the
         * light point-of-view with the previous orthographic camera.
         */
        std::unique_ptr<RenderPassSelectorNode> depthMapPassSelector = nullptr ;

        /**
         * This node is used to clear the depth map in between two frame
         * renders.
         */
        std::unique_ptr<ClearBuffersNode> clearBuffers = nullptr ;

        /**
         * Contains the framebuffer to render the depth map in.
         */
        std::unique_ptr<LayerFramebufferRenderNode> offscreenBuffer = nullptr ;
    } ;
}

#endif
