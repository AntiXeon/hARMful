#ifndef __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__
#define __HOPE__AMBIENT_OCCLUSION_FRAMEGRAPH_SUBTREE__

namespace Hope {
    class RenderPassSelectorNode ;
    class ClearBuffersNode ;
    class DeferredRenderingNode ;
    class FramebufferRenderNode ;
    class EffectApplierNode ;

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
            EffectApplierNode* ssaoApplier = nullptr ;

            /**
             * Node bearing the framebuffer in which the ambient occlusion
             * contribution is written.
             */
            FramebufferRenderNode* offscreen = nullptr ;

            /**
             * Clear previous buffer.
             */
            ClearBuffersNode* clearBuffer = nullptr ;

            /**
             * Selector of the right render pass.
             */
            RenderPassSelectorNode* passSelector = nullptr ;

            /**
             * Node that is used to render the ambient occlusion.
             */
            DeferredRenderingNode* deferredRendering = nullptr ;
        } aoRendering ;
    } ;
}

#endif
