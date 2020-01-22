#include <scene/framegraph/deferred/FramebufferRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

FramebufferRenderNode::FramebufferRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : AbstractFramebufferRenderNode(windowSize, parent) {
    m_framebuffer = new API::Framebuffer2D(size) ;
}

FramebufferRenderNode::FramebufferRenderNode(
    FramebufferRenderNode* other,
    FrameGraphNode* parent
) : AbstractFramebufferRenderNode(other, parent),
    m_framebuffer(other -> m_framebuffer) {}

FramebufferRenderNode::~FramebufferRenderNode() {
    delete m_framebuffer ;
}
