#include <scene/framegraph/deferred/LayerOffScreenRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

LayerOffScreenRenderNode::LayerOffScreenRenderNode(
    API::Framebuffer2DStack* framebuffer,
    int layer,
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {
    m_framebuffer = framebuffer ;
    m_layer = layer ;
}

void LayerOffScreenRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
