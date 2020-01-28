#include <scene/framegraph/deferred/OffscreenRenderingNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

OffscreenRenderingNode::OffscreenRenderingNode(
    MaterialComponent* material,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_material(material) {
    setRenderingStepEnabled(false) ;
}

void OffscreenRenderingNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
