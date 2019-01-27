#include <scene/framegraph/ActiveCamera.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void ActiveCamera::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
