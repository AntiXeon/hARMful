#include <scene/framegraph/deferred/offscreen/base/AbstractFramebufferRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

AbstractFramebufferRenderNode::AbstractFramebufferRenderNode(
    const bool windowSize,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_windowSize(windowSize) {}

AbstractFramebufferRenderNode::AbstractFramebufferRenderNode(
    AbstractFramebufferRenderNode* other,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_internalFramebuffer(false),
    m_windowSize(other -> windowSize()) {}

void AbstractFramebufferRenderNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
