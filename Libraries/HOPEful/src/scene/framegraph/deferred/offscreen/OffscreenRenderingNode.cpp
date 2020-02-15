#include <scene/framegraph/deferred/offscreen/OffscreenRenderingNode.hpp>
#include <interfaces/visitors/framegraph/IFrameGraphVisitor.hpp>

using namespace Hope ;

OffscreenRenderingNode::OffscreenRenderingNode(
    std::unique_ptr<MaterialComponent> material,
    FrameGraphNode* parent
) : FrameGraphNode(parent),
    m_material(std::move(material)) {
    setRenderingStepEnabled(false) ;
}

void OffscreenRenderingNode::specificAccept(IFrameGraphVisitor* visitor) {
    visitor -> visit(this) ;
}
