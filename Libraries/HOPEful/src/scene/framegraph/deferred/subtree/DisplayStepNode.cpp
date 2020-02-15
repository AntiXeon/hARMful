#include <scene/framegraph/deferred/subtree/DisplayStepNode.hpp>
#include <scene/components/materials/deferred/DisplayDeferredRenderMaterialComponent.hpp>
#include <memory>

using namespace Hope ;

DisplayStepNode::DisplayStepNode(
    FramebufferRenderNode* framebufferNode,
    FrameGraphNode* parent
) : OffscreenRenderingNode(
        std::make_unique<DisplayDeferredRenderMaterialComponent>(framebufferNode),
        parent
    ),
    m_framebufferNode(framebufferNode) {}
