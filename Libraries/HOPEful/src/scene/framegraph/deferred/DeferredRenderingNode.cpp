#include <scene/framegraph/deferred/DeferredRenderingNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

DeferredRenderingNode::DeferredRenderingNode(
    MaterialComponent* material,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_material(material) {
    setRenderingStepEnabled(false) ;
}

void DeferredRenderingNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
