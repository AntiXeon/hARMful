#include <scene/framegraph/Viewport.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void Viewport::accept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;

    for (FrameGraphNode* child : children()) {
        child -> accept(visitor) ;
    }
}
