#include <scene/framegraph/deferred/subtree/DisplayStepNode.hpp>
#include <scene/components/materials/deferred/DisplayDeferredRenderMaterialComponent.hpp>

using namespace Hope ;

DisplayStepNode::DisplayStepNode(
    FramebufferRenderNode* framebufferNode,
    FrameGraphNode* parent
) : OffscreenRenderingNode(
        new DisplayDeferredRenderMaterialComponent(framebufferNode),
        parent
    ),
    m_framebufferNode(framebufferNode) {}
