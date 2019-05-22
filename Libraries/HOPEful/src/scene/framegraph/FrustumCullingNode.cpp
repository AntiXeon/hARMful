#include <scene/framegraph/FrustumCullingNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void FrustumCullingNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
