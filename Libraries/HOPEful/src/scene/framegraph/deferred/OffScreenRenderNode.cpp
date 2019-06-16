#include <scene/framegraph/deferred/OffScreenRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

OffScreenRenderNode::OffScreenRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {
    m_framebuffer = new API::Framebuffer2D(size) ;
}

OffScreenRenderNode::~OffScreenRenderNode() {
    delete m_framebuffer ;
}

void OffScreenRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
