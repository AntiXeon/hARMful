#include <scene/framegraph/ActiveCamera.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

ActiveCamera::ActiveCamera(
    Hope::FrameGraphNode* parent,
    ActiveCamera* cacheOwner
) : FrameGraphNode(parent) {
    if (cacheOwner) {
        m_isCacheOwner = false ;
        m_cache = cacheOwner -> m_cache ;
    }
    else {
        m_isCacheOwner = true ;
        m_cache = std::make_shared<Hope::FrameRenderCache>() ;
    }
}

void ActiveCamera::specificAccept(IFrameGraphVisitor* visitor) {
    if (m_isCacheOwner) {
        m_cache -> clear() ;
    }

    visitor -> visit(this) ;
}
