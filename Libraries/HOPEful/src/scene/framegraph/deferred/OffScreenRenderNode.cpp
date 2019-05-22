#include <scene/framegraph/deferred/OffScreenRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

OffScreenRenderNode::OffScreenRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {
    m_framebuffer.resize(size) ;
}

void OffScreenRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
