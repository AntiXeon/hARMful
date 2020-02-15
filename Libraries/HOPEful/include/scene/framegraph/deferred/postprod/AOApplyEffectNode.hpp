#ifndef __HOPE__AO_APPLY_EFFECT_NODE__
#define __HOPE__AO_APPLY_EFFECT_NODE__

#include <scene/framegraph/deferred/postprod/PostProdEffectNode.hpp>

namespace Hope {
    /**
     * Framegraph node to apply ambient occlusion pass to the render.
     */
    class AOApplyEffectNode : public PostProdEffectNode {
        public:
            /**
             * Create a new AOApplyEffectNode instance.
             */
            AOApplyEffectNode(FramebufferRenderNode* framebuffer) ;
    } ;
}

#endif
