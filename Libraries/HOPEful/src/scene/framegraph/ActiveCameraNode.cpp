#include <scene/framegraph/ActiveCameraNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

ActiveCameraNode::ActiveCameraNode(
    Hope::FrameGraphNode* parent,
    ActiveCameraNode* cacheOwner
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

void ActiveCameraNode::specificAccept(IFrameGraphVisitor* visitor) {
    if (m_isCacheOwner) {
        m_cache -> clear() ;
    }

    visitor -> visit(this) ;
}
