#include <scene/framegraph/FrustumCulling.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void FrustumCulling::accept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;

    for (FrameGraphNode* child : children()) {
        child -> accept(visitor) ;
    }
}
