#ifndef __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__
#define __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__

#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>
#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <scene/framegraph/ClearBuffersNode.hpp>
#include <scene/framegraph/deferred/effects/EffectApplierNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <memory>

namespace Hope {
    /**
     * Structure grouping the nodes of the subtree that is generated
     * just below the current ambient occlusion node.
     */
    struct AOFramegraphSubtree {
        /**
         * Subtree used to compute the ambient occlusion and render it into a
         * framebuffer.
         */
        struct {
            /**
             * Node to enable the SSAO computations.
             */
            std::unique_ptr<EffectApplierNode> ssaoApplier = nullptr ;

            /**
             * Node bearing the framebuffer in which the ambient occlusion
             * contribution is written.
             */
            std::unique_ptr<FramebufferRenderNode> offscreen = nullptr ;

            /**
             * Selector of the right render pass.
             */
            std::unique_ptr<RenderPassSelectorNode> passSelector = nullptr ;

            /**
             * Node that is used to render the ambient occlusion.
             */
            std::unique_ptr<OffscreenRenderingNode> deferredRendering = nullptr ;
        } aoRendering ;

        /**
         * Subtree to blur and copy the ambient occlusion (rendered with the
         * previous subtree) into the G-Buffer as the alpha channel of the
         * albedo render target.
         */
        struct {
            /**
             * Node bearing the framebuffer into which the ambient occlusion
             * contribution is copied.
             */
            std::unique_ptr<FramebufferRenderNode> offscreen = nullptr ;

            /**
             * Selector of the right render pass.
             */
            std::unique_ptr<RenderPassSelectorNode> passSelector = nullptr ;

            /**
             * Node that is used to blur and copy the ambient occlusion.
             */
            std::unique_ptr<OffscreenRenderingNode> deferredRendering = nullptr ;
        } aoBlurCopy ;
    } ;
}

#endif
