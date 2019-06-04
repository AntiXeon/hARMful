#include <scene/framegraph/ClearBuffersNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void ClearBuffersNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
