#include <scene/framegraph/deferred/subtree/DisplayStepNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

DisplayStepNode::DisplayStepNode(
    API::Framebuffer* framebuffer,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_framebuffer(framebuffer) {}

void DisplayStepNode::specificAccept(IFrameGraphVisitor* /*visitor*/) {
    //visitor -> visit(this) ;
}
