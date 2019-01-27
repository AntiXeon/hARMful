#include <scene/framegraph/FrustumCulling.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

void FrustumCulling::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
