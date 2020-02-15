#include <scene/framegraph/deferred/offscreen/base/FramebufferMultisampleRenderNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

FramebufferMultisampleRenderNode::FramebufferMultisampleRenderNode(
    const Mind::Dimension2Di& size,
    const bool windowSize,
    FrameGraphNode* parent
) : AbstractFramebufferRenderNode(windowSize, parent) {
    m_framebuffer = std::make_shared<API::Framebuffer2DMultisample>(size) ;
}

FramebufferMultisampleRenderNode::FramebufferMultisampleRenderNode(
    FramebufferMultisampleRenderNode* other,
    FrameGraphNode* parent
) : AbstractFramebufferRenderNode(other, parent),
    m_framebuffer(other -> m_framebuffer) {}
