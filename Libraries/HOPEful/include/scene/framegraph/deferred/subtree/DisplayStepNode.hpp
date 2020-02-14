#ifndef __HOPE__DISPLAY_STEP_NODE__
#define __HOPE__DISPLAY_STEP_NODE__

#include <scene/FrameGraphNode.hpp>
#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <scene/framegraph/deferred/offscreen/base/FramebufferRenderNode.hpp>

namespace Hope {
    /**
     * Framegraph node to display on screen the result of deferred rendering.
     */
    class DisplayStepNode final : public OffscreenRenderingNode {
        private:
            /**
             * Node bearing the framebuffer containing the final render to be
             * displayed.
             */
            FramebufferRenderNode* m_framebufferNode = nullptr ;

        public:
            /**
            * Create a new DisplayStepNode instance.
            * @param   framebufferNode  Node bearing the framebuffer containing
            *                           the final render to be displayed.
            */
            DisplayStepNode(
                FramebufferRenderNode* framebufferNode,
                FrameGraphNode* parent = nullptr
            ) ;
    } ;
}

#endif
