#include <scene/framegraph/deferred/FramebufferRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

FramebufferRenderNode::FramebufferRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {
    m_framebuffer = new API::Framebuffer2D(size) ;
}

FramebufferRenderNode::FramebufferRenderNode(
    FramebufferRenderNode* other,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_internalFramebuffer(false),
    m_framebuffer(other -> framebuffer()),
    m_windowSize(other -> windowSize()) {}

FramebufferRenderNode::~FramebufferRenderNode() {
    delete m_framebuffer ;
}

void FramebufferRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
