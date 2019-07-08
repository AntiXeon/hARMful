#ifndef __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__
#define __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__

namespace Hope {
    class RenderPassSelectorNode ;
    class ClearBuffersNode ;
    class DeferredRenderingNode ;
    class FramebufferRenderNode ;
    class MemoryBarrierNode ;

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
             * Node bearing the framebuffer in which the ambient occlusion
             * contribution is written.
             */
            FramebufferRenderNode* offscreen = nullptr ;

            /**
             * Selector of the right render pass.
             */
            RenderPassSelectorNode* passSelector = nullptr ;

            /**
             * Node that is used to render the ambient occlusion.
             */
            DeferredRenderingNode* deferredRendering = nullptr ;
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
            FramebufferRenderNode* offscreen = nullptr ;

            /**
             * Selector of the right render pass.
             */
            RenderPassSelectorNode* passSelector = nullptr ;

            /**
             * Node that is used to blur and copy the ambient occlusion.
             */
            DeferredRenderingNode* deferredRendering = nullptr ;
        } aoBlurCopy ;
    } ;
}

#endif
