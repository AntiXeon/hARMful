#include <scene/framegraph/ActiveCamera.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void ActiveCamera::accept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;

    for (FrameGraphNode* child : children()) {
        child -> accept(visitor) ;
    }
}
