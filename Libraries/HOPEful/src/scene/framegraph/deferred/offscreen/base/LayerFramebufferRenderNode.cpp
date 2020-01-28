#include <scene/framegraph/deferred/offscreen/base/LayerFramebufferRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

LayerFramebufferRenderNode::LayerFramebufferRenderNode(
    API::Framebuffer2DStack* framebuffer,
    int layer,
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {
    m_framebuffer = framebuffer ;
    m_layer = layer ;
}

void LayerFramebufferRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
