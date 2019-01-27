#include <scene/framegraph/Viewport.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void Viewport::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
