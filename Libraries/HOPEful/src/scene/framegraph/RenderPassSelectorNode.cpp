#include <scene/framegraph/RenderPassSelectorNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void RenderPassSelectorNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
